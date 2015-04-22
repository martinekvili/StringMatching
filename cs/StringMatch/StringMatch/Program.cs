using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StringMatch
{

// TODO: asszem perpill csak 8-cal osztható hosszúságú stringekre fog működni.
//       ezzel majd kezdeni kell valamit alkalomadtán

    public class Program
    {
        static void Main(string[] args)
        {
            //string orig = "CGATATATCGG";
            string orig = File.ReadAllText("english.txt");
            for (int i = 0; i < 5; i++)
            {
                orig += File.ReadAllText("english.txt");
            }
            //    //orig += File.ReadAllText("szoveg.txt", Encoding.UTF8);
            //    //orig += File.ReadAllText("szoveg.txt", Encoding.UTF8);
            //    //orig += File.ReadAllText("szoveg.txt", Encoding.UTF8);
            //    Console.WriteLine(orig.Length);

                StringMatch sm = new StringMatch(orig);

                Stopwatch sw = new Stopwatch();

                sw.Start();
                sm.preprocess();
                sw.Stop();

                Console.WriteLine("Preprocessing took " + sw.Elapsed.Seconds + " s " + sw.Elapsed.Milliseconds + " ms\n");

                sw.Restart();
                int[] occ = sm.match("commit");
                sw.Stop();

                Console.WriteLine("Searching took " + sw.Elapsed.Seconds + " s " + sw.Elapsed.Milliseconds + " ms\n");

                if (occ != null)
                {
                    Console.WriteLine(occ.Length + " occurences found.");
                    //foreach (int o in occ)
                    //{
                    //    Console.WriteLine(o + ": " + orig.Substring(o, "commit".Length));
                    //}
                }
                else
                {
                    Console.WriteLine("No match!");
                }

            //sm.print();

            Console.ReadKey();
        }
    }
}
