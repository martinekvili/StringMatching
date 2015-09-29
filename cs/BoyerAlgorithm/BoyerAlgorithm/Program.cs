using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BoyerAlgorithm
{
    class Program
    {
        static void Main(string[] args)
        {
            string s = "i had to, Hence, i peed the fence. i don't see the adHence";
	        string pat = "ence";
	        MatchAbleString str = new MatchAbleString(s);
            Pattern p = new Pattern(pat);
            p.PreProcess();

	        List<int> l = str.Match(p, false);

            foreach (int i in l)
	        {
                Console.WriteLine(i + " : " + s.Substring(i, pat.Length));
	        }

            Console.ReadKey();
        }
    }
}
