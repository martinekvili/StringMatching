using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BoyerAlgorithm
{
    class Program
    {
        //static void Main(string[] args)
        //{
        //    string s = "i had to, Hence, i peed the fence. i don't see the adHence";
        //    string pat = "ence";
        //    MatchAbleString str = new MatchAbleString(s);
        //    Pattern p = new Pattern(pat);
        //    p.PreProcess();

        //    List<int> l = str.Match(p, false);

        //    foreach (int i in l)
        //    {
        //        Console.WriteLine(i + " : " + s.Substring(i, pat.Length));
        //    }

        //    Console.ReadKey();
        //}

        static private long measure(string orig, string pat, bool parallel, int num)
        {
            Stopwatch sw = new Stopwatch();
	        List<int> l = null;

	        MatchAbleString str = new MatchAbleString(orig);

            sw.Start();     // mérés indul

	        for (int i = 0; i < 5 * num; i++) 
            {
		        Pattern p = new Pattern(pat);
  
		        p.PreProcess();
		        l = str.Match(p, parallel);
	        }

            sw.Stop();      // mérés vége
            long elapsed = sw.ElapsedMilliseconds;

            //Console.WriteLine((parallel ? "Parallel" : "Single thread") + " matching took " + (elapsed / 1000) + " s " + (elapsed % 1000) + " ms");
            //Console.WriteLine("Found " + l.Count + " matches.");

	        return elapsed / 5;
        }

        static void Main(string[] args)
        {
            string path = "..\\..\\..\\..\\..\\resources\\" + args[0];
            //string path = "..\\..\\..\\..\\..\\resources\\spacewrecked.txt";
            string str = File.ReadAllText(path);

            string orig = str;
            for (int i = 0; i < 63; i++)
            {
                orig += str;
            }

            Console.Write(orig.Length + ";");

            //int num = Int32.Parse(args[2]);
            //Console.Write(num + ";");

            Console.Write(measure(orig, args[1], false, 1000) + ";");
            Console.WriteLine(measure(orig, args[1], true, 1000) + ";");
            //Console.Write(measure(orig, "plentifully", false, 1000) + ";");
            //Console.WriteLine(measure(orig, "plentifully", true, 1000) + ";");
        }
    }
}
