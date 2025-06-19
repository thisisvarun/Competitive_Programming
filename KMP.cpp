vector<int> buildLPS(const string &s) {
	int n = s.size();
	vector<int> LPS(n, 0);
	for (int i = 1, j = 0; i < n;) {
		if (s[i] == s[j]) LPS[i++] = ++j;
		else if (j) j = LPS[j - 1];
		else LPS[i++] = 0;
	}
	return LPS;
}
vector<int> stringMatch(string text, string pattern) {
	int n = text.size();
	vector<int> ans;
	vector<int> LPS = buildLPS(pattern);
	int m = pattern.size();
	for (int i = 0, j = 0; i < n; i++) {
		while (j > 0 && text[i] != pattern[j]) j = LPS[j - 1];
		if (text[i] == pattern[j]) j++;
		if (j == m) {
			ans.push_back(i - m + 2);
			j = LPS[j - 1];
		}
	}
	return ans;
}
