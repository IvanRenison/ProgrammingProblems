// https://codeforces.com/gym/101047/problem/H
#include <bits/stdc++.h>
#define pb push_back
#define fst first
#define snd second
#define fore(i, a, b) for (int i = a, ggmat = b; i < ggmat; ++i)
#define SZ(x) ((int)x.size())
#define mset(a, v) memset((a), (v), sizeof(a))
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const ll MAXN = 1e3 + 10;
const ll MAXM = 5e3 + 10;

vector<int> g[MAXN];
int n, m;
int mat[MAXM];
bool vis[MAXN];
int match(int x) {
  if (vis[x])
    return 0;
  vis[x] = true;
  for (int y : g[x])
    if (mat[y] < 0 || match(mat[y])) {
      mat[y] = x;
      return 1;
    }
  return 0;
}

vector<pair<int, int>> max_matching() {
  vector<pair<int, int>> r;
  mset(mat, -1);
  fore(i, 0, n) mset(vis, 0), match(i);
  fore(i, 0, m) if (mat[i] >= 0) r.pb({mat[i], i});
  return r;
}

int main() {
  FIN;
  ull T;
  cin >> T;
  while (T--) {
    cin >> n >> m;
    fore(i, 0, m) {
      ll x, y;
      cin >> x >> y;
      --x;
      --y;
      g[x].pb(y);
      g[y].pb(x);
    }
    vector<pair<int, int>> r = max_matching();
    ll res = SZ(r) / 2 + (n - SZ(r));
    cout << res << "\n";
    fore(i, 0, n) g[i].clear();
  }

  return 0;
}