// https://codeforces.com/group/YjFmW2O15Q/contest/101881/problem/E

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define DBG(x) cerr << #x << " = " << x << endl

// Check that all apps can reach 0
bool check_reach(ull i, ull j, const vector<vu>& Tss) {
  ull N = Tss.size(), M = Tss[0].size();

  vector<vb> vis(N, vb(N, false));
  vuu s = {{i, j}};
  vis[i][j] = true;
  while (!s.empty()) {
    auto [u, v] = s.back();
    s.pop_back();

    fore(k, 0, M) {
      ull nu = Tss[u][k], nv = Tss[v][k];
      if (nu == 0 && nv == 0) {
        return true;
      }
      if (!vis[nu][nv]) {
        vis[nu][nv] = true;
        s.push_back({nu, nv});
      }
    }
  }

  return false;
}

bool solve(const vector<vu>& Tss) {
  ull N = Tss.size();

  vector<vb> checked(N, vb(N, false));

  fore(i, 0, N) {
    fore(j, 0, N) if (i != j) {
      bool found = false;
      fore(k, 0, N) {
        if (checked[i][k] && checked[k][j]) {
          found = true;
          break;
        }
      }
      if (!found && !check_reach(i, j, Tss)) {
        return false;
      }
      checked[i][j] = checked[j][i] = true;
    }
  }

  return true;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull N, M;
  cin >> N >> M;
  vector<vu> Tss(N, vu(M));
  for (vu& Ts : Tss) {
    for (ull& T : Ts) {
      cin >> T;
      T--;
    }
  }

  bool ans = solve(Tss);
  if (ans) {
    cout << "S\n";
  } else {
    cout << "N\n";
  }

}
