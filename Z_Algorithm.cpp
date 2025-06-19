#include <bits/stdc++.h>
using namespace std;

vector<int> build_Z(const string &s) {
    // Compute Z-array
    int n = s.size();
    vector<int> z(n, 0);
    int l = 0, r = 0;
    for (int i = 1; i < n; ++i) {
        if (i > r) {
            l = r = i;
            while (r < n && s[r] == s[r - l]) {
                r++;
            }
            z[i] += r - l;
            r--;
        } else {
            int k = i - l;
            if (z[k] < r - i + 1) {
                z[i] = z[k];
            } else {
                l = i;
                while (r < n && s[r] == s[r - l]) {
                    r++;
                }
                z[i] = r - l;
                r--;
            }
        }
    }
    return z;
}

vector<int> getOccurrences(const string &text, const string &pattern) {
    int n = text.size(), m = pattern.size();
    string s = pattern + "$" + text;

    vector<int> z = build_Z(s);

    // Collect occurrences
    vector<int> occurrences;
    for (int i = m + 1; i < z.size(); ++i) {
        if (z[i] == m) {
            occurrences.push_back(i - m); // 1-based index
        }
    }
    
    return occurrences;
}

int main() {
    string text, pattern;
    cin >> text >> pattern;
    vector<int> ans = getOccurrences(text, pattern);
    cout << ans.size() << endl;
    for (int i : ans) {
        cout << i << " ";
    }
    return 0;
}