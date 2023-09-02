// https://codeforces.com/gym/101243
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(), x.end()
#define SZ(x) ((int)x.size())
#define fore(i, a, b) for (ull i = a, thxMat = b; i < thxMat; ++i)
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

struct UF {
  ull n;
  vector<ll> e;
  vector<pair<ll, ll>> st;
  UF(ll n) : n(n), e(n, -1) {}
  ll find(ll x) {
    return e[x] < 0 ? x : find(e[x]);
  }
  bool join(ll a, ll b) {
    a = find(a), b = find(b);
    if (a == b) {
      return false;
    }
    if (e[a] > e[b]) {
      swap(a, b);
    }
    st.push_back({a, e[a]});
    st.push_back({b, e[b]});
    e[a] += e[b];
    e[b] = a;
    return true;
  }
};

vector<char>
solve(ull n, vector<pair<ull, ull>> edges_e, vector<pair<ull, ull>> edges_l) {
  UF uf(n);

  for (auto [u, v] : edges_e) {
    uf.join(u, v);
  }

  map<ull, ull> new_names;
  map<ull, vector<ull>> old_names;
  ull new_n = 0;

  fore(u, 0, n) {
    ull uf_u = uf.find(u);
    if (new_names.count(uf_u) == 0) {
      new_names[uf_u] = new_n;
      new_n++;
    }
    old_names[new_names[uf_u]].push_back(u);
  }

  set<pair<ull, ull>> new_edges;
  for (auto [u, v] : edges_l) {
    ull uf_u = uf.find(u), uf_v = uf.find(v);
    new_edges.insert({new_names[uf_u], new_names[uf_v]});
  }

  vector<vector<ull>> adj_front(new_n), adj_back(new_n);
  for (auto [u, v] : new_edges) {
    adj_front[u].push_back(v);
    adj_back[v].push_back(u);
  }

  vector<ull> front_level(new_n, -1);
  fore(u, 0, new_n) {
    if (adj_back[u].size() == 0) {
      front_level[u] = 0;
    }
  }
  fore(x, 1, 3) {
    fore(u, 0, new_n) if (front_level[u] == -1ull) {
      bool all_valid = true;
      for (ull v : adj_back[u]) {
        if (front_level[v] >= x) {
          all_valid = false;
          break;
        }
      }
      if (all_valid) {
        front_level[u] = x;
      }
    }
  }

  vector<ull> back_level(new_n, -1);
  fore(u, 0, new_n) {
    if (adj_front[u].size() == 0) {
      back_level[u] = 0;
    }
  }
  fore(x, 1, 3) {
    fore(u, 0, new_n) if (back_level[u] == -1ull) {
      bool all_valid = true;
      for (ull v : adj_front[u]) {
        if (back_level[v] >= x) {
          all_valid = false;
          break;
        }
      }
      if (all_valid) {
        back_level[u] = x;
      }
    }
  }

  vector<char> ans(n, '?');
  fore(u, 0, new_n) {
    if (front_level[u] == 2 - back_level[u]) {
      for(ull i : old_names[u]) {
        ans[i] = "BRW"[front_level[u]];
      }
    }
  }

  return ans;
}

int main() {
  FIN;
#ifdef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif

  ull n, m;
  cin >> n >> m;
  vector<pair<ull, ull>> edges_e, edges_l;
  fore(_, 0, m) {
    ull u, v;
    char c;
    cin >> u >> c >> v;
    u--, v--;
    if (c == '=') {
      edges_e.push_back({u, v});
    } else if (c == '<') {
      edges_l.push_back({u, v});
    } else {
      edges_l.push_back({v, u});
    }
  }

  auto ans = solve(n, edges_e, edges_l);
  for (char c : ans) {
    cout << c;
  }
  cout << '\n';

  return 0;
}
