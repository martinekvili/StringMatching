package matchablestring;

import matchablestring.boyer.MatchableStringB;
import matchablestring.suffixarray.MatchableStringSA;

public class MatchableStrings {
    public enum NumberOfMatches {
        LessThan1000,
        MoreThan1000
    }

    public static MatchableString createBoyer(String s) {
        return new MatchableStringB(s);
    }

    public static MatchableString createSuffixArray(String s) {
        return new MatchableStringSA(s);
    }

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
