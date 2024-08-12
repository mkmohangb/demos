using System;
using System.Linq;
using BenchmarkDotNet;
using BenchmarkDotNet.Attributes;

namespace benchmark
{
    [MemoryDiagnoser]
    public class Benchmarks
    {
        private const int MaxValue = 1_000;
        private const int ArraySize = 1_000_000;

        private Random _random;
        private int[] _array;

        [GlobalSetup]
        public void Setup()
        {
            _random = new Random();
            _array = Enumerable.Range(0, ArraySize)
                .Select(_ => _random.Next(0, MaxValue))
                .ToArray();
        }

        [Benchmark]
        public void LinqSum()
        {
            ArrayOperations.LinqSum(_array);
        }

        [Benchmark]
        public void NaiveSum()
        {
            ArrayOperations.NaiveSum(_array);
        }

        [Benchmark]
        public void SimdSum()
        {
            ArrayOperations.SimdSum(_array);
        }
    }
}
