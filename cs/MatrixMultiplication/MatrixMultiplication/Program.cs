using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.IO;

namespace MatrixMultiplication
{
    class Program
    {
        private static Random random = new Random();

        private static int maxNum = 100;

        public static int randomInt()
        {
            return random.Next(maxNum);
        }

        private static void printMatrix(Matrix<int> m) {
            for (int i = 0; i < m.getSize(); i++) {
                for (int j = 0; j < m.getSize(); j++) {
                    Console.Write(m.get(i, j) + " ");
                }
                Console.WriteLine();
            }
            Console.WriteLine();
        }

        static long measurement(int size, bool parallel)
        {
            long[] times = new long[5];

            Console.Write("Starting measurement ( ");
            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.Write(parallel ? "parallel " : "non-parallel ");
            Console.ResetColor();
            Console.WriteLine("algorithm, " + size + " × " + size + " matrices )\n");   

            for (int i = 0; i < 5; i++)
            {
                Matrix<int> m1 = new Matrix<int>(size, true, randomInt);
                Matrix<int> m2 = new Matrix<int>(size, true, randomInt);

                Console.Write("Measurement number " + (i + 1) + "... ");

                Stopwatch watch = new Stopwatch();
                watch.Start();

                Matrix<int> m3 = Multiplicator.multiply(m1, m2, parallel);
                watch.Stop();

                Console.ForegroundColor = ConsoleColor.Green;
                Console.Write("DONE");
                Console.ResetColor();
                Console.WriteLine(" ( " + watch.ElapsedMilliseconds / 1000 + " s " + watch.ElapsedMilliseconds % 1000 + " ms )");
                   
                times[i] = watch.ElapsedMilliseconds;         
            }

            Console.WriteLine();

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
            if (args.Length < 2)
            {
                return;
            }
            int size = Int32.Parse(args[0]);
            bool inFile = (args[1].Equals("file"));
            bool first = false;

            if (inFile)
            {
                first = (args[2].Equals("first"));
            }

            long time1 = measurement(size, false);
            //long time1 = 0;

            Console.WriteLine("Matrix multiplication took on average " + time1 / 1000 + " seconds and " + time1 % 1000 + " milliseconds.\n");

            
            long time2 = measurement(size, true);

            Console.WriteLine("Matrix multiplication took on average " + time2 / 1000 + " seconds and " + time2 % 1000 + " milliseconds.\n");

            if (inFile)
            {
                using (StreamWriter writer = new StreamWriter("data.csv", !first))
                {
                    writer.WriteLine(size + ";" + time1 + ";" + time2 + ";");
                }
            }
        }
    }
}
