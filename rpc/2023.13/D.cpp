// https://redprogramacioncompetitiva.com/contests/2023/13
#include <bits/stdc++.h>
#define fore(i,a,b) for(int i=a,thxMat=b;i<thxMat;++i)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(),x.end()
#define FIN ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
using namespace std;
typedef long long ll;
const ll NMAX = 2e5+10;
const ll MOD = 1e9+7;

int main(){FIN;
    ll n,q;cin>>n>>q;
    vector<string> words(n);
    fore(i,0,n)cin>>words[i];
    sort(ALL(words));
    while(q--){
        string w1,w2;cin>>w1>>w2;
        ll l = lower_bound(ALL(words),w1)-words.begin();
        ll r = upper_bound(ALL(words),w2)-words.begin();
        cout << r-l << "\n";
    }
    return 0;
}
