using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StringMatch
{
    public class StringMatch : IComparer<int>
    {
        private string original;
        //private string[] substringCache;
        private int[] substringArray;

        public StringMatch(string orig)
        {
            original = orig;

            substringArray = new int[original.Length];
            for (int i = 0; i < substringArray.Length; i++)
            {
                substringArray[i] = i;
            }

            //substringCache = new string[original.Length];
            //for (int i = 0; i < substringArray.Length; i++)
            //{
            //    substringCache[i] = original.Substring(i);
            //}
        }

        public int Compare(int x, int y)
        {
            return String.Compare(original.Substring(x), original.Substring(y)/*, StringComparison.OrdinalIgnoreCase*/);
            //return String.Compare(substringCache[x], substringCache[y], StringComparison.OrdinalIgnoreCase);
            //return substringCache[x].CompareTo(substringCache[y]);
        }

        public void preprocess()
        {
            ArraySorter.sort(substringArray, original, new MyStringComparer(original, substringArray), 3);
            //ArraySorter.sort(substringArray, original, this, 0);
            //Array.Sort(substringArray, this);
        }

        private int binarySearch(int min, int max, string pattern, ComparerBase cb)
        {
            if (min == max) {
                return -1;
            }

            int num = (min + max) / 2;

            switch (cb.compare(num))
            {
                case 0:
                    return num;
                case -1:
                    return binarySearch(num + 1, max, pattern, cb);
                case 1:
                    return binarySearch(min, num, pattern, cb);
                default:
                    throw new Exception();
            }
        }

        public int[] match(string pattern)
        {
            int first = binarySearch(0, substringArray.Length, pattern, new FirstOccurenceComparer(original, pattern, substringArray));
            int last = binarySearch(0, substringArray.Length, pattern, new LastOccurenceComparer(original, pattern, substringArray));

            if (first == -1)
            {
                return null;
            }
            else
            {
                int[] occurrences = new int[last - first + 1];
                for (int i = 0; i <= last - first; i++)
                {
                    occurrences[i] = substringArray[first + i];
                }
                return occurrences;
            }
        }

        public void print()
        {
            for (int i = 0; i < substringArray.Length; i++)
            {
                Console.WriteLine(original.Substring(substringArray[i]));
            }
        }
    }
}
