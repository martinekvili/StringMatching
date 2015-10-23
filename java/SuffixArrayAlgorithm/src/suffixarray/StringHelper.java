package suffixarray;

public class StringHelper {

	public static int compare(String str1, int start1, String str2, int start2, int length) {
		int pos = 0;

		while (pos < length && (start1 + pos) < str1.length() && (start2 + pos) < str2.length()) {
			int c = str1.charAt(start1 + pos) - str2.charAt(start2 + pos);

			if (c != 0) {
				return c;
			}

			pos++;
		}

		if (pos == length) {
			return 0;
		} else if (start1 + pos == str1.length()) {
			return -1;
		} else {
			return 1;
		}
	}

}
