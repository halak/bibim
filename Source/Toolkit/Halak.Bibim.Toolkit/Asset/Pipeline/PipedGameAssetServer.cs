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
        private uint idGenerator;
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
            this.idGenerator = 0;

            if (string.IsNullOrEmpty(pipeName) == false)
                InitializeNewPeer();
        }
        #endregion

        #region Methods
        #region Peer-Handlers
        private void InitializeNewPeer()
        {
            Peer result = new Peer(pipeName);
            peers.AddLast(result);
            result.Stream.BeginWaitForConnection(new AsyncCallback(OnPeerConnected), result);

            Trace.WriteLine("Waiting new peer...");
        }

        private void ShutdownPeer(Peer peer)
        {
            ShutdownPeer(peer, null);
        }

        private void ShutdownPeer(Peer peer, string message)
        {
            peer.Disconnect();
            peers.Remove(peer);

            if (string.IsNullOrEmpty(message) == false)
                Trace.WriteLine(message);
        }

        private void OnPeerConnected(IAsyncResult result)
        {
            Peer peer = (Peer)result.AsyncState;
            if (result.IsCompleted)
            {
                peer.Stream.EndWaitForConnection(result);
                string exeFilePath = peer.StreamReader.ReadBibimString();

                string exeFileName = Path.GetFileNameWithoutExtension(exeFilePath);
                peer.Name = exeFileName;
                peer.ID = idGenerator++;

                peer.Stream.BeginRead(peer.Buffer, 0, 4, new AsyncCallback(OnPeerRead), peer);

                Trace.WriteLine(string.Format("[{0}:{1}] Peer connected.", peer.Name, peer.ID));
            }
            else
            {
                ShutdownPeer(peer);
                Trace.WriteLine("Peer connect failure.");
            }

            InitializeNewPeer();
        }

        private void OnPeerRead(IAsyncResult result)
        {
            Peer peer = (Peer)result.AsyncState;

            if (result.IsCompleted == false)
            {
                ShutdownPeer(peer, string.Format("[{0}:{1}] Peer disconnected. (unknown)", peer.Name, peer.ID));
                return;
            }

            int readBytes = peer.Stream.EndRead(result);
            if (readBytes != 4)
            {
                ShutdownPeer(peer, string.Format("[{0}:{1}] Peer disconnected. (read error)", peer.Name, peer.ID));
                return;
            }

            uint id = BitConverter.ToUInt32(peer.Buffer, 0);
            string message = null;
            switch (id)
            {
                case AssetProvider.LoadAssetPacketID:
                    string path = peer.StreamReader.ReadBibimString();
                    string guid = Guid.NewGuid().ToString();
                    peer.StreamWriter.WriteBibimString(guid);
                    BeginCook(path, (buffer, index, count) =>
                    {
                        NamedPipeServerStream stream = new NamedPipeServerStream(guid,
                                                                                 PipeDirection.Out,
                                                                                 NamedPipeServerStream.MaxAllowedServerInstances,
                                                                                 PipeTransmissionMode.Byte,
                                                                                 PipeOptions.Asynchronous);
                        stream.WaitForConnection();
                        stream.BeginWrite(buffer, 0, count, (_) =>
                        {
                            stream.Disconnect();
                            stream.Dispose();
                        }, null);
                    });
                    message = string.Format("[{0}:{1}] Received LoadAssetPacket {2}\n ({3}) AssetPipe.", peer.Name, peer.ID, path, guid);
                    break;
            }

            peer.ResetBuffer();
            peer.Stream.BeginRead(peer.Buffer, 0, 4, new AsyncCallback(OnPeerRead), peer);

            if (string.IsNullOrEmpty(message) == false)
                Trace.WriteLine(message);
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

            public uint ID
            {
                get;
                set;
            }

            public string Name
            {
                get;
                set;
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
