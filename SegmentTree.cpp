#include <bits/stdc++.h>
using namespace std;
#define ll long long

class SegmentTree{
private:
    ll n;
    vector<ll>Tree;

    void formTree(ll i,ll j,vector<ll>&arr,ll ind){
        if (i==j){
            Tree[ind] = arr[i];
            return;
        }
        ll mid = (i+j)/2;
        formTree(i,mid,arr,ind*2+1);
        formTree(mid+1,j,arr,ind*2+2);
        Tree[ind] = Tree[ind*2+1]+Tree[ind*2+2];
    }

    void updateTree(ll i,ll j,ll uInd,ll uVal,ll ind){
        if (i==j && i==uInd){
            Tree[ind] = uVal;
            return;
        }
        if (j<uInd || i>uInd)return;
        ll mid = (i+j)/2;
        updateTree(i,mid,uInd,uVal,ind*2+1);
        updateTree(mid+1,j,uInd,uVal,ind*2+2);
        Tree[ind] = Tree[ind*2+1]+Tree[ind*2+2];
    }

    ll getSum(ll i,ll j,ll l,ll r,ll ind){
        if (i>r || j<l)return 0;
        if (l<=i && j<=r)return Tree[ind];
        ll mid = (i+j)/2;
        return getSum(i,mid,l,r,ind*2+1)+getSum(mid+1,j,l,r,ind*2+2);
    }

public:
    SegmentTree(){
    }
    void buildTree(vector<ll>&arr){
        n = arr.size();
        Tree.resize(n*4,0);
        n--;
        formTree(0,n,arr,0);
    }
    void updateQuery(ll index,ll val){
        updateTree(0,n,index,val,0);
    }
    ll getSumQuery(ll left,ll right){
        return getSum(0,n,left,right,0);
    }
};

int main(){
    ll n,q;
    cin>>n>>q;
    vector<ll>v(n);
    for (ll i=0; i<n; i++)cin>>v[i];
    SegmentTree segment;
    segment.buildTree(v);
    for (ll i=0; i<q; i++){
        ll type,ip1,ip2;
        cin>>type>>ip1>>ip2;
        if (type == 1){
            segment.updateQuery(ip1-1,ip2);
        }
        else{
            cout << segment.getSumQuery(ip1-1,ip2-1) << endl;
        }
    }
    return 0;
}