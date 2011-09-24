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
        private Dictionary<string, GameAssetRecipe> recipes;
        private Thread taskThread;
        private int taskThreadClosed;
        private LinkedList<Action> taskQueue;
        private object taskQueueLock = new object();
        private object taskQueueEvent = new object();
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
            recipes = new Dictionary<string, GameAssetRecipe>();
            Kitchen = kitchen;
            taskThread = new Thread(new ThreadStart(WorkCookingThread));
            taskThreadClosed = 0;
            taskThread.Start();
            taskQueue = new LinkedList<Action>();
        }

        ~GameAssetServer()
        {
            Interlocked.Exchange(ref taskThreadClosed, 1);
            taskThread.Join();
        }
        #endregion

        #region Methods
        protected abstract void Send(object target, byte[] buffer, int index, int count);

        protected bool ProcessPacket(object target, uint id, BinaryReader reader)
        {
            switch (id)
            {
                case 1000:
                    GameAssetKitchen kitchen = Kitchen;
                    string path = reader.ReadBibimString();
                    Trace.WriteLine("Request Asset {0}", path);
                    AddTask(() =>
                    {
                        object asset = kitchen.Cook(path);
                        if (asset != null)
                        {
                            GameAssetWriter writer = GameAssetWriter.CreateWriter(asset.GetType());
                            MemoryStream memoryStream = new MemoryStream();
                            AssetStreamWriter streamWriter = new AssetStreamWriter(memoryStream, null);
                            writer.Write(streamWriter, asset);

                            Send(target, memoryStream.GetBuffer(), 0, (int)memoryStream.Length);

                            string filepath = Path.ChangeExtension(path, GameAsset.BinaryFileExtension);
                            FileStream fileStream = new FileStream(filepath, FileMode.Create, FileAccess.Write);
                            fileStream.BeginWrite(memoryStream.GetBuffer(),
                                                  0,
                                                  (int)memoryStream.Length,
                                                  new AsyncCallback(OnCacheFileWritten),
                                                  fileStream);
                        }
                    });
                    return true;
                default:
                    return false;
            }
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

        private void OnCacheFileWritten(IAsyncResult result)
        {
            FileStream fileStream = (FileStream)result.AsyncState;
            fileStream.EndWrite(result);
            fileStream.Close();
        }
        #endregion
    }
}
