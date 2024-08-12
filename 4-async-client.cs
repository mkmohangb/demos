// https://stackoverflow.com/questions/56245509/start-async-task-now-await-later/56303970
class Program {

    static async Task<int> DoIoBoundWorkAsync() {
        Console.WriteLine("Make API call...");
        await Task.Delay(2000).ConfigureAwait(false); // non-blocking async call
        Console.WriteLine("Data back.");
        return 1;
    }

    static int DoCpuIntensizeCalc() {
        Console.WriteLine("Do smart calc...");
        Thread.Sleep(2000);  // blocking call. e.g. a spinning loop
        Console.WriteLine("Calc finished.");
        return 2;
    }

    static async Task Main() {

        var watch = System.Diagnostics.Stopwatch.StartNew();
        var ioBoundTask = DoIoBoundWorkAsync();
        int cpuBoundResult = DoCpuIntensizeCalc();
        int ioBoundResult = await ioBoundTask.ConfigureAwait(false);
        watch.Stop();
    
        Console.WriteLine($"The result is {cpuBoundResult + ioBoundResult}");
        Console.WriteLine($"Time taken is {watch.ElapsedMilliseconds} ");
    }

}
