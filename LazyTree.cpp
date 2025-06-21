#include <bits/stdc++.h>
using namespace std;
#define int long long
#define all(x) begin(x), end(x)

class LazyTree {
    private:
    vector<int> lazy, Tree;
    int n, N;
    void build(int i, int j, int idx, const vector<int> &v) {
        if (i == j) {
            Tree[idx] = v[i];
            return;
        }
        int mid = (i + j) / 2;
        build(i, mid, 2 * idx + 1, v);
        build(mid + 1, j, 2 * idx + 2, v);
    }
    int getValueUtil(int i, int j, int idx, int x) {
        if (i == j) {
            return Tree[idx] + lazy[idx];
        }
        int mid = (i + j) / 2;
        if (x <= mid) {
            return getValueUtil(i, mid, 2 * idx + 1, x) + lazy[idx];
        } else {
            return getValueUtil(mid + 1, j, 2 * idx + 2, x) + lazy[idx];
        }
    }
    void addXtoRangeUtil(int i, int j, int l, int r, int x, int idx) {
        if (lazy[idx] != 0) {
            Tree[idx] += lazy[idx];
            if (i != j) {
                lazy[2 * idx + 1] += lazy[idx];
                lazy[2 * idx + 2] += lazy[idx];
            }
            lazy[idx] = 0;
        }
        if (i > r || j < l) return; // No overlap
        if (i >= l && j <= r) { // Total overlap
            Tree[idx] += x;
            if (i != j) {
                lazy[2 * idx + 1] += x;
                lazy[2 * idx + 2] += x;
            }
            return;
        }
        // Partial overlap
        int mid = (i + j) / 2;
        addXtoRangeUtil(i, mid, l, r, x, 2 * idx + 1);
        addXtoRangeUtil(mid + 1, j, l, r, x, 2 * idx + 2);
        Tree[idx] = Tree[2 * idx + 1] + Tree[2 * idx + 2];
    }
    public:
    LazyTree(const vector<int> &v) {
        n = v.size();
        N = n*4;
        lazy.assign(N, 0);
        Tree.assign(N, 0);
        build(0, n - 1, 0, v);
    }
    void addXtoRange(int l, int r, int x) {
        addXtoRangeUtil(0, n - 1, l, r, x, 0);
    }
    int getValue(int idx) {
        return getValueUtil(0, n - 1, 0, idx);
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> v(n);
    for (int &i : v) cin >> i;
    LazyTree s(v);
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            --l, --r;
            s.addXtoRange(l, r, x);
        } else {
            int idx;
            cin >> idx;
            --idx;
            cout << s.getValue(idx) << '\n';
        }
    }
}

signed main() {
    solve();
    // can add testcases
}