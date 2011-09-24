using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.IO.Pipes;
using System.Linq;
using System.Text;
using System.Threading;
using Halak.Bibim.IO;

namespace Halak.Bibim.Asset.Pipeline
{
    [GameModule('P', 'A', 'S', 'S')]
    public sealed class PipedGameAssetServer : GameAssetServer
    {
        #region Fields
        private string pipeName;
        private LinkedList<Peer> peers;
        #endregion

        #region Properties
        public string PipeName
        {
            get { return pipeName; }
            set
            {
                if (pipeName != value)
                {
                    pipeName = value;

                    foreach (Peer item in peers)
                        item.Disconnect();

                    peers.Clear();

                    if (string.IsNullOrEmpty(pipeName) == false)
                        InitializeNewPeer();
                }
            }
        }
        #endregion

        #region Constructor
        public PipedGameAssetServer()
            : this(null, string.Empty)
        {
        }

        public PipedGameAssetServer(GameAssetKitchen kitchen, string pipeName)
            : base(kitchen)
        {
            this.pipeName = pipeName;
            this.peers = new LinkedList<Peer>();

            if (string.IsNullOrEmpty(pipeName) == false)
                InitializeNewPeer();
        }
        #endregion

        #region Methods
        protected override void Send(object target, byte[] buffer, int index, int count)
        {
        }

        #region Peer-Handlers
        private void InitializeNewPeer()
        {
            Peer result = new Peer(pipeName);
            peers.AddLast(result);
            result.Stream.BeginWaitForConnection(new AsyncCallback(OnPeerConnected), result);

            Trace.WriteLine("Waiting new peer...");
        }

        private void OnPeerConnected(IAsyncResult result)
        {
            Peer peer = (Peer)result.AsyncState;
            if (result.IsCompleted)
            {
                peer.Stream.EndWaitForConnection(result);
                string directory = peer.StreamReader.ReadBibimString();
                peer.Stream.BeginRead(peer.Buffer, 0, 4, new AsyncCallback(OnPeerRead), peer);

                Trace.WriteLine("Peer connected. \n \t>{0}", directory);
            }
            else
            {
                peer.Disconnect();
                peers.Remove(peer);

                Trace.WriteLine("Peer connect failure.");
            }

            InitializeNewPeer();
        }

        private void OnPeerRead(IAsyncResult result)
        {
            Peer peer = (Peer)result.AsyncState;

            if (result.IsCompleted)
            {
                int readBytes = peer.Stream.EndRead(result);
                if (readBytes == 4)
                {
                    uint id = BitConverter.ToUInt32(peer.Buffer, 0);
                    ProcessPacket(null, id, peer.StreamReader);
                    string assetPipeName = Guid.NewGuid().ToString();
                    peer.StreamWriter.WriteBibimString(assetPipeName);
                    peer.ResetBuffer();
                    peer.Stream.BeginRead(peer.Buffer, 0, 4, new AsyncCallback(OnPeerRead), peer);
                }
                else
                {
                    Trace.WriteLine("Peer disconnected.");
                    peer.Disconnect();
                }
            }

            //    Connection connection = (Connection)result.AsyncState;
            //    int r = connection.Stream.EndRead(result);
            //    uint id = BitConverter.ToUInt32(connection.Buffer, 0);
            //    switch (id)
            //    {
            //        case 1000:
            //            string path = connection.Reader.ReadBibimString();
            //            object asset = Kitchen.Cook(path);
            //            if (asset != null)
            //            {
            //                GameAssetWriter writer = GameAssetWriter.CreateWriter(asset.GetType());
            //                MemoryStream ms = new MemoryStream();
            //                AssetStreamWriter assetWriter = new AssetStreamWriter(ms, null);
            //                writer.Write(assetWriter, asset);

            //                NamedPipeServerStream serverStream = new NamedPipeServerStream(pipeName + "_" + "ASSET", PipeDirection.Out,
            //                                       NamedPipeServerStream.MaxAllowedServerInstances,
            //                                       PipeTransmissionMode.Byte,
            //                                       PipeOptions.Asynchronous);
            //                serverStream.WaitForConnection();
            //                serverStream.BeginWrite(ms.GetBuffer(), 0, (int)ms.Length, new AsyncCallback(OnAssetWritten), serverStream);
            //                connection.Buffer[0] = 0;
            //                connection.Buffer[1] = 0;
            //                connection.Buffer[2] = 0;
            //                connection.Buffer[3] = 0;
            //                connection.Stream.BeginRead(connection.Buffer, 0, 4, new AsyncCallback(OnRead), connection);
            //                ms.Close();
            //            }
            //            break;
            //    }
            //}
            //else
            //{
            //}
        }

        private void OnAssetWritten(IAsyncResult result)
        {
            try
            {
                NamedPipeServerStream stream = (NamedPipeServerStream)result.AsyncState;
                stream.EndWrite(result);
                stream.Flush();
                stream.Disconnect();
                stream.Close();
            }
            catch (Exception ex)
            {
            }

            if (result.IsCompleted == false)
            {
            }
        }
        #endregion
        #endregion

        #region Peer
        private class Peer
        {
            public NamedPipeServerStream Stream
            {
                get;
                private set;
            }

            public BinaryReader StreamReader
            {
                get;
                private set;
            }

            public BinaryWriter StreamWriter
            {
                get;
                private set;
            }

            public byte[] Buffer
            {
                get;
                private set;
            }

            public Peer(string pipeName)
            {
                this.Stream = new NamedPipeServerStream(pipeName, PipeDirection.InOut,
                                                        NamedPipeServerStream.MaxAllowedServerInstances,
                                                        PipeTransmissionMode.Byte,
                                                        PipeOptions.Asynchronous);
                this.StreamReader = new BinaryReader(Stream);
                this.StreamWriter = new BinaryWriter(Stream);
                this.Buffer = new byte [64];
            }

            public void Disconnect()
            {
                if (this.Stream.IsConnected)
                    this.Stream.Disconnect();

                this.Stream.Dispose();
                this.Stream = null;
                this.StreamReader = null;
                this.StreamWriter = null;
                this.Buffer = null;
            }

            public void ResetBuffer()
            {
                ResetBuffer(0, Buffer.Length);
            }

            public void ResetBuffer(int index, int length)
            {
                byte[] buffer = Buffer;
                int end = Math.Min(index + length, buffer.Length);
                for (int i = index; i < end; i++)
                    buffer[i] = 0x00;
            }
        }
        #endregion
    }
}
