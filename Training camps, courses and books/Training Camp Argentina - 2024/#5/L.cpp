// https://codeforces.com/group/5GNF7zti59/contest/536252/problem/L
#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(X) X.begin(),X.end()
#define SZ(x) ((ll)x.size())
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define pb push_back
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef long double ld;

struct SuffixArray {
  vi sa, lcp, rank;
  SuffixArray(string& s, ll lim=256) {
    ll n = SZ(s) + 1, k = 0, a, b;
    vi x(ALL(s)+1), y(n), ws(max(n, lim));
    sa = lcp = rank = y, iota(ALL(sa), 0);
for (ll j = 0, p= 0; p < n; j = max(1ll, j*2), lim = p) {
  p = j, iota(ALL(y), n - j);
fore(i, 0, n) if (sa[i] >= j) y[p++] = sa[i] - j;
fill(ALL(ws), 0);
fore(i, 0, n) ws[x[i]]++;
fore(i, 1, lim) ws[i] += ws[i - 1];
for(ll i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
swap(x, y), p = 1, x[sa[0]] = 0;
fore(i, 1, n) a = sa[i - 1], b = sa[i], x[b] = (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;

}
fore(i, 1, n) rank[sa[i]] = i;
for (ll i = 0, j; i < n - 1; lcp[rank[i++]] = k)
  for (k && k--, j = sa[rank[i] - 1];
  s[i + k] == s[j + k]; k++);
  }
};

template<class T>
struct RMQ{
  vector<vector<T>> jmp;
  RMQ(const vector<T>&V) : jmp(1,V) {
    for(ll pw = 1, k = 1;pw*2 <=SZ(V); pw *= 2, ++k){
      jmp.emplace_back(SZ(V)-pw*2+1);
      fore(j,0,SZ(jmp[k])){
        jmp[k][j] = min(jmp[k-1][j],jmp[k-1][j+pw]);
      }
    }
  }
  T query(ll a, ll b){
    assert(a < b);
    ll dep = 63 - __builtin_clzll(b-a);
    return min(jmp[dep][a],jmp[dep][b-(1<<dep)]);
  }
};

void solve() {
  ll n; cin >> n;
  string s; cin >> s;
  SuffixArray sa(s);
  RMQ rmq(sa.lcp);

  auto lcp = [&](ll i, ll j) {
    if (i == j) return n - i;
    i = sa.rank[i];
    j = sa.rank[j];
    if (j < i) swap(i, j);
    return rmq.query(i + 1, j + 1);
  };

  vi dp(n);
  fore(i, 0, n) {
    dp[i] = n - sa.sa[i+1];
    fore(j, 0, n) if (sa.sa[i+1] > sa.sa[j+1]) {
      dp[i] = max(dp[i], dp[j] + (n - sa.sa[i+1]) - lcp(sa.sa[i+1], sa.sa[j+1]));
    }
  }

  // fore(i, 0, n) cerr << dp[i] <<' ';
  // cerr << "\n";

  ll res = *max_element(ALL(dp));
  cout << res << "\n";
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll t; cin >> t;
  while(t--) solve();
}