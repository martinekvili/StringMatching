package suffixarray;

import java.util.List;

public class Program {

	private static void measureSimple() {
		String orig = "i had to, Hence, i peed the fence. i don't see the adHence";
		MatchAbleString sm = new MatchAbleString(orig);
		sm.preProcess(true);

		String pat = "ence";
		List<Integer> h = sm.match(pat);

		for (Integer i : h) {
			System.out.println(i + " : " + orig.substring(i, i + pat.length()));
		}
	}

	public static void main(String[] args) {
		measureSimple();
	}

}
