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
        private bool isPreProcessed;

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
                    throw new NotImplementedException("Not possible to get here - theoretically.");
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

            isPreProcessed = false;
        }

        public void PreProcess(bool parallel = false)
        {
            IComparer<int> comp = new MergeSort.Comparer(original);

            if (!parallel)
            {
                Array.Sort(substringArray, comp);
            }
            else
            {
                MergeSort.ParallelSort(substringArray, comp);
            }

            isPreProcessed = true;
        }

        public List<int> Match(string pattern)
        {
            if (!isPreProcessed)
            {
                throw new InvalidOperationException("This MatchAbleString hasn't been preprocessed yet!");
            }

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
