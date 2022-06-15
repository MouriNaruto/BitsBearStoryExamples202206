using Microsoft.Dism;

namespace ImageBuilder
{
    internal class Program
    {
        static void Main(string[] args)
        {
            try
            {
                DismApi.Initialize(DismLogLevel.LogErrors);
            }
            finally
            {
                DismApi.Shutdown();
            }
        }
    }
}
