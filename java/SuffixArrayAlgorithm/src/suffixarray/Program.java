package suffixarray;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
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

	static private long measure(String orig, String pat, boolean parallel, int num) {
		// @SuppressWarnings("unused")
		List<Integer> l = null;

		long startTime = System.nanoTime(); // mérés kezdete

		for (int i = 0; i < 5 * num; i++) {
			MatchAbleString str = new MatchAbleString(orig);
			str.preProcess(parallel);
			l = str.match(pat);
		}

		long elapsed = (System.nanoTime() - startTime) / 1000000 / 5; // mérés
																		// vége

		System.out.println((parallel ? "Parallel" : "Single thread") + "matching took " + (elapsed / 1000) + " s "
				+ (elapsed % 1000) + " ms");
		System.out.println("Found " + l.size() + " matches.");
		return elapsed;
	}

	private static void measureFileRead(String[] args) {
//		String path = "..\\resources\\" + args[0];
		 String path = "..\\..\\resources\\spacewrecked.txt";

		BufferedReader reader = null;
		try {
			reader = new BufferedReader(new FileReader(new File(path)));
			StringBuilder sb = new StringBuilder();
			while (reader.ready()) {
				sb.append(reader.readLine());
				sb.append('\n');
			}
			String str = sb.toString();

			// int multiplier = Integer.parseInt(args[2]);
			// int num = Integer.parseInt(args[3]);

			int multiplier = 1;

			String orig = str;
			for (int i = 0; i < multiplier - 1; i++) {
				orig += str;
			}

			System.out.print(orig.length() + ";");

			// System.out.print(measure(orig, args[1], false, num) + ";");
			// System.out.println(measure(orig, args[1], true, num) + ";");
			System.out.println(measure(orig, "plentifully", false, 1) + ";");
			System.out.println(measure(orig, "plentifully", true, 1) + ";");
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			if (reader != null) {
				try {
					reader.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		}
	}

	public static void main(String[] args) {
		// measureSimple();

		measureFileRead(args);
	}

}
