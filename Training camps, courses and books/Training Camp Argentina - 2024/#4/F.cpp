// https://codeforces.com/group/5GNF7zti59/contest/535722/problem/F
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define SZ(x) ((ll)x.size())
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;

struct UF {
  vi e;
  UF(ll n) : e(n, -1) {}
  ll size(ll x) { return -e[find(x)];}
  ll find(ll x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
  bool join(ll a, ll b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (e[a] > e[b]) swap(a, b);
    e[a] += e[b]; e[b] = a;
    return true;
  }
};

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll n, m, k; cin >> n >> m >> k;
  vi c(k);
  fore(i, 0, k) cin >> c[i], c[i]--;
  UF uf(n);
  fore(i,0, m) {
    ll u, v; cin >> u >> v;
    u--, v--;
    uf.join(u, v);
  }
  ll ans = 0;
  map<ll, ll> comps;
  fore(i, 0, k) comps[uf.find(c[i])] = uf.size(c[i]);
  ll noncap = 0;
  fore(i, 0, n) if (!comps.count(uf.find(i))) noncap++;
  ll ma = 0;
  for(auto [rep, sz] : comps) {
    ma = max(ma, sz);
    ans += sz * (sz - 1) / 2;
  }
  ans -= ma * (ma - 1) / 2;
  ma += noncap;
  ans += ma * (ma - 1) / 2;

  cout << ans - m << "\n";

}