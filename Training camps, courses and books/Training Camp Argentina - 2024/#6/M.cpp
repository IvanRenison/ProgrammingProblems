// https://codeforces.com/group/5GNF7zti59/contest/534709/problem/M
#include<bits/stdc++.h>
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i =a,gmat=b;i<gmat;++i)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;

/** Author: Simon Lindholm
 * Date: 2015-03-15
 * License: CC0
 * Source: own work
 * Description: Self-explanatory methods for string hashing.
 * Status: stress-tested
 */
// Arithmetic mod 2^64-1. 2x slower than mod 2^64 and more
// code, but works on evil test data (e.g. Thue-Morse, where
// ABBA... and BAAB... of length 2^10 hash the same mod 2^64).
// "typedef ull H;" instead if you think test data is random,
// or work mod 10^9+7 if the Birthday paradox is not a problem.
typedef uint64_t ull;
struct H {
  ull x; H(ull x=0) : x(x) {}
  H operator+(H o) { return x + o.x + (x + o.x < x); }
  H operator-(H o) { return *this + ~o.x; }
  H operator*(H o) { auto m = (__uint128_t)x * o.x;
    return H((ull)m) + (ull)(m >> 64); }
  ull get() const { return x + !~x; }
  bool operator==(H o) const { return get() == o.get(); }
  bool operator<(H o) const { return get() < o.get(); }
};
static const H C = (ll)1e11+3; // (order ~ 3e9; random also ok)

struct HashInterval {
  vector<H> ha, pw;
  HashInterval(const string& str) : ha(SZ(str)+1), pw(ha) {
    pw[0] = 1;
    fore(i,0,SZ(str))
      ha[i+1] = ha[i] * C + str[i],
      pw[i+1] = pw[i] * C;
  }
  H hashInterval(ll a, ll b) { // hash [a, b)
    return ha[b] - ha[a] * pw[b - a];
  }
};

/** Author: Simon Lindholm
 * Date: 2019-12-31
 * License: CC0
 * Source: folklore
 * Description: Eulerian undirected/directed path/cycle algorithm.
 * Input should be a vector of (dest, global edge index), where
 * for undirected graphs, forward/backward edges have the same index.
 * Returns a list of nodes in the Eulerian path/cycle with src at both start and end, or
 * empty list if no cycle/path exists.
 * To get edge indices back, add .snd to s and ret.
 * Time: O(V + E)
 * Status: stress-tested
 */
vii eulerWalk(const vector<vector<ii>>& gr, ll nedges, ll src=0) {
  ll n = SZ(gr);
  vi D(n), its(n), eu(nedges);
  vii ret, s = {{src, -1}};
  D[src]++; // to allow Euler paths, not just cycles
  while (!s.empty()) {
    auto [x, xe] = s.back();
    ll &it = its[x], end = SZ(gr[x]);
    if (it == end){ ret.push_back({x, xe}); s.pop_back(); continue; }
    auto [y, e] = gr[x][it++];
    if (!eu[e]) {
      D[x]--, D[y]++;
      eu[e] = 1; s.push_back({y, e});
    }}
  for (ll x : D) if (x < 0 || SZ(ret) != nedges+1) return {};
  return {ret.rbegin(), ret.rend()};
}

bool eulerCycleCond(const vector<vector<ii>>& g, ll src=0) {
  ll n = g.size();

  vi in_deg(n);
  fore(u, 0, n) {
    for (auto [v, _] : g[u]) {
      in_deg[v]++;
    }
  }

  fore(i, 0, n) {
    if (in_deg[i] != g[i].size()) {
      return false;
    }
  }

  vector<bool> vis(n, false);
  vi s = {0};
  vis[0] = true;
  while (!s.empty()) {
    ll u = s.back();
    s.pop_back();
    for (auto [v, _] : g[u]) {
      if (!vis[v]) {
        vis[v] = true;
        s.push_back(v);
      }
    }
  }

  fore(i, 0, n) {
    if (!vis[i]) {
      return false;
    }
  }

  return true;
}

optional<pair<vi, vi>> solve(const vector<string>& As, const vector<string>& Bs) {
  ll n = As.size(), m = As[0].size();
  { // Check base
    vi p(n);
    iota(ALL(p), 0);
    vi q = p;

    sort(ALL(p), [&](ll i, ll j) {
      return As[i] < As[j];
    });
    sort(ALL(q), [&](ll i, ll j) {
      return Bs[i] < Bs[j];
    });

    bool eq = true;
    fore(i, 0, n) {
      if (As[p[i]] != Bs[q[i]]) {
        eq = false;
        break;
      }
    }

    if (eq) {
      return {{p, q}};
    }
  }

  vector<HashInterval> HAs, HBs;
  fore(i, 0, n) {
    HAs.push_back(HashInterval(As[i]));
    HBs.push_back(HashInterval(Bs[i]));
  }

  fore(k, 1, m) {
    vector<tuple<pair<H, bool>, pair<H, bool>, ll>> edges;
    fore(i, 0, n) {
      H u = HAs[i].hashInterval(0, k);
      H v = HAs[i].hashInterval(k, m);
      edges.push_back({{u, true}, {v, false}, 2 * i});
      u = HBs[i].hashInterval(0, m - k);
      v = HBs[i].hashInterval(m - k, m);
      edges.push_back({{u, false}, {v, true}, 2 * i + 1});
    }

    map<pair<H, bool>, ll> nodes_ids;
    for (auto [u, v, i] : edges) {
      if (!nodes_ids.count(u)) {
        nodes_ids[u] = nodes_ids.size();
      }
      if (!nodes_ids.count(v)) {
        nodes_ids[v] = nodes_ids.size();
      }
    }

    ll N = nodes_ids.size();
    vector<vector<ii>> g(N);
    vii edges_;
    for (auto [u, v, i] : edges) {
      ll u_id = nodes_ids[u];
      ll v_id = nodes_ids[v];
      g[u_id].push_back({v_id, i});
      edges_.push_back({u_id, v_id});
    }

    if (eulerCycleCond(g)) {

      vii path = eulerWalk(g, edges.size());
      if (path.size() != edges.size() + 1) {
        exit(0);
        return {};
      }

      vi p, q;
      fore(i, 1, path.size()) {
        ll e = path[i].second;
        if (i % 2 == 0) {
          q.push_back(get<2>(edges[e])/2);
        } else {
          p.push_back(get<2>(edges[e])/2);
        }
      }

      return {{p, q}};
    }
  }

  return {};
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll t;
  cin >> t;
  while (t--) {
    ll n, m;
    cin >> n >> m;
    vector<string> As(n), Bs(n);
    for (string& A : As) {
      cin >> A;
    }
    for (string& B : Bs) {
      cin >> B;
    }

    auto ans = solve(As, Bs);
    if (ans) {
      auto [ps, qs] = *ans;
      for (ll p : ps) {
        cout << p + 1 << ' ';
      }
      cout << '\n';
      for (ll q : qs) {
        cout << q + 1 << ' ';
      }
      cout << '\n';
    } else {
      cout << "-1\n";
    }
  }

/*   fore(_, 0, 10000) {
    ll n = rand() % 10 + 1, m = rand() % 10 + 1;
    vector<string> As(n), Bs(n);
    for (string& A : As) {
      fore(_, 0, m) {
        A.push_back('a' + rand() % 26);
      }
    }
    for (string& B : Bs) {
      fore(_, 0, m) {
        B.push_back('a' + rand() % 26);
      }
    }

    auto ans = solve(As, Bs);

  } */

}
