package boyer;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.*;

public class MatchAbleString {
	private String Str;

	private int findFirst(Pattern p, int startPos, int endPos) {
		int i = p.Str.length() - 1;
		while (i < endPos - startPos) {
			int j = p.Str.length() - 1;
			for (; j >= 0; j--, i--) {
				if (Str.charAt(startPos + i) != p.Str.charAt(j)) {
					break;
				}
			}
			if (j < 0) {
				return i + 1;
			} else {
				int delta1 = p.getDelta1((int) Str.charAt(startPos + i));
				int delta2 = p.Delta2[j];
				i += delta1 > delta2 ? delta1 : delta2;
			}
		}
		return -1;
	}

	private List<Integer> _matchSubstr(Pattern p, int startPos, int endPos) {
		List<Integer> occurrences = new ArrayList<Integer>();
		int occ = 0, next;
		while ((next = findFirst(p, startPos + occ, endPos)) != -1) {
			occ += next;
			occurrences.add(occ + startPos);
			occ++;
		}
		return occurrences;
	}

	private List<Integer> matchSubstr(Pattern p, int parts, int i) {
		/*
		 * Teh�t a sz�veget parts darabra bontjuk. Mindegyik kezd�pontja az i *
		 * length / parts, ezek az oszt�pontok. Az�rt hogy meglegyen a megfelel�
		 * �tfed�s, a hossz a length / parts-n�l p.getLength() - 1 -gyel
		 * hosszabb, kiv�ve az utols� string eset�n, ahol viszont a
		 * kerek�t�sekb�l sz�rmaz� k�l�nbs�get vessz�k hozz�.
		 */
		int startPos = i * Str.length() / parts;
		int length = Str.length() / parts + p.Str.length() - 1;
		return _matchSubstr(p, startPos, (i == parts - 1) ? Str.length() : startPos + length);
	}

	public MatchAbleString(String s) {
		Str = s;
	}

	public List<Integer> match(Pattern p, boolean parallel) {
		int parts = 8;

		@SuppressWarnings("unchecked")
		List<Integer>[] occurrencesArray = new ArrayList[parts];

		if (!parallel) {
			for (int i = 0; i < parts; i++) {
				occurrencesArray[i] = matchSubstr(p, parts, i);
			}
		} else {
			IntStream.range(0, parts).parallel().forEach(i -> occurrencesArray[i] = matchSubstr(p, parts, i));
		}

		List<Integer> occurrences = new ArrayList<Integer>();
		for (int i = 0; i < parts; i++) {
			occurrences.addAll(occurrencesArray[i]);
		}
		return occurrences;
	}
}
