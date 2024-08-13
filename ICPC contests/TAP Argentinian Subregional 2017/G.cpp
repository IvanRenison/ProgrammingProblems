// https://codeforces.com/group/YjFmW2O15Q/contest/101811
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define SZ(x) ((ll)x.size())
#define mset(a,v) memset((a),(v),sizeof(a))
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
const ll NMAX = 110;
const ll VALMAX = 1010;
const ll MOD = 1e9+7;

ll add(ll x, ll y){
    return (x+y)%MOD;
}
ll mul(ll x, ll y){
    return (x*y)%MOD;
}
ll bin(ll b, ll e){
    if(e==0)return 1;
    ll x = bin(b,e/2);
    if(e&1){
        return mul(b,mul(x,x));
    }
    return mul(x,x);
}

ll dp[NMAX][VALMAX];
ll n,m,p1,p2;
ll fact[NMAX];

ll comb(ll x, ll y){
    ll den = mul(fact[y],fact[x-y]);
    den = bin(den,MOD-2);
    return mul(fact[x],den);
}

ll f(ll x, ll y){
    if(y<0)return 0;
    if(x==0 && y>0)return 0;
    if(x==0)return 1;
    ll &res = dp[x][y];
    if(res!=-1)return res;
    res = 0;
    fore(i,1,m+1){
        res = add(res,f(x-1,y-i));
    }
    // cout << x << " " << y << " " << res << "\n";
    return res;
}

int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    mset(dp,-1);
    cin>>n>>m>>p1>>p2;
    fact[0]=1;
    fore(i,1,NMAX)fact[i]=mul(fact[i-1],i);

    ll res = 0;
    fore(i,1,n){
        ll aux = comb(n,i);
        // cout << i << " " << aux << "\n";
        fore(j,1,n){
            if(i+j>n)break;
            ll aux2 = mul(aux,comb(n-i,j));
            res = add(res,mul(aux2,mul(f(i,p1),f(j,p2))));
        }
    }
    cout << res << "\n";

}