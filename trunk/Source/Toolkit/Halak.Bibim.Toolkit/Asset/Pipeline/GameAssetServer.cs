using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Text;
using System.Threading;
using Halak.Bibim.IO;

namespace Halak.Bibim.Asset.Pipeline
{
    public abstract class GameAssetServer : GameModule
    {
        #region Fields
        private ConcurrentQueue<Action> taskQueue;
        private Thread taskThread;
        private int taskThreadClosed;

        private Dictionary<string, byte[]> assetCaches;
        private object assetCachesLock = new object();
        #endregion

        #region Properties
        public GameAssetKitchen Kitchen
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        protected GameAssetServer()
            : this(null)
        {
        }

        protected GameAssetServer(GameAssetKitchen kitchen)
        {
            Kitchen = kitchen;
            taskQueue = new ConcurrentQueue<Action>();
            taskThread = new Thread(new ThreadStart(WorkCookingThread));
            taskThreadClosed = 0;
            taskThread.Start();

            assetCaches = new Dictionary<string, byte[]>();
        }

        ~GameAssetServer()
        {

        }
        #endregion
        
        #region Methods
        protected override void OnStatusChanged(GameModuleStatus old)
        {
            switch (Status)
            {
                case GameModuleStatus.Dead:
                    Interlocked.Exchange(ref taskThreadClosed, 1);
                    taskThread.Join();
                    taskQueue = null;
                    break;
                case GameModuleStatus.Alive:
                case GameModuleStatus.Active:
                    if (taskThread.IsAlive == false)
                    {
                        taskQueue = new ConcurrentQueue<Action>();
                        Interlocked.Exchange(ref taskThreadClosed, 0);
                        taskThread.Start();
                    }
                    break;
            }
        }

        protected void BeginCook(string directory, string assetPath, Action<byte[], int, int> callback, Action fallback)
        {
            string binaryAbsolutePath = Path.ChangeExtension(Path.Combine(directory, assetPath), GameAsset.BinaryFileExtension);

            // Cache Table에 Asset Binary가 존재하면 Cooking하지 않습니다.

            byte[] cache = null;
            bool hasCache = false;
            lock (assetCachesLock)
                hasCache = assetCaches.TryGetValue(binaryAbsolutePath, out cache);

            if (hasCache)
            {
                callback(cache, 0, cache.Length);
                return;
            }

            GameAssetKitchen kitchen = Kitchen;
            taskQueue.Enqueue(() =>
                              {
                                  try
                                  {
                                      Trace.WriteLine(string.Format("#start cooking. {0}", assetPath));

                                      string recipePath = Path.ChangeExtension(assetPath, GameAsset.TextFileExtension);
                                      object asset = kitchen.Cook(directory, recipePath);
                                      if (asset != null)
                                      {
                                          // Cooking 된 asset은 나중에 가져다 쓰기 쉽게 단순 Binary화합니다.

                                          GameAssetWriter writer = GameAssetWriter.CreateWriter(asset.GetType());
                                          MemoryStream memoryStream = new MemoryStream();
                                          AssetStreamWriter streamWriter = new AssetStreamWriter(memoryStream, null, Kitchen.Storage);
                                          writer.Write(streamWriter, asset);

                                          callback(memoryStream.GetBuffer(), 0, (int)memoryStream.Length);

                                          // Cooking 작업을 마치고 Callback까지 호출했으면,
                                          //   1. Asset Binary를 Cache Table에 보관합니다.
                                          //      다음 요청부터 Cooking 하지 않고 바로 Cache에서 넘겨줍니다.
                                          //   2. "{AssetName}.ab" File에 Asset Binary를 저장합니다.

                                          byte[] cacheBuffer = new byte[memoryStream.Length];
                                          System.Buffer.BlockCopy(memoryStream.GetBuffer(), 0, cacheBuffer, 0, (int)memoryStream.Length);

                                          lock (assetCachesLock)
                                              assetCaches[binaryAbsolutePath] = cacheBuffer;

                                          WriteCacheFile(binaryAbsolutePath, cacheBuffer);
                                      }
                                      else
                                      {
                                          Trace.WriteLine(string.Format("!Asset cooking failed. {0}", assetPath));

                                          if (fallback != null)
                                              fallback();
                                      }
                                  }
                                  catch (Exception e)
                                  {
                                      Trace.WriteLine("!" + e.Message);
                                      Trace.WriteLine("!" + e.StackTrace);

                                      if (fallback != null)
                                          fallback();
                                  }
                              });
        }

        protected void WorkCookingThread()
        {
            Action task = null;
            while (taskThreadClosed == 0)
            {
                Thread.Sleep(1);

                if (taskQueue.Count == 0)
                    continue;

                if (taskQueue.TryDequeue(out task))
                    task();
            }
        }
        
        private static void WriteCacheFile(string path, byte[] buffer)
        {
            WriteCacheFile(path, buffer, 0, buffer.Length);
        }

        private static void WriteCacheFile(string path, byte[] buffer, int index, int count)
        {
            FileStream fileStream = new FileStream(path, FileMode.Create, FileAccess.Write);
            fileStream.BeginWrite(buffer, index, count,
                                  (result) =>
                                  {
                                      fileStream.EndWrite(result);
                                      fileStream.Close();
                                  }, null);
        }
        #endregion
    }
}
