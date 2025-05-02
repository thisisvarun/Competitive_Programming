vector<int> buildLPS(const string &pat) {
    int m = pat.size();
    vector<int> lps(m, 0);
    for (int i = 1, len = 0; i < m; ) {
        if (pat[i] == pat[len]) {
            lps[i++] = ++len;
        } else if (len) {
            len = lps[len - 1];
        } else {
            lps[i++] = 0;
        }
    }
    return lps;
}
 for (int i = 0, j = 0; i < N; ++i) {
    while (j > 0 && str[i] != pattern[j]) j = lps[j - 1];
    if (str[i] == pattern[j]) ++j;
    if (j == o) {
        // do specific process here
        j = lps[j - 1];
    }
}
