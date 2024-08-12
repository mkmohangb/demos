```

BenchmarkDotNet v0.13.12, Windows 11 (10.0.22621.3958/22H2/2022Update/SunValley2)
AMD Ryzen 7 5700U with Radeon Graphics, 1 CPU, 16 logical and 8 physical cores
.NET SDK 8.0.302
  [Host]     : .NET 8.0.6 (8.0.624.26715), X64 RyuJIT AVX2
  DefaultJob : .NET 8.0.6 (8.0.624.26715), X64 RyuJIT AVX2


```
| Method   | Mean      | Error    | StdDev   | Allocated |
|--------- |----------:|---------:|---------:|----------:|
| LinqSum  |  68.20 μs | 0.924 μs | 0.721 μs |         - |
| NaiveSum | 308.71 μs | 6.065 μs | 6.985 μs |       2 B |
| SimdSum  |  75.50 μs | 2.714 μs | 7.520 μs |         - |
