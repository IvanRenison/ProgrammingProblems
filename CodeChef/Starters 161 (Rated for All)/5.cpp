// https://www.codechef.com/problems/QUICKEXIT0

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


ull solve(ull K, vuu& edges) {
  ull N = edges.size() + 1;

  vector<vu> adj(N);
  for (auto& [u, v] : edges) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vector<vu> suns(N);
  vu pars(N, -1);

  {
    vuu st;
    st.push_back({0, -1});
    while (!st.empty()) {
      auto [u, p] = st.back();
      st.pop_back();

      for (auto v : adj[u]) {
        if (v != p) {
          st.push_back({v, u});
          suns[u].push_back(v);
          pars[v] = u;
        }
      }
    }
  }

  vu sub_tree_sizes(N);
  {
    function<void(ull)> dfs = [&](ull u) {
      sub_tree_sizes[u] = 1;
      for (auto v : suns[u]) {
        dfs(v);
        sub_tree_sizes[u] += sub_tree_sizes[v];
      }
    };
    dfs(0);
  }

  vu Ps(N, -1);
  Ps[N - 1] = K;
  ull big = N - 1;
  big -= big == K;

  vuu for_small;

  ull ans = 1;

  for (ull i = pars[N - 1], j = N - 1; i != -1; j = i, i = pars[i]) {
    ans++;
    Ps[i] = big;
    big--;
    big -= big == K;
    for (ull u : suns[i]) if (u != j) {
      for_small.push_back({sub_tree_sizes[u], u});
    }
  }

  sort(ALL(for_small));
  reverse(ALL(for_small));

  ull small = 0;
  small += small == K;

  for (auto [tam, u] : for_small) {
    Ps[u] = small;
    if (Ps[u] > K) {
      ans += tam;
    }
    small++;
    small += small == K;
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  fore(tc, 0, t) {
    ull N, K;
    cin >> N >> K;
    K--;
    vuu edges(N - 1);
    for (auto& [u, v] : edges) {
      cin >> u >> v;
      u--, v--;
    }


    auto ans = solve(K, edges);
    cout << ans << '\n';
  }

}
