#include "matchablestring.h"

int MatchAbleString::findFirst(const Pattern &p, int startPos, int endPos) {
    int i = p.getLength() - 1;
    while (i < endPos - startPos) {
        int j = p.getLength() - 1;
        for (; j >= 0; j--, i--) {
            if (str[startPos + i] != p[j]) {
                break;
            }
        }
        if (j < 0) {
            return i + 1;
        } else {
            int delta1 = p.getDelta1(str[startPos + i]);
            int delta2 = p.getDelta2(j);
            i += delta1 > delta2 ? delta1 : delta2;
        }
    }
    return -1;
}

std::unique_ptr<std::vector<int>> MatchAbleString::_matchSubstr(const Pattern &p, int startPos, int endPos) {
	std::unique_ptr<std::vector<int>> occurrences = std::make_unique<std::vector<int>>();
	int occ = 0, next;
	while ((next = findFirst(p, startPos + occ, endPos)) != -1) {
		occ += next;
		occurrences->push_back(occ + startPos);
		occ++;
	}
	return occurrences;
}

std::unique_ptr<std::vector<int>> MatchAbleString::matchSubstr(const Pattern &p, int parts, int i) {
	/*
	 * Teh�t a sz�veget parts darabra bontjuk.
	 * Mindegyik kezd�pontja az i * length / parts, ezek az oszt�pontok.
	 * Az�rt hogy meglegyen a megfelel� �tfed�s, a hossz a length / parts-n�l p.getLength() - 1 -gyel hosszabb,
	 * kiv�ve az utols� string eset�n, ahol viszont a kerek�t�sekb�l sz�rmaz� k�l�nbs�get vessz�k hozz�.
	 */
	int startPos = i * (int) str.length() / parts;
	int length = (int) str.length() / parts + p.getLength() - 1;
	return _matchSubstr(p, startPos, (i == parts - 1) ? (int) str.length() : startPos + length);
}

std::unique_ptr<std::vector<int>> MatchAbleString::match(const Pattern &p, bool parallel) {
	const int parts = 8;

    std::vector<std::unique_ptr<std::vector<int>>> occurrencesArray(parts);
    
	if (!parallel) {
		for (int i = 0; i < parts; i++) {
			occurrencesArray[i] = matchSubstr(p, parts, i);
		}
	}
	else {
		tbb::parallel_for(tbb::blocked_range<int>(0, parts), 
			[this, &occurrencesArray, &p, parts](const tbb::blocked_range<int>& range) {
			for (int i = range.begin(); i != range.end(); ++i) {
				occurrencesArray[i] = matchSubstr(p, parts, i);
			}
		});
	}
	
	size_t fullSize = 0;
	for (const auto& occurrence : occurrencesArray) {
		fullSize += occurrence->size();
	}

	std::unique_ptr<std::vector<int>> occurrences = std::make_unique<std::vector<int>>();
	occurrences->reserve(fullSize);
	for (const auto& occurrence : occurrencesArray) {
		occurrences->insert(occurrences->end(), occurrence->begin(), occurrence->end());
	}
    return occurrences;
}
