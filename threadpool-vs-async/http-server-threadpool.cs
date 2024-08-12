using System.Net;
using System.Text;
using System.Threading;

namespace ConsoleApp
{
    public class HttpServer : IDisposable
    {

        private readonly HttpListener listener = new HttpListener();

        private readonly int port;

        public string Hostname { get; set; } = "localhost";

        public string Scheme { get; set; }= "http";

        public HttpServer(int port)
        {

            this.port = port;
        }

        public string BaseUrl
        {
            get { return BuildUri(); }
        }

        public void Run()
        {

            listener.Prefixes.Add(BaseUrl);
            listener.Start();

            ThreadPool.QueueUserWorkItem((o) =>
            {
                Console.WriteLine("Webserver running...");
                try
                {
                    while (listener.IsListening)
                    {
                        ThreadPool.QueueUserWorkItem((c) =>
                        {
                            var ctx = c as HttpListenerContext;
                            try
                            {
                                ProcessRequest(ctx);
                            }
                            catch { } // suppress any exceptions
                            finally
                            {
                                // always close the stream
                                ctx.Response.OutputStream.Close();
                            }
                        }, listener.GetContext());
                    }
                }
                catch { } // suppress any exceptions
            });
        }

        public void Stop()
        {
            listener.Stop();
            listener.Close();
        }

        private string BuildUri(string path = "", string query = "")
        {            
            return new UriBuilder(Scheme, Hostname, port, path, query).ToString();
        }

        private void ProcessRequest(HttpListenerContext ctx)
        {
            try
            {
                Thread.Sleep(100);
                string response = "threads";
                Respond200(ctx, response);
            }
            catch (Exception)
            {
                Respond500(ctx);
            }
        }

        public void Respond200(HttpListenerContext ctx, string content)
        {
            ctx.Response.StatusCode = 200;
            ctx.Response.StatusDescription = "The request was fulfilled.";
            byte[] buf = Encoding.UTF8.GetBytes(content);
            ctx.Response.ContentLength64 = buf.Length;
            ctx.Response.OutputStream.Write(buf, 0, buf.Length);
        }

        public void Respond404(HttpListenerContext ctx)
        {
            ctx.Response.StatusCode = 404;
            ctx.Response.StatusDescription = "The server has not found anything matching the URI given.";
        }

        public void Respond500(HttpListenerContext ctx)
        {
            ctx.Response.StatusCode = 500;
            ctx.Response.StatusDescription = "The server encountered an unexpected condition which prevented it from fulfilling the request.";
        }

        #region IDisposable Support

        private bool disposed = false; // To detect redundant calls
        private string hostname;
        private string _scheme;

        protected virtual void Dispose(bool disposing)
        {
            if (!disposed)
            {
                if (disposing)
                {
                    if (listener.IsListening)
                        Stop();
                }

                disposed = true;
            }
        }

        public void Dispose()
        {
            // Do not change this code. Put cleanup code in Dispose(bool disposing) above.
            Dispose(true);
        }

        #endregion
    }

    class Program {
        static void Main(string[] args) {
            Console.WriteLine("Starting HttpServer...");
            int workerThreads;
            int portThreads;
            ThreadPool.GetMaxThreads(out workerThreads, out portThreads);
            Console.WriteLine("{0}, {1}", workerThreads, portThreads);


            var server = new HttpServer(4221);
            server.Run();

            Console.WriteLine("HttpServer started.");
            Console.WriteLine("Listening at {0}", server.BaseUrl);
            Console.WriteLine();
            Console.WriteLine("Press <Enter> to exit");
            Console.ReadLine();

            server.Stop();

        }
    }
}