using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SuffixArrayAlgorithm
{
    public class MatchAbleString
    {
        private string original;
        private int[] substringArray;

        private int binarySearch(int min, int max, ComparerBase comparer)
        {
            int num = (min + max) / 2;

            switch (comparer.Compare(num))
            {
                case 0:
                    return num;
                case -1:
                    return binarySearch(num + 1, max, comparer);
                case 1:
                    return binarySearch(min, num, comparer);
                default:
                    throw new InvalidOperationException("Not possible to get here - theoretically.");
            }
        }

        public MatchAbleString(string orig)
        {
            original = orig;
            substringArray = new int[original.Length];

            for (int i = 0; i < substringArray.Length; i++)
            {
                substringArray[i] = i;
            }
        }

        public void PreProcess(bool parallel = false)
        {
            MergeSort<int>.Comparator comp = (int one, int other) =>
            {
                return String.Compare(original, one, original, other, original.Length);
            };

            if (!parallel)
            {
                //Array.Sort(substringArray);
            }
            else
            {
                MergeSort<int>.ParallelSort(substringArray, comp);
            }
        }

        public List<int> Match(string pattern)
        {
            ComparerBase foc = new FirstOccurenceComparer(original, pattern, substringArray);
            ComparerBase loc = new LastOccurenceComparer(original, pattern, substringArray);

            int first = binarySearch(0, original.Length, foc);
            int last = binarySearch(0, original.Length, loc);

            if (first == -1)
            {
                return new List<int>();
            }
            else
            {
                List<int> tmp = new List<int>();

                for (int i = first; i <= last; i++)
                {
                    tmp.Add(substringArray[i]);
                }

                tmp.Sort();

                return tmp;
            }
        }
    }
}
