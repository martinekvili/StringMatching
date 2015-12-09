using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MatchableString
{
    public abstract class MatchableString
    {
        protected string Str;

        public MatchableString(string s)
        {
            Str = s;
        }

        /// <summary>
        /// Preprocesses the main text, has to be called before the first matching.
        /// </summary>
        /// <param name="parallel">Sets whether to run parallel or not.</param>
        public virtual void PreProcess(bool parallel) { }

        /// <summary>
        /// Matches the given pattern on the string.
        /// </summary>
        /// <param name="pattern">The pattern to match.</param>
        /// <param name="parallel">Sets whether to run parallel or not.</param>
        /// <returns>The list of the occurrences.</returns>
        public abstract List<int> Match(Pattern pattern, bool parallel);
    }
}
