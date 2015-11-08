package matchablestring.suffixarray;

import matchablestring.MatchableString;
import matchablestring.Pattern;

import java.util.*;

public class MatchableStringSA extends MatchableString {
    private Integer[] substringArray;
    private boolean isPreProcessed;

    private int binarySearch(int min, int max, ComparerBase comparer) {
        int num = (min + max) / 2;

        switch (comparer.Compare(num)) {
            case 0:
                return num;
            case -1:
                return binarySearch(num + 1, max, comparer);
            case 1:
                return binarySearch(min, num, comparer);
            default:
                throw new UnsupportedOperationException("Not possible to get here - theoretically.");
        }
    }

    public MatchableStringSA(String s) {
        super(s);

        substringArray = new Integer[Str.length()];

        for (int i = 0; i < substringArray.length; i++) {
            substringArray[i] = i;
        }

        isPreProcessed = false;
    }

    public void preprocess(boolean parallel) {
        Comparator<Integer> comp = new MergeSort.Comparer(Str);

        if (!parallel) {
            Arrays.sort(substringArray, comp);
        } else {
            MergeSort.parallelSort(substringArray, comp);
        }

        isPreProcessed = true;
    }

    public List<Integer> match(Pattern pattern, boolean parallel) {
        if (!isPreProcessed) {
            throw new IllegalStateException("This MatchAbleString hasn't been preprocessed yet!");
        }

        ComparerBase foc = new FirstOccurenceComparer(Str, pattern.Str, substringArray);
        ComparerBase loc = new LastOccurenceComparer(Str, pattern.Str, substringArray);

        int first = binarySearch(0, Str.length(), foc);
        int last = binarySearch(0, Str.length(), loc);

        if (first == -1) {
            return new ArrayList<Integer>();
        } else {
            List<Integer> tmp = new ArrayList<Integer>();

            for (int i = first; i <= last; i++) {
                tmp.add(substringArray[i]);
            }

            Collections.sort(tmp);

            return tmp;
        }
    }
}
