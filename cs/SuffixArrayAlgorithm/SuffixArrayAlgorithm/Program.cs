using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SuffixArrayAlgorithm
{
    class Program
    {
        private static void measureSimple()
        {
            string orig = "i had to, Hence, i peed the fence. i don't see the adHence";
            MatchAbleString sm = new MatchAbleString(orig);
            sm.PreProcess(true);

            string pat = "ence";
            List<int> h = sm.Match(pat);

            foreach (var i in h)
            {
                Console.WriteLine(i + " : " + orig.Substring(i, pat.Length));
            }

            Console.ReadKey();
        }

        static private long measure(string orig, string pat, bool parallel)
        {
            Stopwatch sw = new Stopwatch();
            sw.Start();     // mérés indul

            for (int i = 0; i < 5; i++)
            {
                MatchAbleString str = new MatchAbleString(orig);
                str.PreProcess(parallel);
                var l = str.Match(pat);
            }

            sw.Stop();      // mérés vége

            long elapsed = sw.ElapsedMilliseconds / 5;

            //Console.WriteLine((parallel ? "Parallel" : "Single thread") + " matching took " + (elapsed / 1000) + " s " + (elapsed % 1000) + " ms");
            //Console.WriteLine("Found " + l.Count + " matches.");

            return elapsed;
        }

        private static void measureFileRead(string[] args)
        {
            string path = @"..\resources\" + args[0];
            string orig = File.ReadAllText(path);

            Console.Write(orig.Length + ";");

            Console.Write(measure(orig, args[1], false) + ";");
            Console.WriteLine(measure(orig, args[1], true) + ";");
            //Console.Write(measure(orig, "alrightness", false, 1) + ";");
            //Console.WriteLine(measure(orig, "alrightness", true, 1) + ";");
        }

        static void Main(string[] args)
        {
            //measureSimple();

            measureFileRead(args);
            //Console.ReadKey();
        }
    }
}
