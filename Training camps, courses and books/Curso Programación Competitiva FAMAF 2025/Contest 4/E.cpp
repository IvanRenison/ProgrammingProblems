// https://codeforces.com/group/Xaa6lwRoge/contest/635590/problem/E

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


vu solve(vu& ps, vuu& sws) {
  ull n = ps.size();

  vector<vu> adj(n);
  for (auto [a, b] : sws) {
    adj[a].push_back(b), adj[b].push_back(a);
  }

  vector<vu> grups;
  vector<vu> grups_vals;

  vb vis(n);
  fore(a, 0, n) if (!vis[a]) {
    vis[a] = true;
    vu s = {a};
    grups.push_back({a});
    grups_vals.push_back({ps[a]});

    for (ull i = 0; i < s.size(); i++) {
      ull b = s[i];
      for (ull c : adj[b]) {
        if (!vis[c]) {
          vis[c] = true;
          s.push_back(c);
          grups.back().push_back(c);
          grups_vals.back().push_back(ps[c]);
        }
      }
    }
  }

  vu ans(n);

  fore(i, 0, grups.size()) {
    sort(ALL(grups[i]));
    sort(ALL(grups_vals[i]));
    reverse(ALL(grups_vals[i]));

    fore(j, 0, grups[i].size()) {
      ans[grups[i][j]] = grups_vals[i][j];
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull n, m;
  cin >> n >> m;
  vu ps(n);
  for (ull& p : ps) {
    cin >> p;
    p--;
  }
  vuu sws(m);
  for (auto& [a, b] : sws) {
    cin >> a >> b;
    a--, b--;
  }

  auto ans = solve(ps, sws);
  for (ull p : ans) {
    cout << p + 1 << ' ';
  }
  cout << '\n';

}
