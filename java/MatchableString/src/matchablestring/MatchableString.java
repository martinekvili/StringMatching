package matchablestring;

import java.util.List;

public abstract class MatchableString {
    protected String Str;

    public MatchableString(String s) {
        Str = s;
    }

    public void preprocess(boolean parallel) {
    }

    public abstract List<Integer> match(Pattern pattern, boolean parallel);
}
