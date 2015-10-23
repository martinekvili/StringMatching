package suffixarray;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public class MatchAbleString {
	private String original;
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

	public MatchAbleString(String orig) {
		original = orig;
		substringArray = new Integer[original.length()];

		for (int i = 0; i < substringArray.length; i++) {
			substringArray[i] = i;
		}

		isPreProcessed = false;
	}

	public void preProcess(boolean parallel) {
		Comparator<Integer> comp = new MergeSort.Comparer(original);

		if (!parallel) {
			Arrays.sort(substringArray, comp);
		} else {
			MergeSort.parallelSort(substringArray, comp);
		}

		isPreProcessed = true;
	}

	public List<Integer> match(String pattern) {
		if (!isPreProcessed) {
			throw new IllegalStateException("This MatchAbleString hasn't been preprocessed yet!");
		}

		ComparerBase foc = new FirstOccurenceComparer(original, pattern, substringArray);
		ComparerBase loc = new LastOccurenceComparer(original, pattern, substringArray);

		int first = binarySearch(0, original.length(), foc);
		int last = binarySearch(0, original.length(), loc);

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
