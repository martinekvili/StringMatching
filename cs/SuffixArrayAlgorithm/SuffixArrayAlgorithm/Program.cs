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

        static void Main(string[] args)
        {
            measureSimple();
        }
    }
}
