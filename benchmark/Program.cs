using BenchmarkDotNet.Configs;
using BenchmarkDotNet.Running;
using System.Numerics;
using System;

namespace benchmark
{
    public class Program
    {
        public static void Main(string[] args)
        {
            var config = DefaultConfig.Instance;
            var summary = BenchmarkRunner.Run<Benchmarks>(config, args);
            Console.WriteLine(Vector<int>.Count);

            // Use this to select benchmarks from the console:
            // var summaries = BenchmarkSwitcher.FromAssembly(typeof(Program).Assembly).Run(args, config);
        }
    }
}