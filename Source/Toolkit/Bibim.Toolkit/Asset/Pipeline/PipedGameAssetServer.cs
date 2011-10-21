using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.IO.Pipes;
using System.Text;
using System.Threading;
using Bibim;
using Bibim.IO;

namespace Bibim.Asset.Pipeline
{
    [ClassID('P', 'A', 'S', 'S')]
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
                Trace.TraceInformation(message);
        }

        private void OnPeerConnected(IAsyncResult result)
        {
            Peer peer = (Peer)result.AsyncState;
            if (result.IsCompleted)
            {
                peer.Stream.EndWaitForConnection(result);
                
                // 접속 직후 Client에서는 기본 Directory와 Client 이름을 보내오기 때문에,
                // 바로 읽어서 Client정보에 설정합니다.
                string directory = peer.StreamReader.ReadBibimString();
                string clientName = peer.StreamReader.ReadBibimString();

                peer.Directory = directory;
                peer.Name = clientName;
                peer.ID = idGenerator++;

                // Client에서는 uint32형식의 Packet ID를 먼저 전송합니다.
                // Packet 종류에 따라 다음에 이어질 정보가 달라집니다.
                // 그렇기 때문에 일단 Packet ID를 읽기 위해 일단 4byte 비동기 읽기 작업을 수행합니다.
                peer.Stream.BeginRead(peer.Buffer, 0, 4, new AsyncCallback(OnPeerRead), peer);

                Trace.TraceInformation(string.Format("[{0}:{1}] Peer connected.", peer.Name, peer.ID));
            }
            else
            {
                ShutdownPeer(peer);
                Trace.TraceError("Peer connect failed.");
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
                // Client에서 정보를 보내기 전까지는 무한정 대기하며 이 Callback은 호출되지 않습니다.
                // Callback이 호출되었는데 Packet ID를 읽어올 4byte만큼 Stream을 읽지 못했다면 실패로 간주합니다.
                // 경험적으로 이는 Client와의 접속이 끊겼을 때 자주 발생하였습니다.
                // 그렇기 때문에 Peer와의 접속을 끊는 작업을 수행합니다.
                ShutdownPeer(peer, string.Format("[{0}:{1}] Peer disconnected. (read error)", peer.Name, peer.ID));
                return;
            }

            uint id = BitConverter.ToUInt32(peer.Buffer, 0);
            string message = null;
            switch (id)
            {
                case PipedAssetProvider.LoadAssetPacketID:
                    string relativePath = peer.StreamReader.ReadBibimString();

                    // Asset Binary를 전송할 Pipe의 이름을 알려줍니다.
                    // 단순히 Unique한 이름을 가져오기 위해 GUID를 이용하였습니다.
                    string guid = Guid.NewGuid().ToString();
                    peer.StreamWriter.WriteBibimString(guid);

                    BeginCook(peer.Directory, relativePath,
                              (buffer, index, count) =>
                              {
                                  NamedPipeServerStream stream = new NamedPipeServerStream(guid,
                                                                                           PipeDirection.Out,
                                                                                           NamedPipeServerStream.MaxAllowedServerInstances,
                                                                                           PipeTransmissionMode.Byte,
                                                                                           PipeOptions.Asynchronous);

                                  stream.BeginWaitForConnection((waitResult) =>
                                                                {
                                                                    stream.EndWaitForConnection(waitResult);
                                                                    stream.BeginWrite(buffer, 0, count,
                                                                                      (r) =>
                                                                                      {
                                                                                          try
                                                                                          {
                                                                                              stream.EndWrite(r);
                                                                                          }
                                                                                          catch (Exception ex)
                                                                                          {
                                                                                              Trace.WriteLine(ex);
                                                                                          }

                                                                                          stream.Disconnect();
                                                                                          stream.Dispose();
                                                                                      },
                                                                                      null);
                                                                },
                                                                null);
                              },
                              () =>
                              {
                                  // Asset 가공이나 전송을 실패하더라도,
                                  // 일단 Client와 접속하여 "ClassID = 0"을 전송하여 실패를 알려줍니다.

                                  NamedPipeServerStream stream = new NamedPipeServerStream(guid,
                                                                                           PipeDirection.Out,
                                                                                           NamedPipeServerStream.MaxAllowedServerInstances,
                                                                                           PipeTransmissionMode.Byte,
                                                                                           PipeOptions.Asynchronous);
                                  stream.BeginWaitForConnection((waitResult) =>
                                                                {
                                                                    stream.EndWaitForConnection(waitResult);
                                                                    byte[] zeroInteger = { 0, 0, 0, 0 };
                                                                    stream.Write(zeroInteger, 0, zeroInteger.Length);
                                                                    stream.WaitForPipeDrain();
                                                                    stream.Disconnect();
                                                                    stream.Dispose();
                                                                },
                                                                null);
                              });

                    message = string.Format("[{0}:{1}] Received LoadAssetPacket. {2}\n\tAssetPipe opened. ({3}).", peer.Name, peer.ID, relativePath, guid);
                    break;
                case PipedAssetProvider.ChangeClientNamePacketID:
                    string oldName = peer.Name;
                    peer.Name = peer.StreamReader.ReadBibimString();
                    message = string.Format("[{0}:{1}] Received ChangeClientName. {2} => {3}", peer.Name, peer.ID, oldName, peer.Name);
                    break;
            }

            // 다시 새로운 Packet ID를 받기 위해 비동기 읽기 작업을 수행합니다.
            peer.Stream.BeginRead(peer.Buffer, 0, 4, new AsyncCallback(OnPeerRead), peer);

            if (string.IsNullOrEmpty(message) == false)
                Trace.WriteLine(message);
        }
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

            public string Directory
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
        }
        #endregion
    }
}
