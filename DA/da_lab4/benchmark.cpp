#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

const unsigned short MAX_WORD_SIZE = 16;

struct TWord {
	char Word[MAX_WORD_SIZE];
	unsigned int StringId, WordId;
};

bool operator == (const TWord & lhs, const TWord & rhs) {
	for (unsigned short i = 0; i < MAX_WORD_SIZE; ++i) {
		if (lhs.Word[i] != rhs.Word[i]) {
			return false;
		}
	}
	return true;
}

bool operator != (const TWord & lhs, const TWord & rhs) {
	return !(lhs == rhs);
}

std::vector<unsigned int> PrefixFunction(const std::vector<TWord> & s) {
	unsigned int n = s.size();
	std::vector<unsigned int> p(n);
	for (unsigned int i = 1; i < n; ++i) {
		p[i] = p[i - 1];
		while (p[i] > 0 and s[i] != s[p[i]]) {
			p[i] = p[p[i] - 1];
		}
		if (s[i] == s[p[i]]) {
			++p[i];
		}
	}
	return p;
}

std::vector<unsigned int> KMPWeak(const std::vector<TWord> & pattern, const std::vector<TWord> & text) {
	std::vector<unsigned int> p = PrefixFunction(pattern);
	unsigned int m = pattern.size();
	unsigned int n = text.size();
	unsigned int i = 0;
	std::vector<unsigned int> ans;
	if (m > n) {
		return ans;
	}
	while (i < n - m + 1) {
		unsigned int j = 0;
		while (j < m and pattern[j] == text[i + j]) {
			++j;
		}
		if (j == m) {
			ans.push_back(i);
		} else {
			if (j > 0 and j > p[j - 1]) {
				i = i + j - p[j - 1] - 1;
			}
		}
		++i;
	}
	return ans;
}

std::vector<unsigned int> ZFunction(const std::vector<TWord> & s) {
	unsigned int n = s.size();
	std::vector<unsigned int> z(n);
	unsigned int l = 0, r = 0;
	for (unsigned int i = 1; i < n; ++i) {
		if (i <= r) {
			z[i] = std::min(z[i - l], r - i);
		}
		while (i + z[i] < n and s[i + z[i]] == s[z[i]]) {
			++z[i];
		}
		if (i + z[i] > r) {
			l = i;
			r = i + z[i];
		}
	}
	return z;
}

std::vector<unsigned int> StrongPrefixFunction(const std::vector<TWord> & s) {
	std::vector<unsigned int> z = ZFunction(s);
	unsigned int n = s.size();
	std::vector<unsigned int> sp(n);
	for (unsigned int i = n - 1; i > 0; --i) {
		sp[i + z[i] - 1] = z[i];
	}
	return sp;
}

std::vector<unsigned int> KMPStrong(const std::vector<TWord> & pattern, const std::vector<TWord> & text) {
	std::vector<unsigned int> p = StrongPrefixFunction(pattern);
	unsigned int m = pattern.size();
	unsigned int n = text.size();
	unsigned int i = 0;
	std::vector<unsigned int> ans;
	if (m > n) {
		return ans;
	}
	while (i < n - m + 1) {
		unsigned int j = 0;
		while (j < m and pattern[j] == text[i + j]) {
			++j;
		}
		if (j == m) {
			ans.push_back(i);
		} else {
			if (j > 0 and j > p[j - 1]) {
				i = i + j - p[j - 1] - 1;
			}
		}
		++i;
	}
	return ans;
}

void Clear(char arr[MAX_WORD_SIZE]) {
	for (unsigned short i = 0; i < MAX_WORD_SIZE; ++i) {
		arr[i] = 0;
	}
}

int main() {
	bool flagPatternText = 1;
	std::vector<TWord> pattern;
	std::vector<TWord> text;
	TWord cur;
	Clear(cur.Word);
	char c = getchar();
	unsigned short j = 0;
	while (c > 0) {
		if (c == '\n') {
			if (j > 0) {
				text.push_back(cur);
				Clear(cur.Word);
				j = 0;
			}
			++cur.StringId;
			if (flagPatternText) {
				std::swap(pattern, text);
				flagPatternText = 0;
				cur.StringId = 1;
			}
			cur.WordId = 1;
		} else if (c == '\t' or c == ' ') {
			if (j > 0) {
				text.push_back(cur);
				Clear(cur.Word);
				j = 0;
				++cur.WordId;
			}
		} else {
			if ('A' <= c and c <= 'Z') {
				c = c + 'a' - 'A';
			}
			cur.Word[j] = c;
			++j;
		}
	    c = getchar();
	}
	if (j > 0) {
		text.push_back(cur);
	}
    auto start = high_resolution_clock::now();
	std::vector<unsigned int> ans = KMPStrong(pattern, text);
    auto end = high_resolution_clock::now();
    /*
	for (const unsigned int & id : ans) {
		printf("%d, %d\n", text[id].StringId, text[id].WordId);
	}
    */
    auto duration = duration_cast<microseconds>(end-start);
    std::cout << "Time: " << duration.count() << " microseconds" << "\n";
}
