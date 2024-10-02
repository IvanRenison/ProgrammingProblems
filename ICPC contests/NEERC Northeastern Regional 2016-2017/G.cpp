// https://codeforces.com/gym/101190

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
typedef long double ld;
typedef vector<ld> vd;
typedef pair<ld, ld> dd;
typedef vector<dd> vdd;
typedef tuple<ld, ld, ld> ddd;
typedef vector<ddd> vddd;
typedef tuple<ld, ld, ld, ld> dddd;
typedef vector<dddd> vdddd;
typedef vector<bool> vb;
typedef pair<bool, bool> bb;
typedef vector<bb> vbb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;
const ld eps = 1e-7;


pair<string, string> solve(ull n, const vuu& edges) {
  vector<vu> adj(n), adj_back(n);
  vu out_deg(n);
  for (auto [u, v] : edges) {
    adj[u].push_back(v), adj_back[v].push_back(u);
    out_deg[u]++;
  }

  vector<array<bool, 2>> dp_inf(n, {true, false});
  // dp_inf[u].first iff fst can make the game infinite
  // dp_inf[u].second iff snd can make the game finite
  {
    vu fst_deg = out_deg;
    vbb vis(n, {false, false});

    vector<pair<ull, bool>> s;
    fore(u, 0, n) {
      if (out_deg[u] == 0) {
        s.push_back({u, true}), s.push_back({u, false});
        vis[u] = {true, true};
      }
    }
    if (s.empty()) {
      return {string(n, 'D'), string(n, 'D')};
    }

    while (!s.empty()) {
      auto [u, p] = s.back();
      s.pop_back();

      if (!p) { // fst cant make infinite the game from u
        dp_inf[u][0] = false;

        for (ull v : adj_back[u]) {
          if (!vis[v].second) {
            s.push_back({v, true});
            vis[v].second = true;
          }
        }
      } else { // snd can make finite the game from u
        dp_inf[u][1] = true;

        for (ull v : adj_back[u]) {
          assert(fst_deg[v] > 0);
          fst_deg[v]--;
          if (fst_deg[v] == 0) {
            s.push_back({v, false});
            vis[v].first = true;
          }
        }
      }
    }
  }


  vector<array<bool, 2>> dp_win(n, {false, false});
  // Can win for when game is not infinite

  {
    vector<array<ull, 2>> out_degs(n, {inf, inf});
    vector<array<bool, 2>> vis(n, {false, false});
    vuu s;
    fore(u, 0, n) {
      if (!dp_inf[u][0]) {
        out_degs[u][0] = out_deg[u];
      }
      if (dp_inf[u][1]) {
        out_degs[u][1] = 0;
        for (ull v : adj[u]) {
          if (!dp_inf[v][0]) {
            out_degs[u][1]++;
          }
        }
      }

      fore(p, 0, 2) {
        if (out_degs[u][p] == 0) {
          s.push_back({u, p});
          vis[u][p] = true;
        }
      }
    }

    while (!s.empty()) {
      auto [u, p] = s.back();
      s.pop_back();

      if (dp_win[u][p]) {
        for (ull v : adj_back[u]) if (dp_inf[v][!p] != p && !vis[v][!p]) {
          assert(out_degs[v][!p] > 0);
          out_degs[v][!p]--;
          if (out_degs[v][!p] == 0) {
            s.push_back({v, !p});
            vis[v][!p] = true;
          }
        }
      } else {
        for (ull v : adj_back[u]) if (dp_inf[v][!p] != p && !vis[v][!p]) {
          dp_win[v][!p] = true;
          s.push_back({v, !p});
          vis[v][!p] = true;
        }
      }
    }
  }

  fore(u, 0, n) {
    if (!dp_inf[u][0] && !dp_win[u][0]) {
      for (ull v : adj[u]) {
        if (!dp_win[v][1]) {
          dp_win[u][0] = true;
          break;
        }
      }
    }
  }

  string fst(n, '.'), snd(n, '.');
  fore(u, 0, n) {
    if (dp_inf[u][0]) {
      fst[u] = 'D';
    } else {
      if (dp_win[u][0]) {
        fst[u] = 'W';
      } else {
        fst[u] = 'L';
      }
    }
    if (!dp_inf[u][1]) {
      snd[u] = 'D';
    } else {
      if (dp_win[u][1]) {
        snd[u] = 'W';
      } else {
        snd[u] = 'L';
      }
    }
  }

  return {fst, snd};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
#ifdef ONLINE_JUDGE
  freopen("game.in", "r", stdin);
  freopen("game.out", "w", stdout);
#endif

  ull n, m;
  cin >> n >> m;
  vuu edges(m);
  for (auto& [u, v] : edges) {
    cin >> u >> v;
    u--, v--;
  }
  auto [ans0, ans1] = solve(n, edges);
  cout << ans0 << '\n' << ans1 << '\n';
}
