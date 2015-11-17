using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MatchableString
{
    public class Program
    {
        private delegate MatchableString CreatorFunction(string s);

        private static long measure(string orig, string pat, bool parallel, int matchNum, CreatorFunction func)
        {
            List<int> l = null;
            Stopwatch sw = new Stopwatch();

            sw.Start();                             // mérés indul 

            for (int i = 0; i < 5; i++)
            {
                var str = func(orig);
                str.PreProcess(parallel);

                for (int j = 0; j < matchNum; j++)
                {
                    Pattern p = new Pattern(pat);
                    l = str.Match(p, parallel);
                }
            }

            sw.Stop();	// mérés vége
            long elapsed = sw.ElapsedMilliseconds / 5;

            //Console.WriteLine((parallel ? "Parallel" : "Single thread") + " matching took " + (elapsed / 1000) + " s " + (elapsed % 1000) + " ms");
            //Console.WriteLine("Found " + l.Count + " matches.");

            return elapsed;
        }

        private static void measureReadFile(string[] args)
        {
            string path = "..\\resources\\" + args[1];

            int multiplier = int.Parse(args[3]);
            int matchNum = int.Parse(args[4]);

            string orig = File.ReadAllText(path);

            string str = orig;
            for (int i = 0; i < multiplier - 1; i++)
            {
                str += orig;
            }

            Console.Write(str.Length + ";");

            if (args[0] == "both")
            {
                Console.Write(matchNum + ";");

                Console.Write(measure(str, args[2], true, matchNum, MatchableStrings.CreateBoyer) + ";");
                Console.WriteLine(measure(str, args[2], true, matchNum, MatchableStrings.CreateSuffixArray));
            }
            else
            {
                CreatorFunction func = (args[0] == "boyer") ?
                   new CreatorFunction(MatchableStrings.CreateBoyer) :
                   new CreatorFunction(MatchableStrings.CreateSuffixArray);
                
                Console.Write(measure(str, args[2], false, matchNum, func) + ";");
                Console.WriteLine(measure(str, args[2], true, matchNum, func));
            }
        }

        private static void measureSimple(CreatorFunction func)
        {
            string orig = "i had to, Hence, i peed the fence. i don't see the adHence";
            MatchableString sm = func(orig);
            sm.PreProcess(true);

            string pat = "ence";
            Pattern p = new Pattern(pat);
            List<int> h = sm.Match(p, true);

            foreach (var i in h)
            {
                Console.WriteLine(i + " : " + orig.Substring(i, pat.Length));
            }

            Console.ReadKey();
        }

        public static void Main(string[] args)
        {
            //measureSimple(MatchableStrings.CreateBoyer);
            //measureSimple(MatchableStrings.CreateSuffixArray);

            measureReadFile(args);
        }
    }
}
