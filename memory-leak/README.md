  - Memory leak scenario from [here](https://github.com/dotnet/samples/tree/main/core/diagnostics/DiagnosticScenarios)

  - ```dotnet-counters ps```
  - ```dotnet-counters monitor -p <pid>```
  - ```dotnet-dump  collect -p <pid>```
  - ```dotnet-dump analyze <dump file>```
     ```
       - dumpheap -stat
       - dumpheap -mt
       - gcroot <addr>
     ```
