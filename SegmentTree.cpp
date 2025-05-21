#include <bits/stdc++.h>
using namespace std;
#define ll long long

class SegmentTree {
private:
    ll n;
    vector<ll> Tree, Lazy;

    void formTree(ll i, ll j, vector<ll> &arr, ll ind) {
        if (i == j) {
            Tree[ind] = arr[i];
            return;
        }
        ll mid = (i + j) / 2;
        formTree(i, mid, arr, ind * 2 + 1);
        formTree(mid + 1, j, arr, ind * 2 + 2);
        Tree[ind] = Tree[ind * 2 + 1] + Tree[ind * 2 + 2];
    }

    void push(ll i, ll j, ll ind) {
        if (Lazy[ind] != 0) {
            Tree[ind] += (j - i + 1) * Lazy[ind];
            if (i != j) {
                Lazy[ind * 2 + 1] += Lazy[ind];
                Lazy[ind * 2 + 2] += Lazy[ind];
            }
            Lazy[ind] = 0;
        }
    }

    void updateRange(ll i, ll j, ll l, ll r, ll val, ll ind) {
        push(i, j, ind);
        if (j < l || i > r) return;
        if (i >= l && j <= r) {
            Lazy[ind] += val;
            push(i, j, ind);
            return;
        }
        ll mid = (i + j) / 2;
        updateRange(i, mid, l, r, val, ind * 2 + 1);
        updateRange(mid + 1, j, l, r, val, ind * 2 + 2);
        Tree[ind] = Tree[ind * 2 + 1] + Tree[ind * 2 + 2];
    }

    ll getSum(ll i, ll j, ll l, ll r, ll ind) {
        push(i, j, ind);
        if (i > r || j < l) return 0;
        if (l <= i && j <= r) return Tree[ind];
        ll mid = (i + j) / 2;
        return getSum(i, mid, l, r, ind * 2 + 1) + getSum(mid + 1, j, l, r, ind * 2 + 2);
    }

    void updatePoint(ll i, ll j, ll uInd, ll uVal, ll ind) {
        push(i, j, ind);
        if (i == j && i == uInd) {
            Tree[ind] = uVal;
            return;
        }
        if (j < uInd || i > uInd) return;
        ll mid = (i + j) / 2;
        updatePoint(i, mid, uInd, uVal, ind * 2 + 1);
        updatePoint(mid + 1, j, uInd, uVal, ind * 2 + 2);
        Tree[ind] = Tree[ind * 2 + 1] + Tree[ind * 2 + 2];
    }

public:
    SegmentTree() {}

    void buildTree(vector<ll> &arr) {
        n = arr.size();
        Tree.assign(n * 4, 0);
        Lazy.assign(n * 4, 0);
        formTree(0, n - 1, arr, 0);
    }

    void updateQuery(ll index, ll val) {
        updatePoint(0, n - 1, index, val, 0);
    }

    void updateRangeQuery(ll left, ll right, ll val) {
        updateRange(0, n - 1, left, right, val, 0);
    }

    ll getSumQuery(ll left, ll right) {
        return getSum(0, n - 1, left, right, 0);
    }
};

int main() {
    ll n, q;
    cin >> n >> q;
    vector<ll> v(n);
    for (ll i = 0; i < n; i++) cin >> v[i];

    SegmentTree segment;
    segment.buildTree(v);

    for (ll i = 0; i < q; i++) {
        ll type, ip1, ip2, val;
        cin >> type >> ip1 >> ip2;
        if (type == 1) {
            // point update: set ip1-th index to ip2
            segment.updateQuery(ip1 - 1, ip2);
        } else if (type == 2) {
            // range sum query: sum from ip1 to ip2
            cout << segment.getSumQuery(ip1 - 1, ip2 - 1) << endl;
        } else if (type == 3) {
            // range update: add ip2 to all elements from ip1 to val
            cin >> val;
            segment.updateRangeQuery(ip1 - 1, ip2 - 1, val);
        }
    }
    return 0;
}
