/* https://codeforces.com/gym/104848/problem/M

Problem in graph 0 cl0 1 cl1 2 … k clk (k + 1)

Let:
  f : {0, 1, 2, …, k + 1} → ℝ → ℝ
  f(i)(t) = min cost to get to node i in time t

We have:

  f(0)(t) = 0
  f(i + 1)(t) = min t' ∈ ℝ(0, t) : f(i)(t - t') + cli / t'

  f(1)(t) = min t' ∈ ℝ(0, t) : f(0)(t - t') + cl0 / t'
          = min t' ∈ ℝ(0, t) : cl0 / t'
          = cl0 / t

  f(2)(t) = min t' ∈ ℝ(0, t) : cl0 / (t - t') + cl1 / t'

    d/dt' ( cl0 / (t - t') + cl1 / t' )
        = - cl0 / (t - t')² + cl1 / t'²

    0 = - cl0 / (t - t')² + cl1 / t'²
    cl1 / t'² = cl0 / (t - t')²
    (t - t')² / t'² = cl0 / cl1
    (t² - 2 t t' + t'²) / t'² = cl0 / cl1
    t² / t'² - 2 t / t' + 1 = cl0 / cl1
    t² / t'² - 2 t / t' + 1 - cl0 / cl1 = 0
    t/t' = (2 ± √(2² - 4 · 1 · (1 - cl0 / cl1))) / 2
    t/t' = 1 ± √(4 - 4 + 4 cl0 / cl1)/2
    t/t' = 1 ± √(4 cl0 / cl1)/2
    t/t' = 1 ± √(cl0 / cl1)
    t/t' = 1 + √(cl0 / cl1)
    t' = t / (1 + √(cl0 / cl1))

⇒
  f(2)(t)
    = cl0 / (t - t / (1 + √(cl0 / cl1)))) + cl1 / (t / (1 + √(cl0 / cl1))))
    = cl0 (1 + √(cl0 / cl1))) / (t ((1 + √(cl0 / cl1))) - t) + cl1 (1 + √(cl0 / cl1)))) / t
    = cl0 (1 + √(cl0 / cl1))) / (t √(cl0 / cl1)) + cl1 (1 + √(cl0 / cl1)))) / t
    = (cl0 / √(cl0 / cl1) + cl1) (1 + √(cl0 / cl1)))) / t
    = (cl0 √cl1 / √cl0 + cl1) (1 + √(cl0 / cl1)))) / t
    = (√cl0 √cl1 + cl1) (1 + √(cl0 / cl1)))) / t
    = (√cl0 √cl1 + cl1 + √cl0 √cl1 √(cl0 / cl1) + cl1 √(cl0 / cl1)) / t
    = (√cl0 √cl1 + cl1 + cl0 + √cl1 √cl0) / t
    = (cl1 + 2 √cl1 √cl0 + cl0) / t
    = (√cl0 + √cl1)² / t


  For f(i + 1) let cl' = (√cl0 + √cl1 + … + √cl(i - 1))² and consider the graph 0' cl' 1' cli (i + 1)
  So using the case f(2) and inductive hipótesis we have:

  f(i + 1)(t)
    = (√cl' + √cli)² / t
    = (√cl0 + √cl1 + … + √cl(i - 1) + √cli)² / t
    = (√cl0 + √cl1 + … + √cli)² / t


  For a general graph we can use Dijkstra with weights √cl

*/
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
typedef long double ld;
typedef vector<ld> vd;
typedef pair<ld, ld> dd;
typedef vector<dd> vdd;
typedef tuple<ld, ld, ld> ddd;
typedef vector<ddd> vddd;
typedef tuple<ld, ld, ld, ld> dddd;
typedef vector<dddd> vdddd;
typedef pair<ull, ld> ud;
typedef vector<ud> vud;
typedef pair<ld, ull> du;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()
#define sz(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;
const ld eps = 1e-7;

template <typename T>
using rpriority_queue = priority_queue<T, vector<T>, greater<T>>;

ld solve(ull n, const vuuu& edges, ull T) {
  vector<vud> adj(n);
  for (auto [u, v, cl] : edges) {
    ld sqrtcl = sqrt((ld)cl);
    adj[u].push_back({v, sqrtcl});
    adj[v].push_back({u, sqrtcl});
  }

  vd vis(n, -1.0);
  rpriority_queue<du> q;
  q.push({0.0, 0});

  while (!q.empty()) {
    auto [d, u] = q.top();
    q.pop();

    if (vis[u] >= 0.0) {
      continue;
    }

    vis[u] = d;

    for (auto [v, w] : adj[u]) {
      if (vis[v] < 0.0) {
        q.push({d + w, v});
      }
    }
  }

  assert(vis[n - 1] > 0.0);
  return vis[n - 1] * vis[n - 1] / T;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n, m, T;
  cin >> n >> m >> T;
  vuuu edges(m);
  for (auto& [u, v, cl] : edges) {
    ull c, l;
    cin >> u >> v >> c >> l;
    u--, v--;
    cl = c * l;
  }

  auto ans = solve(n, edges, T);
  cout << setprecision(10);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
