// https://redprogramacioncompetitiva.com/contests/2023/13
#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define fst first
#define snd second
#define str string
#define fore(i,a,b) for(int i=a,thxMat=b;i<thxMat;++i)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(),x.end()
#define mset(a,v) memset((a),(v),sizeof(a))
#define FIN ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
using namespace std;
typedef long long ll;
const ll NMAX = 2e5+10;
const ll MOD = 1e9+7;

int main(){FIN;
    ll n;cin>>n;
    vector<ll> a;
    ll it = 2;
    ll sum = 0;
    while(sum<ll(1e18)){
        sum+=it*(it+1)/2;
        a.pb(sum);
        it++;
    }
    ll res = 0;
    while(n>=3){
        ll l = upper_bound(ALL(a),n)-a.begin();
        res+=l;
        l--;
        n-=a[l];
    }
    cout << res << " " << n << "\n";
    return 0;
}
