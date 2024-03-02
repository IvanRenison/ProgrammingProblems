// https://codeforces.com/gym/104505/problem/J
#include <bits/stdc++.h>
#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; ++i)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

optional<vi> solve(vii SSs, const vi& res) {
  ll n = SSs.size(), m = res.size();

  vector<set<ll>> g_sets(m);
  vector<vii> g(m);

  fore(e, 0, n) {
    auto [s0, s1] = SSs[e];
    if (!g_sets[s0].count(s1)) {
      g[s0].push_back({s1, e}), g[s1].push_back({s0, e});
      g_sets[s0].insert(s1), g_sets[s1].insert(s0);
    }
  }

  vector<bool> vis(m, false);

  vector<bool> used(n, false);

  fore(u, 0, m) {
    if (!vis[u]) {
      vi h_edges_e, h_nodes = {u};

      vi stack = {u};
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

      vi ones;

      for (ll s : h_nodes) {
        if (res[s] == 1) {
          ones.push_back(s);
        }
      }

      if (ones.size() % 2 != 0) {
        return {};
      }

      map<ll, ll> h_nodes_compressed;
      fore(i, 0, h_n) {
        h_nodes_compressed[h_nodes[i]] = i;
      }

      assert(h_nodes_compressed.size() == h_n);

      vector<vii> h(h_n);
      for (ll e : h_edges_e) {
        auto [s0, s1] = SSs[e];
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

  vi ans;
  fore(i, 0, n) {
    if (used[i]) {
      ans.push_back(i);
    }
  }

  return ans;
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);

  ll n, m;
  cin >> n >> m;
  vii SSs(n);
  for (auto& [s0, s1] : SSs) {
    cin >> s0 >> s1;
    s0--, s1--;
  }
  vector<ll> res(m);
  for (ll& x : res) {
    cin >> x;
  }

  auto ans = solve(SSs, res);
  if (ans.has_value()) {
    cout << ans->size() << '\n';
    for (ll a : *ans) {
      cout << a + 1 << ' ';
    }
  } else {
    cout << -1;
  }
  cout << '\n';

/*   fore(_, 0, 10000) {
    ll m = 3;
    ll n = rand() % 3 + 2;

    vii SSs(n);
    for (auto& [s0, s1] : SSs) {
      s0 = rand() % m, s1 = rand() % m;
      if (s0 == s1) {
        s1 = (s1 + 1) % m;
      }
    }
    vi res(m);
    for (ll& x : res) {
      x = rand() % 2;
    }

    auto ans = solve(SSs, res);

    if (ans.has_value()) {
      vi res_(m);
      for (ll e : *ans) {
        auto [u, v] = SSs[e];
        res_[u] ^= 1, res_[v] ^= 1;
      }

      if (res != res_) {
        cerr << "FAIL" << endl;
        cerr << n << " " << m << endl;
        for (auto [s0, s1] : SSs) {
          cerr << s0 + 1 << " " << s1 + 1 << endl;
        }
        for (ll x : res) {
          cerr << x << " ";
        }
        cerr << endl;
        cerr << "ans: ";
        for (ll x : *ans) {
          cerr << x << " ";
        }
        cerr << endl;
        cerr << "res_: ";
        for (ll x : res_) {
          cerr << x << " ";
        }
        cerr << endl;

        return EXIT_FAILURE;
      }
    }

  } */

  return 0;
}
