// https://codeforces.com/group/gmV7IkT2pN/contest/525522/problem/E

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
typedef vector<uint> vu;
typedef pair<uint, uint> uu;
typedef vector<uu> vuu;

#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; i++)

optional<pair<vu, vu>> solve(uint n, const vuu& edges) {

  vector<vu> adj(n);
  for (auto [u, v] : edges) {
    adj[u].push_back(v), adj[v].push_back(u);
  }

  vu color(n, -1);

  fore(i, 0, n) {
    if (color[i] == -1) {
      color[i] = 0;
      vu s = {i};

      while (!s.empty()) {
        uint u = s.back();
        s.pop_back();

        uint c = color[u];

        for (uint v : adj[u]) {
          if (color[v] == -1) {
            color[v] = 1 - c;
            s.push_back(v);
          } else if (color[v] == c) {
            return nullopt;
          }
        }
      }
    }
  }

  vu pari, arya;
  fore(i, 0, n) {
    if (color[i] == 0) {
      pari.push_back(i);
    } else {
      arya.push_back(i);
    }
  }

  return {{pari, arya}};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  uint n, m;
  cin >> n >> m;

  vuu edges(m);
  for (auto& [u, v] : edges) {
    cin >> u >> v;
    u--, v--;
  }

  optional<pair<vu, vu>> ans = solve(n, edges);
  if (!ans.has_value()) {
    cout << "-1\n";
  } else {
    auto& [pari, arya] = *ans;
    cout << pari.size() << '\n';
    for (uint u : pari) {
      cout << u + 1 << ' ';
    }
    cout << '\n';
    cout << arya.size() << '\n';
    for (uint u : arya) {
      cout << u + 1 << ' ';
    }
    cout << '\n';
  }

  return EXIT_SUCCESS;
}
