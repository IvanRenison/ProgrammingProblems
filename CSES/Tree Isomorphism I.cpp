// https://cses.fi/problemset/task/1700

#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef tuple<ull, ull, ull> uuu;
typedef vector<uuu> vuuu;
typedef tuple<ull, ull, ull, ull> uuuu;
typedef vector<uuuu> vuuuu;
typedef tuple<ull, ull, ull, ull, ull> uuuuu;
typedef vector<uuuuu> vuuuuu;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;
typedef tuple<ll, ll, ll, ll> iiii;
typedef vector<iiii> viiii;
typedef tuple<ll, ll, ll, ll, ll> iiiii;
typedef vector<iiiii> viiiii;
typedef long double ld;
typedef vector<ld> vd;
typedef pair<ld, ld> dd;
typedef vector<dd> vdd;
typedef tuple<ld, ld, ld> ddd;
typedef vector<ddd> vddd;
typedef tuple<ld, ld, ld, ld> dddd;
typedef vector<dddd> vdddd;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;
const ld eps = 1e-7;

// Arithmetic mod 2^64-1 from kactlpp
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
static const H C = (ull)1e11+3; // (order ~ 3e9; random also ok)

// Struct that computes rooted tree hashes for each subtree in O(N)
// Idea: https://codeforces.com/blog/entry/113465
struct TreeHash {
  ull n;
  vector<vu> adj;
  vector<H> hashes;

  TreeHash(vector<vu>& adj_, ull root = 0) : n(adj_.size()), adj(adj_), hashes(n) {
    dfs(root, -1);
  }

  H dfs(ull u, ull p) {
    vector<H> suns_hashes;
    for (ull v : adj[u]) if (v != p) {
      suns_hashes.push_back(dfs(v, u));
    }
    sort(ALL(suns_hashes));
    H hash = 42;
    H pow = 1;
    fore(i, 0, suns_hashes.size()) {
      hash = hash * C + suns_hashes[i] * suns_hashes[i] + suns_hashes[i] * pow;
      pow = pow * C;
    }
    return hashes[u] = hash;
  }
};

bool rooted_tree_iso(vector<vu>& adj0, vector<vu>& adj1, ull root0 = 0, ull root1 = 0) {
  TreeHash th0(adj0, root0);
  TreeHash th1(adj1, root1);
  return th0.hashes[root0] == th1.hashes[root1];
}

bool solve(const vuu& edges0, const vuu& edges1) {
  ull n = edges0.size() + 1;

  vector<vu> adj0(n), adj1(n);
  for (auto [u, v] : edges0) {
    adj0[u].push_back(v);
    adj0[v].push_back(u);
  }
  for (auto [u, v] : edges1) {
    adj1[u].push_back(v);
    adj1[v].push_back(u);
  }

  bool ans = rooted_tree_iso(adj0, adj1);
  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;
    vuu edges0(n - 1), edges1(n - 1);
    for (auto& [u, v] : edges0) {
      cin >> u >> v;
      u--, v--;
    }
    for (auto& [u, v] : edges1) {
      cin >> u >> v;
      u--, v--;
    }

    bool ans = solve(edges0, edges1);
    if (ans) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }

}
