package suffixarray;

public class LastOccurenceComparer extends ComparerBase {

	public LastOccurenceComparer(String s, String p, Integer[] ssA) {
		super(s, p, ssA);
	}

	@Override
	protected int checkIfValid(int num) {
		if (num == str.length() - 1 || !str.regionMatches(substringArray[num + 1], pattern, 0, pattern.length())) {
			return 0;
		} else {
			return -1;
		}
	}

}
