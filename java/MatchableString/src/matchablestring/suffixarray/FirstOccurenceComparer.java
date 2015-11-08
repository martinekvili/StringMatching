package matchablestring.suffixarray;

public class FirstOccurenceComparer extends ComparerBase {

    public FirstOccurenceComparer(String s, String p, Integer[] ssA) {
        super(s, p, ssA);
    }

    @Override
    protected int checkIfValid(int num) {
        if (num == 0 || !str.regionMatches(substringArray[num - 1], pattern, 0, pattern.length())) {
            return 0;
        } else {
            return 1;
        }
    }

}
