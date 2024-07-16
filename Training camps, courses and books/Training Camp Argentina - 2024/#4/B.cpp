// https://codeforces.com/group/5GNF7zti59/contest/535722/problem/B
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
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;

const ll wlim = 5e5 + 1;

/** Author: Lukas Polacek, Simon Lindholm
 * Date: 2019-12-26
 * License: CC0
 * Source: folklore
 * Description: Disjoint-set data structure with undo.
 * If undo is not needed, skip st, time() and rollback().
 * Usage: ll t = uf.time(); ...; uf.rollback(t);
 * Time: O(\log(N))$
 * Status: tested as part of DirectedMST.h
 */
struct RollbackUF {
  vi e; vector<ii> st;
  RollbackUF(ll n) : e(n, -1) {}
  ll size(ll x) { return -e[find(x)]; }
  ll find(ll x) { return e[x] < 0 ? x : find(e[x]); }
  ll time() { return SZ(st); }
  void rollback(ll t) {
    for (ll i = time(); i --> t;)
      e[st[i].fst] = st[i].snd;
    st.resize(t);
  }
  bool join(ll a, ll b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (e[a] > e[b]) swap(a, b);
    st.pb({a, e[a]}), st.pb({b, e[b]});
    e[a] += e[b]; e[b] = a;
    return true;
  }
};

vector<bool> solve(ll n, viii& edges, const vector<vi>& queries) {
  ll m = edges.size(), q = queries.size();

  vector<vi> edges_per_w(wlim);
  fore(i, 0, m) {
    auto [u, v, w] = edges[i];
    edges_per_w[w].push_back(i);
  }

  vector<map<ll, vi>> queries_per_w(wlim);
  fore(i, 0, q) {
    for (ll e : queries[i]) {
      auto [u, v, w] = edges[e];
      queries_per_w[w][i].push_back(e);
    }
  }

  vector<bool> ans(q, true);

  RollbackUF uf(n);

  fore(w, 0, wlim) {
    if (!edges_per_w[w].empty()) {
      ll t = uf.time();
      for (const auto& [i, ks] : queries_per_w[w]) {
        bool valid = true;
        for (ll e : ks) {
          auto [u, v, _] = edges[e];
          if (!uf.join(u, v)) {
            valid = false;
            break;
          }
        }
        if (!valid) {
          ans[i] = false;
        }
        uf.rollback(t);
      }
    }
    for (ll e : edges_per_w[w]) {
      auto [u, v, _] = edges[e];
      uf.join(u, v);
    }
  }

  return ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll n, m;
  cin >> n >> m;
  viii edges(m);
  for (auto& [u, v, w] : edges) {
    cin >> u >> v >> w;
    u--, v--;
  }
  ll q;
  cin >> q;
  vector<vi> queries(q);
  for (vi& es : queries) {
    ll k;
    cin >> k;
    es = vi(k);
    for (ll& e : es) {
      cin >> e;
      e--;
    }
  }

  vector<bool> ans = solve(n, edges, queries);
  for (bool b : ans) {
    cout << (b ? "YES" : "NO") << '\n';
  }

}