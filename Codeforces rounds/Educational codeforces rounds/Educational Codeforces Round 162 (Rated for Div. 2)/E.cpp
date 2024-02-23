// https://codeforces.com/contest/1923/problem/E

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
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()
#define sz(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;

ull solve1(const vu& cs, const vuu& edges) {
  ull n = cs.size();

  vector<vi> adj(n);
  for (auto [u, v] : edges) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  ull ans = 0;

  vector<map<ull, ull>> counts(n);

  function<void(ull, ull)> dfs = [&](ull u, ull p) {
    ull cu = cs[u];

    ull this_ans = 0;
    for (ull v : adj[u]) {
      if (v != p) {
        dfs(v, u);
        if (counts[v].size() > counts[u].size()) {
          swap(counts[u], counts[v]);
        }
        for (auto [c, cnt] : counts[v]) {
          if (c != cu) {
            this_ans += cnt * counts[u][c];
          }
          counts[u][c] += cnt;
        }
      }
    }

    this_ans += counts[u][cu];

    ans += this_ans;

    counts[u][cu] = 1;;
  };

  dfs(0, inf);

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
    vu cs(n);
    fore(j, 0, n) cin >> cs[j];
    vuu edges(n - 1);
    for (auto& [u, v] : edges) {
      cin >> u >> v;
      --u, --v;
    }

    auto ans = solve1(cs, edges);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
