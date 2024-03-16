// https://atcoder.jp/contests/abc345/tasks/abc345_f

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


optional<vi> solve(ull N, ull K, const vii& edges) {
  ull M = edges.size();
  if (K % 2 != 0) {
    return {};
  }

  vector<set<ll>> g_sets(N);
  vector<vii> g(N);

  fore(e, 0, M) {
    auto [s0, s1] = edges[e];
    if (!g_sets[s0].count(s1)) {
      g[s0].push_back({s1, e}), g[s1].push_back({s0, e});
      g_sets[s0].insert(s1), g_sets[s1].insert(s0);
    }
  }

  vector<bool> vis(N, false);

  vector<bool> used(M, false);

  fore(u, 0, N) {
    if (K == 0) {
      break;
    }
    if (!vis[u]) {
      vi h_edges_e, h_nodes = {(ll)u};

      vi stack = {(ll)u};
      vis[u] = true;
      while (!stack.empty()) {
        ll v = stack.back();
        stack.pop_back();

        for (auto [w, e] : g[v]) {
          if (!vis[w]) {
            h_edges_e.push_back(e);
            h_nodes.push_back(w);

            vis[w] = true;
            stack.push_back(w);
          }
        }
      }

      ll h_n = h_nodes.size();

      vi ones = h_nodes;

      if (h_n % 2 != 0) {
        ones.pop_back();
      }

      while (ones.size() > K) {
        ones.pop_back();
        ones.pop_back();
      }

      K -= ones.size();

      map<ll, ll> h_nodes_compressed;
      fore(i, 0, h_n) {
        h_nodes_compressed[h_nodes[i]] = i;
      }

      assert(h_nodes_compressed.size() == h_n);

      vector<vii> h(h_n);
      for (ll e : h_edges_e) {
        auto [s0, s1] = edges[e];
        ll v = h_nodes_compressed[s0], w = h_nodes_compressed[s1];
        h[v].push_back({w, e}), h[w].push_back({v, e});
      }

      vector<ll> pre_xors(h_n, 0);

      fore(i, 0, ones.size() / 2) {
        ll s0 = ones[2 * i], s1 = ones[2 * i + 1];
        ll v = h_nodes_compressed[s0], w = h_nodes_compressed[s1];

        assert(pre_xors[v] == 0);
        assert(pre_xors[w] == 0);

        pre_xors[v] ^= 1, pre_xors[w] ^= 1;
      }

      vector<ll> xors(h_n, -1);

      fore(i, 0, h_n) {
        ll s = h_nodes[h_n - 1 - i];
        ll v = h_nodes_compressed[s];
        assert(xors[v] == -1);

        xors[v] = pre_xors[v];

        ll p_e = -1;

        for (auto [w, e] : h[v]) {
          if (xors[w] != -1) {
            xors[v] ^= xors[w];
          } else {
            assert(p_e == -1);
            p_e = e;
          }
        }

        assert((p_e != -1) != (s == u));
        if (p_e != -1) {
          if (xors[v] == 1) {
            assert(!used[p_e]);
            used[p_e] = true;
          }
        }
      }

      assert(xors[h_nodes_compressed[u]] == 0);
    }
  }

  if (K > 0) {
    return {};
  }

  vi ans;
  fore(i, 0, M) {
    if (used[i]) {
      ans.push_back(i);
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull N, M, K;
  cin >> N >> M >> K;
  vii edges(M);
  for (auto& [u, v] : edges) {
    cin >> u >> v;
    u--, v--;
  }

  auto ans = solve(N, K, edges);

  if (ans.has_value()) {
    cout << "Yes\n";
    cout << ans->size() << '\n';
    for (ull e : *ans) {
      cout << e + 1 << ' ';
    }
    cout << '\n';
  } else {
    cout << "No\n";
  }

  return EXIT_SUCCESS;
}
