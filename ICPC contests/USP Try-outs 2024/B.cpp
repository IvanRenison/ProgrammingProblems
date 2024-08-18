// https://codeforces.com/gym/105297/problem/B
#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((ll)x.size())
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define pb push_back
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
const ll NMAX = 1e5+10;
const ll MOD = 998244353;


ll n,m,h;

const ll mod = 998244353, root = 62;

ll modpow(ll b, ll e) {
  ll ans = 1;
  for (; e; b = b * b % mod, e /= 2)
    if (e & 1) ans = ans * b % mod;
  return ans;
}


void ntt(vi& a) {
  ll n = SZ(a), L = 63 - __builtin_clzll(n);
  static vi rt(2, 1);
  for (static ll k = 2, s = 2; k < n; k *= 2, s++) {
    rt.resize(n);
    ll z[] = {1, modpow(root, mod >> s)};
    fore(i, k, 2*k) rt[i] = rt[i / 2] * z[i & 1] % mod;
  }
  vi rev(n);
  fore(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
  fore(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
  for (ll k = 1; k < n; k *= 2)
    for (ll i = 0; i < n; i += 2 * k) fore(j, 0, k) {
      ll z = rt[j + k] * a[i + j + k] % mod, &ai = a[i + j];
      a[i + j + k] = ai - z + (z > ai ? mod : 0);
      ai += (ai + z >= mod ? z - mod : z);
    }
}
vi conv(const vi& a, const vi& b) {
  if (a.empty() || b.empty()) return {};
  ll s = SZ(a) + SZ(b) - 1, B = 64 - __builtin_clzll(s),
    n = 1 << B;
  ll inv = modpow(n, mod - 2);
  vi L(a), R(b), out(n);
  L.resize(n), R.resize(n);
  ntt(L), ntt(R);
  fore(i,0,n)
    out[-i & (n - 1)] = (ll)L[i] * R[i] % mod * inv % mod;
  ntt(out);
  return {out.begin(), out.begin() + s};
}




vector<ll> bin(vector<ll> &poly, ll e){
    if(e==0)return {1};
    vector<ll> x = bin(poly,e/2);
    while(SZ(x)>n+10)x.pop_back();
    if(e&1){
        vector<ll> aux = conv(poly,x);
        while(SZ(aux)>n+10)aux.pop_back();
        return conv(x,aux);
    }
    return conv(x,x);
}

ll fact[NMAX];
ll mul(ll x, ll y){return (x*y)%MOD;}
ll add(ll x, ll y){return (x+y)%MOD;}

ll binnum(ll b, ll e){
    if(e==0)return 1;
    ll x = binnum(b,e/2);
    if(e&1){
        return mul(x,mul(b,x));
    }
    return mul(x,x);
}

ll sub(ll x, ll y){return (x-y+MOD)%MOD;}


ll comb(ll x, ll y){
    if(y>x)return 0;
    ll den = mul(fact[y],fact[x-y]);
    den = binnum(den,MOD-2);
    return mul(fact[x],den);
}


int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    ll t;cin>>t;
    fact[0]=1;
    fore(i,1,NMAX)fact[i]=mul(fact[i-1],i);
    while(t--){
        cin>>n>>m>>h;
        if(h>n){
            cout << "0\n";
            continue;
        }
        vector<ll> poly(h+1,1);
        poly[0]=0;
        poly = bin(poly,m+1);
        ll cuantas = 0;
        // dif 0, dif ......, dif n+1 con ultimo
        if(SZ(poly)>n+1)cuantas=poly[n+1];
        ll num = comb(n,m);
        // cout << cuantas << " acaa\n";

        num = sub(num,cuantas);
        ll den = comb(n,m);
        den = binnum(den,MOD-2);
        cout << mul(num,den) << "\n";
    }
}
