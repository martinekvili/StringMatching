package matchablestring.suffixarray;

public abstract class ComparerBase {
    protected String str;
    protected String pattern;
    protected Integer[] substringArray;

    protected abstract int checkIfValid(int num);

    public ComparerBase(String s, String p, Integer[] ssA) {
        str = s;
        pattern = p;
        substringArray = ssA;
    }

    public int Compare(int num) {
        int comp = StringHelper.compare(str, substringArray[num], pattern, 0, pattern.length());
        if (comp < 0) {
            return -1;
        } else if (comp > 0) {
            return 1;
        } else {
            return checkIfValid(num);
        }
    }
}
