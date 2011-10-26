using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Text;
using System.Threading;
using Bibim.IO;

namespace Bibim.Asset.Pipeline
{
    public abstract class GameAssetServer : GameModule
    {
        #region AssetCache (Nested Struct)
        private struct AssetCache
        {
            public readonly byte[] Buffer;
            public readonly string[] Dependencies;

            public AssetCache(byte[] buffer, string[] dependencies)
            {
                Buffer = buffer;
                Dependencies = dependencies;
            }
        }
        #endregion

        #region Fields
        private ConcurrentQueue<Action> taskQueue;
        private Thread taskThread;
        private int taskThreadClosed;

        private Dictionary<string, AssetCache> assetCaches;
        private object assetCachesLock = new object();
        private List<FileSystemWatcher> dependencyWatchers;
        #endregion

        #region Properties
        public GameAssetKitchen Kitchen
        {
            get;
            set;
        }

        public bool IsBusy
        {
            get
            {
                return !taskQueue.IsEmpty;
            }
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

            assetCaches = new Dictionary<string, AssetCache>();
            dependencyWatchers = new List<FileSystemWatcher>();
        }
        #endregion

        #region Methods
        public void Precook(string directory, string assetPath)
        {
            BeginCook(directory, assetPath, null, null);
        }

        public void Precook(string directory, string assetPath, Action<byte[], int, int> callback, Action fallback)
        {
            BeginCook(directory, assetPath, callback, fallback);
        }

        protected override void OnStatusChanged(GameModuleStatus old)
        {
            switch (Status)
            {
                case GameModuleStatus.Dead:
                    foreach (var item in dependencyWatchers)
                        item.EnableRaisingEvents = false;

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

                    foreach (var item in dependencyWatchers)
                        item.EnableRaisingEvents = true;
                    break;
            }
        }

        protected void BeginCook(string directory, string assetPath, Action<byte[], int, int> callback, Action fallback)
        {
            string binaryAbsolutePath = Path.ChangeExtension(Path.Combine(directory, assetPath), GameAsset.BinaryFileExtension);

            // Cache Table에 Asset Binary가 존재하면 Cooking하지 않습니다.

            AssetCache cache;
            bool hasCache = false;
            lock (assetCachesLock)
                hasCache = assetCaches.TryGetValue(binaryAbsolutePath, out cache);

            if (hasCache)
            {
                callback(cache.Buffer, 0, cache.Buffer.Length);
                return;
            }

            GameAssetKitchen kitchen = Kitchen;
            taskQueue.Enqueue(() =>
                              {
                                  try
                                  {
                                      Trace.WriteLine(string.Format("start cooking. {0}", assetPath));

                                      string recipePath = Path.ChangeExtension(assetPath, GameAsset.TextFileExtension);
                                      GameAssetKitchen.CookingReport report = kitchen.Cook(directory, recipePath);
                                      if (report.Asset != null)
                                      {
                                          // Cooking 된 asset은 나중에 가져다 쓰기 쉽게 단순 Binary화합니다.

                                          GameAssetWriter writer = GameAssetWriter.CreateWriter(report.Asset.GetType());
                                          MemoryStream memoryStream = new MemoryStream();
                                          AssetStreamWriter streamWriter = new AssetStreamWriter(memoryStream, null, Kitchen.Storage);
                                          writer.Write(streamWriter, report.Asset);

                                          if (callback != null)
                                              callback(memoryStream.GetBuffer(), 0, (int)memoryStream.Length);

                                          // Cooking 작업을 마치고 Callback까지 호출했으면,
                                          //   1. Asset Binary를 Cache Table에 보관합니다.
                                          //      다음 요청부터 Cooking 하지 않고 바로 Cache에서 넘겨줍니다.
                                          //   2. "{AssetName}.ab" File에 Asset Binary를 저장합니다.

                                          byte[] cacheBuffer = new byte[memoryStream.Length];
                                          System.Buffer.BlockCopy(memoryStream.GetBuffer(), 0, cacheBuffer, 0, (int)memoryStream.Length);

                                          string[] dependencies = new string[report.Dependencies.Count];
                                          report.Dependencies.CopyTo(dependencies, 0);

                                          lock (assetCachesLock)
                                              assetCaches[binaryAbsolutePath] = new AssetCache(cacheBuffer, dependencies);

                                          WriteCacheFile(binaryAbsolutePath, cacheBuffer);

                                          Trace.TraceInformation("Asset cooking succeed. {0}", assetPath);

                                          foreach (string item in dependencies)
                                          {
                                              string dependencyDirectory = Path.GetDirectoryName(item);
                                              if (dependencyWatchers.Exists((watcher) => string.Compare(watcher.Path, dependencyDirectory) == 0) == false)
                                              {
                                                  var watcher = new FileSystemWatcher(dependencyDirectory);
                                                  watcher.Changed += (o, e) => { RemoveAssetCachesByDependency(e.FullPath); };
                                                  watcher.Deleted += (o, e) => { RemoveAssetCachesByDependency(e.FullPath); };
                                                  watcher.Renamed += (o, e) => { RemoveAssetCachesByDependency(e.FullPath); };
                                                  watcher.IncludeSubdirectories = false;
                                                  watcher.EnableRaisingEvents = true;
                                                  dependencyWatchers.Add(watcher);
                                              }
                                          }
                                      }
                                      else
                                      {
                                          Trace.TraceError("AssetRecipe not found. {0}", assetPath);

                                          if (fallback != null)
                                              fallback();
                                      }
                                  }
                                  catch (Exception ex)
                                  {
                                      Trace.WriteLine(ex);

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

        protected void RemoveAssetCachesByDependency(string path)
        {
            List<string> removingKeys = new List<string>();

            lock (assetCachesLock)
            {
                foreach (var cache in assetCaches)
                {
                    foreach (string item in cache.Value.Dependencies)
                    {
                        if (string.Compare(item, path, true) == 0)
                        {
                            removingKeys.Add(cache.Key);
                            break;
                        }
                    }
                }

                foreach (string item in removingKeys)
                    assetCaches.Remove(item);
            }

            foreach (string item in removingKeys)
                Trace.TraceInformation("{0}의 내용이 바뀌었으므로 {1}의 Cache를 비웠습니다.", Path.GetFileName(path), Path.GetFileName(item));
        }
        #endregion
    }
}
