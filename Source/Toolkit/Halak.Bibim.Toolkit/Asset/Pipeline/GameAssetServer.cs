using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using Halak.Bibim.IO;

namespace Halak.Bibim.Asset.Pipeline
{
    public abstract class GameAssetServer : GameModule
    {
        #region Fields
        private Thread taskThread;
        private int taskThreadClosed;
        private LinkedList<Action> taskQueue;
        private object taskQueueLock = new object();
        private object taskQueueEvent = new object();

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
            taskThread = new Thread(new ThreadStart(WorkCookingThread));
            taskThreadClosed = 0;
            taskThread.Start();
            taskQueue = new LinkedList<Action>();

            assetCaches = new Dictionary<string, byte[]>();
        }

        ~GameAssetServer()
        {
            Interlocked.Exchange(ref taskThreadClosed, 1);
            taskThread.Join();
        }
        #endregion
        
        #region Methods
        protected void BeginCook(string path, Action<byte[], int, int> callback, Action fallback)
        {
            string binaryPath = Path.ChangeExtension(path, GameAsset.BinaryFileExtension);

            // Cache Table에 Asset Binary가 존재하면 Cooking하지 않습니다.

            byte[] cache = null;
            bool hasCache = false;
            lock (assetCachesLock)
                hasCache = assetCaches.TryGetValue(binaryPath, out cache);

            if (hasCache)
            {
                callback(cache, 0, cache.Length);
                return;
            }

            GameAssetKitchen kitchen = Kitchen;
            AddTask(() =>
                    {
                        try
                        {
                            Trace.WriteLine(string.Format("#start cooking. {0}", path));

                            string recipePath = Path.ChangeExtension(path, GameAsset.TextFileExtension);
                            object asset = kitchen.Cook(recipePath);
                            if (asset != null)
                            {
                                // Cooking 된 asset은 나중에 가져다 쓰기 쉽게 단순 Binary화합니다.

                                GameAssetWriter writer = GameAssetWriter.CreateWriter(asset.GetType());
                                MemoryStream memoryStream = new MemoryStream();
                                AssetStreamWriter streamWriter = new AssetStreamWriter(memoryStream, null);
                                writer.Write(streamWriter, asset);

                                callback(memoryStream.GetBuffer(), 0, (int)memoryStream.Length);

                                // Cooking 작업을 마치고 Callback까지 호출했으면,
                                //   1. Asset Binary를 Cache Table에 보관합니다.
                                //      다음 요청부터 Cooking 하지 않고 바로 Cache에서 넘겨줍니다.
                                //   2. "{AssetName}.ab" File에 Asset Binary를 저장합니다.

                                byte[] cacheBuffer = memoryStream.GetBuffer();

                                lock (assetCachesLock)
                                    assetCaches[binaryPath] = cacheBuffer;

                                WriteCacheFile(binaryPath, cacheBuffer);
                            }
                            else
                            {
                                Trace.WriteLine(string.Format("!Asset cooking failed. {0}", path));

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

                lock (taskQueueLock)
                {
                    task = taskQueue.First.Value;
                    taskQueue.RemoveFirst();
                }

                task();
            }
        }

        private void AddTask(Action task)
        {
            lock (taskQueueLock)
                taskQueue.AddLast(task);
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
