#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MOD = 1e9 + 7;
const int BASE = 31;

vector<ll> computeHashes(const string &s) {
    int n = s.size();
    vector<ll> hashes(n + 1, 0);
    ll hashValue = 0;
    ll p = 1;
    for (int i = 0; i < n; ++i) {
        hashValue = (hashValue * BASE + (s[i] - 'a' + 1)) % MOD;
        hashes[i + 1] = hashValue;
        p = (p * BASE) % MOD;
    }
    return hashes;
}

vector<ll> computePowers(int n) {
    vector<ll> powers(n + 1, 1);
    for (int i = 1; i <= n; ++i) {
        powers[i] = (powers[i - 1] * BASE) % MOD;
    }
    return powers;
}

ll getSubstringHash(int l, int r, const vector<ll> &hashes, const vector<ll> &powers) {
    ll hashValue = (hashes[r + 1] - (hashes[l] * powers[r - l + 1]) % MOD + MOD) % MOD;
    return hashValue;
}

int main(){
    ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

    string s;
    cin>>s;
    int n = s.size();

    vector<ll> hashes = computeHashes(s);
    vector<ll> powers = computePowers(n);

    vector<ll>borders;

    int i = 0,j = n-1;
    while (i<n-1){
        ll hashLeft = getSubstringHash(0,i,hashes,powers);
        ll hashRight = getSubstringHash(j,n-1,hashes,powers);
        if (hashLeft == hashRight)borders.push_back(i+1);
        i++;
        j--;
    }
    
    for (ll i : borders)cout<<i<<" ";
    cout<<endl;
}