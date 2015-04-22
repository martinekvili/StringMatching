using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.IO;

namespace ParallelSort
{
    class Program
    {
        static long measurement(int size, int depth, bool verbose)
        {
            long[] times = new long[5];

            if (verbose)
            {
                Console.Write("Starting measurement ( ");
                Console.ForegroundColor = ConsoleColor.Yellow;
                Console.Write((depth > 0) ? "parallel - " + Math.Pow(2, depth) + " pieces " : "non-parallel ");
                Console.ResetColor();
                Console.WriteLine("algorithm, size of the array: " + (double)size / 1000000 + " M )\n");
            }
            
            for (int i = 0; i < times.Length; i++)
            {
                IntArray array = new IntArray(size, true);

                if (verbose)
                {
                    Console.Write("Measurement number " + (i + 1) + "... ");
                }

                Stopwatch watch = new Stopwatch();
                watch.Start();

                array.sort(depth);
                watch.Stop();

                if (verbose)
                {
                    Console.ForegroundColor = ConsoleColor.Green;
                Console.Write("DONE");
                Console.ResetColor();
                Console.WriteLine(" ( " + watch.ElapsedMilliseconds / 1000 + " s " + watch.ElapsedMilliseconds % 1000 + " ms )");
                }

                times[i] = watch.ElapsedMilliseconds;
            }

            if (verbose)
            {
                Console.WriteLine();
            }

            long average = 0;
            foreach (long t in times)
            {
                average += t;
            }
            average /= times.Length;

            return average;
        }

        static void Main(string[] args)
        {
            if (args.Length < 1)
            {
                return;
            }
            int size = Int32.Parse(args[0]);
            bool verbose = (args.Length > 1 && args[1].Equals("-v"));

            long[] times = new long[7];

            for (int i = 0; i < 7; i++)
            {
                times[i] = measurement(size, i, verbose);
                if (verbose)
                {
                    Console.WriteLine("Sorting took on average " + times[i] / 1000 + " seconds and " + times[i] % 1000 + " milliseconds.\n");
                }  
            }

            if (!verbose)
            {
                Console.Write((double) size / 1000000 + ";");
                foreach (long time in times)
                {
                    Console.Write(time + ";");
                }
                Console.WriteLine();
            }
        }
    }
}
