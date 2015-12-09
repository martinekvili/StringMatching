package matchablestring;

import java.util.List;

public abstract class MatchableString {
    protected String Str;

    public MatchableString(String s) {
        Str = s;
    }

    /**
     * Preprocesses the main text, has to be called before the first matching.
     * @param parallel Sets whether to run parallel or not
     */
    public void preprocess(boolean parallel) {
    }

    /**
     * Matches the given pattern on the string.
     * @param pattern The pattern to match
     * @param parallel Sets whether to run parallel or not
     * @return The list of the occurrences
     */
    public abstract List<Integer> match(Pattern pattern, boolean parallel);
}
