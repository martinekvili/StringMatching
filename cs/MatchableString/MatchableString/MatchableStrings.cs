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
        /// <summary>
        /// Choices for the approximate number of matches.
        /// </summary>
        public enum NumberOfMatches
        {
            /// <summary>
            /// This object will be used for less than 1000 matches.
            /// </summary>
            LessThan1000,

            /// <summary>
            /// This object will be used for more than 1000 matches.
            /// </summary>
            MoreThan1000
        }

        /// <summary>
        /// Creates a matchable string object using Boyer-Moore algorithm.
        /// </summary>
        /// <param name="s">The main text to match patterns on.</param>
        /// <returns>A matchable string object.</returns>
        public static MatchableString CreateBoyer(string s)
        {
            return new MatchableStringB(s);
        }

        /// <summary>
        /// Creates a matchable string object using Suffix Array algorithm.
        /// </summary>
        /// <param name="s">The main text to match patterns on.</param>
        /// <returns>A matchable string object.</returns>
        public static MatchableString CreateSuffixArray(string s)
        {
            return new MatchableStringSA(s);
        }

        /// <summary>
        /// Creates a matchable string object with a suitable implementation.
        /// </summary>
        /// <param name="s">The main text to match patterns on.</param>
        /// <param name="approx">The approximate number of uses.</param>
        /// <returns>A matchable string object.</returns>
        public static MatchableString Create(string s, NumberOfMatches approx)
        {
            switch (approx)
            {
                case NumberOfMatches.LessThan1000:
                    return new MatchableStringB(s);
                case NumberOfMatches.MoreThan1000:
                    return new MatchableStringSA(s);
                default:
                    return null;
            }
        }
    }
}
