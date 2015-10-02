package boyer;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.List;

public class Program {

	// public static void main(String[] args) {
	// String s = "i had to, Hence, i peed the fence. i don't see the adHence";
	// String pat = "ence";
	// MatchAbleString str = new MatchAbleString(s);
	// Pattern p = new Pattern(pat);
	// p.preprocess();
	//
	// List<Integer> l = str.match(p, true);
	//
	// for(Integer i : l)
	// {
	// System.out.println(i + " : " + s.substring(i, i + pat.length()));
	// }
	// }

	static private long measure(String orig, String pat, boolean parallel, int num) {
		long startTime;
		long elapsed = 0;
		List<Integer> l = null;

		MatchAbleString str = new MatchAbleString(orig);

		for (int i = 0; i < 5 * num; i++) {
			Pattern p = new Pattern(pat);

			startTime = System.nanoTime();
			p.preprocess();
			l = str.match(p, parallel);
			elapsed += System.nanoTime() - startTime;
		}

		elapsed /= 1000000;

//		System.out.println((parallel ? "Parallel" : "Single thread") + " matching took " + (elapsed / 1000) + " s "
//				+ (elapsed % 1000) + " ms");
//		System.out.println("Found " + l.size() + " matches.");
		return elapsed / 5;
	}

	public static void main(String[] args) {
		String path = "..\\..\\..\\resources\\" + args[0];
		// String path = "..\\..\\resources\\spacewrecked.txt";

		BufferedReader reader = null;
		try {
			reader = new BufferedReader(new FileReader(new File(path)));
			StringBuilder sb = new StringBuilder();
			while (reader.ready()) {
				sb.append(reader.readLine());
				sb.append('\n');
			}
			String str = sb.toString();

			String orig = str;
			for (int i = 0; i < 63; i++) {
				orig += str;
			}

			System.out.print(orig.length() + ";");

			// int num = Int32.Parse(args[2]);
			// Console.Write(num + ";");

			System.out.print(measure(orig, args[1], false, 1000) + ";");
			System.out.println(measure(orig, args[1], true, 1000) + ";");
			// System.out.println(measure(orig, "plentifully", false, 1000) +
			// ";");
			// System.out.println(measure(orig, "plentifully", true, 1000) +
			// ";");
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
}
