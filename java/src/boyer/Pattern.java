package boyer;

public class Pattern {
	private int[] Delta1;
	public int[] Delta2;

	public String Str;

	private void fillDelta1() {
		for (int i = 0; i < 256; i++) {
			Delta1[i] = Str.length();
		}

		for (int i = Str.length() - 1; i >= 0; i--) {
			if (Delta1[(int) Str.charAt(i)] == Str.length()) {
				Delta1[(int) Str.charAt(i)] = i;
			}
		}

		for (int i = 0; i < 256; i++) {
			if (Delta1[i] != Str.length()) {
				Delta1[i] = Str.length() - 1 - Delta1[i];
			}
		}
	}

	private int rpr(int i) {
		int subPatternLength = Str.length() - i - 1;

		int j = i - 1;
		for (; j >= -subPatternLength; j--) {
			if (j >= 0) {
				if (Str.regionMatches(j, Str, i + 1, subPatternLength)) {
					if (j == 0 || Str.charAt(j - 1) != Str.charAt(i)) {
						break;
					}
				}
			} else {
				if (Str.regionMatches(0, Str, i + 1 - j, subPatternLength + j)) {
					break;
				}
			}
		}

		return j;
	}

	private void fillDelta2() {
		Delta2[Str.length() - 1] = 1;
		for (int i = Str.length() - 2; i >= 0; i--) {
			Delta2[i] = Str.length() - rpr(i);
		}
	}

	public int getDelta1(int ch) {
		if (ch >= 256) {
			return Str.length();
		} else {
			return Delta1[ch];
		}
	}

	public Pattern(String str) {
		Str = str;

		Delta1 = new int[256];
		Delta2 = new int[Str.length()];
	}

	public void preprocess() {
		fillDelta1();
		fillDelta2();
	}
}
