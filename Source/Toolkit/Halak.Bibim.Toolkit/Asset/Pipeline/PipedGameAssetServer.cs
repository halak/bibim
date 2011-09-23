using System;
using System.Collections.Generic;
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
        private struct Connection
        {
            public Thread Thread;
            public NamedPipeServerStream Stream;
            public BinaryReader Reader;
            public byte[] Buffer;
        }
        private List<Connection> connections;
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

                    foreach (Connection item in connections)
                    {
                    }

                    connections.Clear();

                    if (string.IsNullOrEmpty(pipeName) == false)
                        AllocateConnection();
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
            this.connections = new List<Connection>();

            if (string.IsNullOrEmpty(pipeName) == false)
                AllocateConnection();
        }
        #endregion

        #region Methods
        private void AllocateConnection()
        {
            Connection connection = new Connection();
            connection.Stream = new NamedPipeServerStream(pipeName, PipeDirection.InOut,
                                                          NamedPipeServerStream.MaxAllowedServerInstances,
                                                          PipeTransmissionMode.Byte,
                                                          PipeOptions.Asynchronous);
            connection.Reader = new BinaryReader(connection.Stream);
            connection.Buffer = new byte [4096];
            connection.Stream.BeginWaitForConnection(new AsyncCallback(OnConnected), connection);
            connections.Add(connection);
        }

        #region Connection-Handlers
        private void OnConnected(IAsyncResult result)
        {
            if (result.IsCompleted)
            {
                Connection connection = (Connection)result.AsyncState;
                try
                {
                    connection.Stream.WaitForConnection();
                    connection.Stream.BeginRead(connection.Buffer, 0, 4, new AsyncCallback(OnRead), connection);
                }
                catch (Exception e)
                {

                }
            }
            else
            {
            }
        }

        private void OnRead(IAsyncResult result)
        {
            if (result.IsCompleted)
            {
                Connection connection = (Connection)result.AsyncState;
                uint id = BitConverter.ToUInt32(connection.Buffer, 0);
                switch (id)
                {
                    case 1000:
                        string path = connection.Reader.ReadBibimString();
                        object asset = Kitchen.Cook(path);
                        if (asset != null)
                        {
                            GameAssetWriter writer = GameAssetWriter.CreateWriter(asset.GetType());
                            MemoryStream ms = new MemoryStream();
                            AssetStreamWriter assetWriter = new AssetStreamWriter(ms, null);
                            writer.Write(assetWriter, asset);

                            NamedPipeServerStream serverStream = new NamedPipeServerStream(pipeName + "_" + "ASSET", PipeDirection.Out,
                                                   NamedPipeServerStream.MaxAllowedServerInstances,
                                                   PipeTransmissionMode.Byte,
                                                   PipeOptions.Asynchronous);
                            serverStream.WaitForConnection();
                            serverStream.BeginWrite(ms.GetBuffer(), 0, (int)ms.Length, new AsyncCallback(OnAssetWritten), serverStream);
                            ms.Close();
                        }
                        break;
                }
            }
            else
            {
            }
        }

        private void OnAssetWritten(IAsyncResult result)
        {
            NamedPipeServerStream stream = (NamedPipeServerStream)result.AsyncState;
            stream.Flush();
            stream.Disconnect();
            stream.Close();
        }
        #endregion
        #endregion
    }
}
