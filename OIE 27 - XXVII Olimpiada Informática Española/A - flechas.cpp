// https://codeforces.com/gym/104604

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

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()
#define DBG(x) cerr << #x << " = " << x << endl

bool solveLR(const vector<string>& T) {
  for (const string& s : T) {
    bool L = true;
    for (char c : s) {
      if (L) {
        if (c == 'R') {
          L = false;
        }
      } else {
        if (c == 'L') {
          return false;
        }
      }
    }
  }

  return true;
}

bool solveUD(const vector<string>& T) {
  ull n = T.size();
  fore(j, 0, n) {
    bool U = true;
    fore(i, 0, n) {
      char c = T[i][j];
      if (U) {
        if (c == 'D') {
          U = false;
        }
      } else {
        if (c == 'U') {
          return false;
        }
      }
    }
  }

  return true;
}

/**
 * Author: Lukas Polacek
 * Date: 2009-10-28
 * License: CC0
 * Source: Czech graph algorithms book, by Demel. (Tarjan's algorithm)
 * Description: Finds strongly connected components in a
 * directed graph. If vertices $u, v$ belong to the same component,
 * we can reach $u$ from $v$ and vice versa.
 * Usage: scc(graph, [\&](vi\& v) { ... }) visits all components
 * in reverse topological order. comp[i] holds the component
 * index of a node (a component only has edges to components with
 * lower index). ncomps will contain the number of components.
 * Time: O(E + V)
 * Status: Bruteforce-tested for N <= 5
 */
vi val, comp, z, cont;
ll Time, ncomps;
template<class G, class F> ll dfs(ll j, G& g, F& f) {
  ll low = val[j] = ++Time, x; z.push_back(j);
  for (auto e : g[j]) if (comp[e] < 0)
    low = min(low, val[e] ?: dfs(e,g,f));

  if (low == val[j]) {
    do {
      x = z.back(); z.pop_back();
      comp[x] = ncomps;
      cont.push_back(x);
    } while (x != j);
    f(cont); cont.clear();
    ncomps++;
  }
  return val[j] = low;
}
template<class G, class F> void scc(G& g, F f) {
  ll n = g.size();
  val.assign(n, 0); comp.assign(n, -1);
  Time = ncomps = 0;
  fore(i,0,n) if (comp[i] < 0) dfs(i, g, f);
}



bool solve1(const vector<string>& T) {
  if (!(solveLR(T) && solveUD(T))) {
    return false;
  }

  ull n = T.size();

  vector<vu> adj(n*n);

  fore(i, 0, n) {
    ull lastR = -1;
    fore(j, 0, n) {
      if (T[i][j] == 'R') {
        lastR = i*n + j;
      } else if ((T[i][j] == 'U' || T[i][j] == 'D') && lastR != -1) {
        adj[lastR].push_back(i*n + j);
      }
    }
  }

  fore(i, 0, n) {
    ull lastL = -1;
    for (ull j = n - 1; j < n; j--) {
      if (T[i][j] == 'L') {
        lastL = i*n + j;
      } else if ((T[i][j] == 'U' || T[i][j] == 'D') && lastL != -1) {
        adj[lastL].push_back(i*n + j);
      }
    }
  }

  fore(j, 0, n) {
    ull lastD = -1;
    fore(i, 0, n) {
      if (T[i][j] == 'D') {
        lastD = i*n + j;
      } else if ((T[i][j] == 'L' || T[i][j] == 'R') && lastD != -1) {
        adj[lastD].push_back(i*n + j);
      }
    }
  }

  fore(j, 0, n) {
    ull lastU = -1;
    for (ull i = n - 1; i < n; i--) {
      if (T[i][j] == 'U') {
        lastU = i*n + j;
      } else if ((T[i][j] == 'L' || T[i][j] == 'R') && lastU != -1) {
        adj[lastU].push_back(i*n + j);
      }
    }
  }

  bool ans = true;

  scc(adj, [&](vi& v) {
    if (v.size() > 1) {
      ans = false;
    }
  });

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;
    vector<string> T(n);
    for(string& s : T) {
      cin >> s;
    }

    if (solve1(T)) {
      cout << "POSIBLE\n";
    } else {
      cout << "IMPOSIBLE\n";
    }
  }

  return EXIT_SUCCESS;
}
