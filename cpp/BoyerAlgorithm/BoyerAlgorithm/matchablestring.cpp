#include "matchablestring.h"
#include <iostream>

MatchAbleString::MatchAbleString(const char *c) {
    length = strlen(c);
    str = new char[length + 1];
    strcpy(str, c);
}

MatchAbleString::~MatchAbleString() {
    delete[] str;
}

int MatchAbleString::findFirst(Pattern &p, const char *str_, size_t length_) {
    size_t i = p.getLength() - 1;
    while (i < length_) {
        int j = p.getLength() - 1;
        for (; j >= 0; j--, i--) {
            if (str_[i] != p[j]) {
                break;
            }
        }
        if (j < 0) {
            return i + 1;
        } else {
            //std::cout << i << ", " << j << " - " << str_[i] << " : " << p.getDelta1(str_[i]) << ", " << p.getDelta2(j) << std::endl;
            int delta1 = p.getDelta1(str_[i]);
            int delta2 = p.getDelta2(j);
            i += delta1 > delta2 ? delta1 : delta2;
        }
    }
    return -1;
}

std::list<int> MatchAbleString::matchSubstr(Pattern &p, const char *str_, int length_, int startPos) {
	std::list<int> occurrences;
	int occ = 0, next;
	while ((next = MatchAbleString::findFirst(p, str_ + occ, length_ - occ)) != -1) {
		occ += next;
		occurrences.push_back(occ + startPos);
		occ++;
	}
	return occurrences;
}

std::list<int> MatchAbleString::matchSubstr(Pattern &p, int parts, int i) {
	/*
	* Teh�t a sz�veget parts darabra bontjuk.
	* Mindegyik kezd�pontja az i * length / parts, ezek az oszt�pontok.
	* Az�rt hogy meglegyen a megfelel� �tfed�s, a hossz a length / parts-n�l p.getLength() - 1 -gyel hosszabb,
	* kiv�ve az utols� string eset�n, ahol viszont a kerek�t�sekb�l sz�rmaz� k�l�nbs�get vessz�k hozz�.
	*/
	return MatchAbleString::matchSubstr(p, str + i * length / parts,
		(i == parts - 1) ? length - i * length / parts : length / parts + p.getLength() - 1, i * length / parts);
}

std::list<int> MatchAbleString::match(Pattern &p, bool parallel) {
	const int parts = 8;

    std::vector<std::list<int>> occurrencesArray(parts);
    
	if (!parallel) {
		for (int i = 0; i < parts; i++) {
			occurrencesArray[i] = matchSubstr(p, parts, i);
		}
	}
	else {
		tbb::parallel_for(tbb::blocked_range<int>(1, parts), ParallelMatcher(*this, p, occurrencesArray, parts));
	}
	

	std::list<int> occurrences;
	for (int i = 0; i < parts; i++) {
		occurrences.insert(occurrences.end(), occurrencesArray[i].begin(), occurrencesArray[i].end());
	}
    return occurrences;
}

void MatchAbleString::ParallelMatcher::operator() (const tbb::blocked_range<int>& range) const {
	for (int i = range.begin(); i != range.end(); ++i) {
		array[i] = mas.matchSubstr(p, parts, i);
	}
}
