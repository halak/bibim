using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using Bibim;
using Bibim.IO;

namespace Bibim.Asset.Pipeline
{
    [ClassID('N', 'A', 'S', 'S')]
    public sealed class NetworkGameAssetServer : GameAssetServer
    {
        #region Fields
        private Socket serverSocket;
        #endregion

        #region Constructor
        public NetworkGameAssetServer()
            : this(null, NetworkAssetProvider.DefaultPort)
        {
        }

        public NetworkGameAssetServer(GameAssetKitchen kitchen)
            : this(kitchen, NetworkAssetProvider.DefaultPort)
        {
        }

        public NetworkGameAssetServer(GameAssetKitchen kitchen, int port)
            : base(kitchen)
        {
            serverSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp)
            {
                NoDelay = true
            };
            serverSocket.Bind(new IPEndPoint(IPAddress.Any, port));
            serverSocket.Listen(100);

            Ready();
        }
        #endregion

        #region Methods
        private void Ready()
        {
            serverSocket.BeginAccept(new AsyncCallback(OnClientRequested), null);
        }

        private void OnClientRequested(IAsyncResult result)
        {
            if (result.IsCompleted == false)
            {
                Ready();
                return;
            }

            var clientSocket = serverSocket.EndAccept(result);

            Ready();

            try
            {
                var clientStream = new NetworkStream(clientSocket);
                var reader = new BinaryReader(clientStream);
                string clientName = reader.ReadBibimString();
                string workingDirectory = reader.ReadBibimString();
                string assetName = reader.ReadBibimString();
                reader.Dispose();

                Trace.TraceInformation(string.Format("[{0}] {1}", clientName, assetName));

                BeginCook(workingDirectory,
                          assetName,
                          (buffer, index, count) => SendAssetData(clientSocket, buffer, index, count),
                          () => SendAssetData(clientSocket, null, 0, 0) );
            }
            catch (Exception ex)
            {
                Trace.WriteLine(ex);
            }
        }

        private void SendAssetData(Socket socket, byte[] data, int index, int count)
        {
            if (data == null)
            {
                data = new byte[] { 0, 0, 0, 0 };
                index = 0;
                count = data.Length;
            }

            try
            {
                socket.BeginSend(data, index, count, SocketFlags.None,
                                 (r) =>
                                 {
                                     SocketError error = SocketError.SocketError;
                                     int bytesSent = socket.EndSend(r, out error);
                                     if (bytesSent != count)
                                     {
                                         Trace.TraceWarning("ERROR {0} (sent: {1} bytes)", error, bytesSent);
                                     }
                                     socket.Disconnect(false);
                                 }, null);
            }
            catch (Exception ex)
            {
                Trace.WriteLine(ex);
            }
        }
        #endregion
    }
}
