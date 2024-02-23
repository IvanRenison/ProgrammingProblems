// https://codeforces.com/gym/104857/problem/G
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define mset(a,v) memset((a),(v),sizeof(a))
#define SZ(x) (ll(x.size()))
#define ALL(x) x.begin(),x.end()
#define FIN ios::sync_with_stdio(0),cout.tie(0),cin.tie(0)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
const ll NMAX = 2e5+10;
ll n,m,k;
vector<ll> pre_s;
ll dp[NMAX][8];
ll prox[NMAX];



ll f(ll x, ll cuantos, ll me){
    if(x>=n && cuantos > 0) return NMAX+10;
    if(cuantos==0)return 0;
    ll &res = dp[x][cuantos];
    if(res!=-1)return res;
    res=0;
    if(x+me>n)return res=NMAX+10;
    res = min(f(x+1,cuantos,me),pre_s[x+me]-pre_s[x]+f(prox[x+me]+1,cuantos-1,me));
    // cout << x << " " << cuantos << " " << me << " " << res << "\n";
    return res;
}



bool can(ll me){
    fore(i,0,n+10){
        fore(j,0,8){
            dp[i][j]=-1;
        }
    }
    ll res = f(0,k,me);
    return res<=m;
}


int main(){FIN;
    cin>>n>>m>>k;
    string s;cin>>s;
    pre_s.resize(n+1);
    fore(i,0,SZ(s)){
        pre_s[i+1]=pre_s[i]+(s[i]=='0');
    }
    ll l = 0, r = 0;
    while(l<n && r<=n){
        if(s[r]=='0' || r==n){
            while(l<=r){
                prox[l]=r;++l;
            }
            ++r;
        } else {
            ++r;
        }
    }
    prox[n]=n;
    l = 0, r = NMAX;
    while(l<=r){
        ll me = (l+r)/2;
        if(can(me))l=me+1;
        else r=me-1;
    }
    if(r==0) {
        --r;
    }
    cout << r << "\n";
    return 0;
}