// https://codeforces.com/gym/104555/problem/I
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define fore(i,a,b) for(int i=a,gmat=b;i<gmat;++i)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(),x.end()
#define FIN ios::sync_with_stdio(0);cin.tie(0),cout.tie(0)
#define mset(a,v) memset((a),(v),sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const ll NMAX=1e5+10;


ll b[NMAX];
ll n;
ll dp[NMAX][2];

ll f(ll x, ll pari){
    if(x==n)return 0;
    ll &res = dp[x][pari];
    if(res!=-1)return res;
    res = 0;
    if(pari){
        if(b[x]==0){
            res = 1+f(x+1,1);
        } else {
            res = f(x+1,0);
        }
    } else {
        if(b[x]==1){
            res = 1+f(x+1,1);
        } else {
            res = f(x+1,0);
        }
    }
    return res;
}


int main(){FIN;
    cin>>n;
    fore(i,0,n)cin>>b[i];
    mset(dp,-1);
    ll res = 0;
    fore(i,0,n){
        res += f(i,0);
    }
    cout << res << "\n";
    return 0;
}