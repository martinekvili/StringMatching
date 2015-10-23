using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SuffixArrayAlgorithm
{

    public abstract class ComparerBase
    {
        protected string str;
        protected string pattern;
        protected int[] substringArray;

        protected abstract int checkIfValid(int num);

        public ComparerBase(string s, string p, int[] ssA)
        {
            str = s;
            pattern = p;
            substringArray = ssA;
        }

        public int Compare(int num)
        {
            int comp = String.Compare(str, substringArray[num], pattern, 0, pattern.Length);
            if (comp != 0)
            {
                return comp;
            }
            else
            {
                return checkIfValid(num);
            }
        }
    }

    public class FirstOccurenceComparer : ComparerBase
    {
        protected override int checkIfValid(int num)
        {
            if (num == 0 || String.Compare(str, substringArray[num - 1], pattern, 0, pattern.Length) != 0)
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }

        public FirstOccurenceComparer(string s, string p, int[] ssA) : base(s, p, ssA) { }
    }

    public class LastOccurenceComparer : ComparerBase
    {
        protected override int checkIfValid(int num)
        {
            if (num == str.Length - 1 || String.Compare(str, substringArray[num + 1], pattern, 0, pattern.Length) != 0)
            {
                return 0;
            }
            else
            {
                return -1;
            }
        }

        public LastOccurenceComparer(string s, string p, int[] ssA) : base(s, p, ssA) { }
    }

}
