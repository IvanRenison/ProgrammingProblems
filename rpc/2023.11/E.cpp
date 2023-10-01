// https://redprogramacioncompetitiva.com/contests/2023/11

#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((int)x.size())
#define fore(i,a,b) for(int i=a,gmat=b;i<gmat;++i)
#define pb push_back
#define mset(a,v) memset((a),(v),sizeof(a))
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vii;
typedef vector<ull> vuii;
typedef pair<ll,ll> ii;
const ll NMAX = 10+1000*12;


ll dp[1010][NMAX];
ll n;
ll mat[1010][15];

ll f(ll x, ll cuan){
    if(x==n)return 0;
    ll &res = dp[x][cuan];
    if(res!=-1)return res;
    ll acc=0;
    res = 0;
    fore(i,0,min(13ll,cuan+1)){
        res = max(res,acc+f(x+1,cuan-i));
        acc+=mat[x][i];
    }
    // cout << x << " " << cuan << " " << res << "\n";
    return res;
}

int main(){FIN;
    cin>>n;
    ll k;cin>>k;
    fore(i,0,n){
        fore(j,0,12){
            cin>>mat[i][j];
        }
    }
    mset(dp,-1);
    ll res=f(0,k);
    cout << res << "\n";
    return 0;
}