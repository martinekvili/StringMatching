#include "matchablestringb.h"

int MatchableStringB::findFirst(const Pattern &p, const char *str_, size_t length_) {
    size_t i = p.getLength() - 1;
    while (i < length_) {
        int j = (int) p.getLength() - 1;
        for (; j >= 0; j--, i--) {
            if (str_[i] != p[j]) {
                break;
            }
        }
        if (j < 0) {
            return (int) i + 1;
        } else {
            int delta1 = p.getDelta1(str_[i]);
            int delta2 = p.getDelta2(j);
            i += delta1 > delta2 ? delta1 : delta2;
        }
    }
    return -1;
}

std::vector<int>* MatchableStringB::matchSubstr(const Pattern &p, const char *str_, int length_, int startPos) {
	std::vector<int> *occurrences = new std::vector<int>();
	int occ = 0, next;
	while ((next = MatchableStringB::findFirst(p, str_ + occ, length_ - occ)) != -1) {
		occ += next;
		occurrences->push_back(occ + startPos);
		occ++;
	}
	return occurrences;
}

std::vector<int>* MatchableStringB::matchSubstr(const Pattern &p, int parts, int i) const {
	/*
	 * Tehát a szöveget parts darabra bontjuk.
	 * Mindegyik kezdõpontja az i * length / parts, ezek az osztópontok.
	 * Azért hogy meglegyen a megfelelõ átfedés, a hossz a length / parts-nál p.getLength() - 1 -gyel hosszabb,
	 * kivéve az utolsó string esetén, ahol viszont a kerekítésekbõl származó különbséget vesszük hozzá.
	 */
	return MatchableStringB::matchSubstr(p, str + i * length / parts,
		(i == parts - 1) ? length - i * length / parts : length / parts + p.getLength() - 1, i * length / parts);
}

std::vector<int> MatchableStringB::match(Pattern &p, bool parallel) const {
	if (!p.isPreprocessed()) {
		p.preprocess();
	}

	std::vector<int> occurrences;
    
	if (!parallel) {
		auto tmp = matchSubstr(p, str, length, 0);
		occurrences = std::move(*tmp);
		delete tmp;
	}
	else {
		const int parts = tbb::task_scheduler_init::default_num_threads();
		std::vector<std::vector<int>*> occurrencesArray(parts);

		tbb::parallel_for(tbb::blocked_range<int>(0, parts),
			[this, &occurrencesArray, &p, parts](const tbb::blocked_range<int>& range) {
			for (int i = range.begin(); i != range.end(); ++i) {
				occurrencesArray[i] = matchSubstr(p, parts, i);
			}
		});

		size_t fullSize = 0;
		for (int i = 0; i < parts; i++) {
			fullSize += occurrencesArray[i]->size();
		}

		occurrences.reserve(fullSize);
		for (int i = 0; i < parts; i++) {
			occurrences.insert(occurrences.end(), occurrencesArray[i]->begin(), occurrencesArray[i]->end());
			delete occurrencesArray[i];
		}
	}
		
    return occurrences;
}
