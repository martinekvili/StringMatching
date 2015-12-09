package matchablestring;

import matchablestring.boyer.MatchableStringB;
import matchablestring.suffixarray.MatchableStringSA;

public class MatchableStrings {

    /**
     * Choices for the approximate number of matches.
     */
    public enum NumberOfMatches {

        /**
         * This object will be used for less than 1000 matches.
         */
        LessThan1000,

        /**
         * This object will be used for more than 1000 matches.
         */
        MoreThan1000
    }

    /**
     * Creates a matchable string object using Boyer-Moore algorithm.
     * @param s The main text to match patterns on
     * @return A matchable string object
     */
    public static MatchableString createBoyer(String s) {
        return new MatchableStringB(s);
    }

    /**
     * Creates a matchable string object using Suffix Array algorithm.
     * @param s The main text to match patterns on
     * @return A matchable string object
     */
    public static MatchableString createSuffixArray(String s) {
        return new MatchableStringSA(s);
    }

    /**
     * Creates a matchable string object with a suitable implementation.
     * @param s The main text to match patterns on
     * @param approx The approximate number of uses
     * @return A matchable string object
     */
    public static MatchableString create(String s, NumberOfMatches approx) {
        switch(approx) {
            case LessThan1000:
                return new MatchableStringB(s);
            case MoreThan1000:
                return new MatchableStringSA(s);
            default:
                return null;
        }
    }
}
