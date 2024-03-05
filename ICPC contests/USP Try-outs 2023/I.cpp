// https://codeforces.com/gym/104505/problem/I

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
#define all(x) x.begin(), x.end()
#define sz(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;
const ld eps = 1e-7;


vector<vu> solve(ull n, const vuu& edges, const vu& queries) {
  ull q = queries.size();

  vector<vu> adj(n);
  for (auto [u, v] : edges) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vb active(n, true);

  for (ull u : queries) {
    if (u != inf) {
      active[u] = false;
    }
  }

  vb corn(n, false);

  fore(u, 0, n) {
    if (active[u]) {
      array<ull, 2> cnts = {0, 0};
      for (ull v : adj[u]) {
        if (active[v] && v < u) {
          cnts[corn[v]]++;
        }
      }

      corn[u] = cnts[true] < cnts[false];
    }
  }

  vector<vu> ans;

  fore(i, 0, q) {
    ull u = queries[q - 1 - i];
    if (u == inf) {
      ans.push_back({});
      fore(v, 0, n) {
        if (corn[v]) {
          assert(active[v]);
          ans.back().push_back(v);
        }
      }
    } else {
      array<ull, 2> cnts = {0, 0};
      for (ull v : adj[u]) {
        if (active[v]) {
          cnts[corn[v]]++;
        }
      }

      corn[u] = cnts[true] < cnts[false];
      active[u] = true;
    }
  }

  reverse(all(ans));

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull n, m, q;
  cin >> n >> m >> q;
  vuu edges(m);
  for (auto& [u, v] : edges) {
    cin >> u >> v;
    u--; v--;
  }
  vu queries(q, inf);
  for (auto& u : queries) {
    ull ty;
    cin >> ty;
    if (ty == 1) {
      cin >> u;
      u--;
    }
  }

  auto ans = solve(n, edges, queries);
  for (vu& v : ans) {
    cout << v.size();
    for (ull x : v) {
      cout << ' ' << x + 1;
    }
    cout << '\n';
  }

  return EXIT_SUCCESS;
}
