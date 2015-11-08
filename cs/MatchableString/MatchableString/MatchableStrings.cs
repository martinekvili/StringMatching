using MatchableString.Boyer;
using MatchableString.SuffixArray;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MatchableString
{
    public static class MatchableStrings
    {
        public static MatchableString CreateBoyer(string s)
        {
            return new MatchableStringB(s);
        }

        public static MatchableString CreateSuffixArray(string s)
        {
            return new MatchableStringSA(s);
        }
    }
}
