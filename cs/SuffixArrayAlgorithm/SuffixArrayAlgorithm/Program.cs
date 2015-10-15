using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SuffixArrayAlgorithm
{
    class Program
    {
        static void Main(string[] args)
        {
            int[] arr = new int[10000000];
            Stopwatch sw = new Stopwatch();
            Random r = new Random();

            for (int i = 0; i < arr.Length; i++)
            {
                arr[i] = r.Next(1000);
            }

            sw.Start();

            //Array.Sort(arr);
            MergeSort<int>.ParallelSort(arr, (int one, int other) =>
            {
                if (one < other)
                {
                    return -1;
                }
                else if (one > other)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            });

            sw.Stop();

            Console.WriteLine(sw.ElapsedMilliseconds);
            Console.ReadKey();
        }
    }
}
