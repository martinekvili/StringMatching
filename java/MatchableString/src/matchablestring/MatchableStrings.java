package matchablestring;

import matchablestring.boyer.MatchableStringB;
import matchablestring.suffixarray.MatchableStringSA;

public class MatchableStrings {
    public static MatchableString createBoyer(String s) {
        return new MatchableStringB(s);
    }

    public static MatchableString createSuffixArray(String s) {
        return new MatchableStringSA(s);
    }
}
