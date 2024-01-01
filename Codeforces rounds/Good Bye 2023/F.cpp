// https://codeforces.com/contest/1916/problem/F

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()
#define sz(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;

struct Bicomps {
  vi num, st;
  vector<vector<ii>> ed;
  ll Time;
  vuu edges;
  //ull bridges_count = 0; //
  vu bridges_in;
  Bicomps(ll N, const vuu& edges) : Time(0), edges(edges), bridges_in(N) {
    ull eid = 0;
    ed.resize(N);
    for (auto [a, b] : edges) {
      ed[a].emplace_back(b, eid);
      ed[b].emplace_back(a, eid++);
    }
  }
  template<class F>
  ll dfs(ll at, ll par, F& f) {
    ll me = num[at] = ++Time, e, y, top = me;
    for (auto pa : ed[at]) if (pa.second != par) {
      tie(y, e) = pa;
      if (num[y]) {
        top = min(top, num[y]);
        if (num[y] < me)
          st.push_back(e);
      } else {
        ll si = sz(st);
        ll up = dfs(y, e, f);
        top = min(top, up);
        if (up == me) {
          st.push_back(e);
          f(vi(st.begin() + si, st.end()));
          st.resize(si);
        }
        else if (up < me) st.push_back(e);
        else { /* e is a bridge */
          //bridges_count++; //
          auto [u, v] = edges[e];
          bridges_in[u]++, bridges_in[v]++;
        }
      }
    }
    return top;
  }

  template<class F>
  void bicomps(F f) {
    num.assign(sz(ed), 0);
    fore(i,0,sz(ed)) if (!num[i]) dfs(i, -1, f);
  }

  vu ncomps_each() {
    ull N = ed.size();
    vu ans(N);
    bicomps([&](const vi& comp) {
      vb in_comp(N, false);
      for (ll x : comp) {
        auto [u, v] = edges[x];
        in_comp[u] = in_comp[v] = true;
      }
      fore(u, 0, N) {
        if (in_comp[u]) {
          ans[u]++;
        }
      }
    });

    fore(u, 0, N) {
      ans[u] += bridges_in[u];
    }

    return ans;
  }

  /* ull ncomps() {
    ull ans;
    bicomps([&](const vi&) {
      ans++;
    });

    return ans;
  } */
};

pair<vu, vu> solve1(ull n0, ull n1, vuu edges) {
  ull n = n0 + n1;

  vector<vu> adj(n);
  for (auto [u, v] : edges) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vb in_s0(n, false);
  vu s0 = {0};
  in_s0[0] = true;

  fore(_, 1, n0) {

    vuu new_edges;
    for (auto [u, v] : edges) {
      if (!in_s0[u] && !in_s0[v]) {
        new_edges.push_back({u, v});
      }
    }

    Bicomps bicomps(n, new_edges);

    vu ncomps = bicomps.ncomps_each();

    bool found = false;
    fore(u, 0, n) {
      if (!in_s0[u] && (ncomps[u] == 1)) {
        for (ull v : adj[u]) {
          if (in_s0[v]) {
            found = true;
          }
        }
        if (found) {
          in_s0[u] = true;
          s0.push_back(u);
          break;
        }
      }
    }
    assert(found);
  }


  vu s1;
  fore(u, 0, n) {
    if (!in_s0[u]) {
      s1.push_back(u);
    }
  }

  return {s0, s1};
}

/* bool validGraph(ull n, const vuu& edges) {
  vector<vu> adj(n);
  for (auto [u, v] : edges) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vb vis(n);
  vis[0] = true;
  vu st = {0};
  while (!st.empty()) {
    ull u = st.back();
    st.pop_back();
    for (ull v : adj[u]) {
      if (!vis[v]) {
        vis[v] = true;
        st.push_back(v);
      }
    }
  }

  fore(i, 0, n) {
    if (!vis[i]) {
      return false;
    }
  }

  Bicomps bicomps(n, edges);
  ull ncomps = bicomps.ncomps();
  return ncomps == 1 && bicomps.bridges_count == 0;
}

bool check(ull n0, ull n1, const vuu& edges, vu s0, vu s1) {
  ull n = n0 + n1;

  vb in_s0(n, false);
  for (ull a : s0) {
    in_s0[a] = true;
  }

  vector<vu> adj0(n), adj1(n);
  for (auto [u, v] : edges) {
    if (in_s0[u] && in_s0[v]) {
      adj0[u].push_back(v);
      adj0[v].push_back(u);
    } else if (!in_s0[u] && !in_s0[v]) {
      adj1[u].push_back(v);
      adj1[v].push_back(u);
    }
  }

  vb vis0(n, false);
  vis0[s0[0]] = true;
  vu st0 = {s0[0]};
  while (!st0.empty()) {
    ull u = st0.back();
    st0.pop_back();
    for (ull v : adj0[u]) {
      if (!vis0[v]) {
        vis0[v] = true;
        st0.push_back(v);
      }
    }
  }

  vb vis1(n, false);
  vis1[s1[0]] = true;
  vu st1 = {s1[0]};
  while (!st1.empty()) {
    ull u = st1.back();
    st1.pop_back();
    for (ull v : adj1[u]) {
      if (!vis1[v]) {
        vis1[v] = true;
        st1.push_back(v);
      }
    }
  }

  fore(i, 0, n) {
    if ((in_s0[i] && !vis0[i]) || (!in_s0[i] && !vis1[i])) {
      return false;
    }
  }

  return true;
} */

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n1, n2, m;
    cin >> n1 >> n2 >> m;
    set<uu> edges;
    fore(i, 0, m) {
      ull u, v;
      cin >> u >> v;
      u--, v--;
      if (u > v) {
        swap(u, v);
      }
      edges.insert({u, v});
    }

    auto [s1, s2] = solve1(n1, n2, vuu(all(edges)));
    for (ull a : s1) {
      cout << a + 1 << ' ';
    }
    cout << '\n';
    for (ull a : s2) {
      cout << a + 1 << ' ';
    }
    cout << '\n';
  }

/*   fore(_, 0, 1000) {
    ull n1 = rand() % 5 + 2, n2 = rand() % 5 + 2, m = n1 + n2 + rand() % 3;
    ull n = n1 + n2;
    set<uu> edges;
    while (edges.size() < m) {
      ull u = rand() % n;
      ull v = rand() % n;
      if (u > v) {
        swap(u, v);
      }
      if (u != v) {
        edges.insert({u, v});
      }
    }

    if (!validGraph(n, vuu(all(edges)))) {
      continue;
    }

    auto [s1, s2] = solve1(n1, n2, vuu(all(edges)));

    if (!check(n1, n2, vuu(all(edges)), s1, s2)) {
      cerr << "ERROR:\nInput:\n";
      cerr << n1 << ' ' << n2 << ' ' << m << '\n';
      for (auto [u, v] : edges) {
        cerr << u + 1 << ' ' << v + 1 << '\n';
      }
      cerr << "Output:\n";
      for (ull a : s1) {
        cerr << a + 1 << ' ';
      }
      cerr << '\n';
      for (ull a : s2) {
        cerr << a + 1 << ' ';
      }
      cerr << '\n';
      return EXIT_FAILURE;
    }
  } */

  return EXIT_SUCCESS;
}
