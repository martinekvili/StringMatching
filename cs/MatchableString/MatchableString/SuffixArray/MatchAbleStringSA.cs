using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MatchableString.SuffixArray
{
    public class MatchableStringSA : MatchableString
    {
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

        public MatchableStringSA(string orig) : base(orig)
        {
            substringArray = new int[Str.Length];

            for (int i = 0; i < substringArray.Length; i++)
            {
                substringArray[i] = i;
            }

            isPreProcessed = false;
        }

        public override void PreProcess(bool parallel)
        {
            IComparer<int> comp = new MergeSort.Comparer(Str);

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

        public override List<int> Match(Pattern pattern, bool parallel)
        {
            if (!isPreProcessed)
            {
                throw new InvalidOperationException("This MatchAbleString hasn't been preprocessed yet!");
            }

            ComparerBase foc = new FirstOccurenceComparer(Str, pattern.Str, substringArray);
            ComparerBase loc = new LastOccurenceComparer(Str, pattern.Str, substringArray);

            int first = binarySearch(0, Str.Length, foc);
            int last = binarySearch(0, Str.Length, loc);

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
