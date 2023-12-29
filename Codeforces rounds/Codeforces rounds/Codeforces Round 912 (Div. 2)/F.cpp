// https://codeforces.com/contest/1903/problem/F

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
#define DBG(x) //cerr << #x << " = " << x << endl

/** Author: Emil Lenngren, Simon Lindholm
 * Date: 2011-11-29
 * License: CC0
 * Source: folklore
 * Description: Calculates a valid assignment to boolean variables a, b, c,... to a 2-SAT problem, so that an expression of the type $(a\|\|b)\&\&(!a\|\|c)\&\&(d\|\|!b)\&\&...$ becomes true, or reports that it is unsatisfiable.
 * Negated variables are represented by bit-inversions (\texttt{\tilde{}x}).
 * Usage:
 *  TwoSat ts(number of boolean variables);
 *  ts.either(0, \tilde3); // Var 0 is true or var 3 is false
 *  ts.setValue(2); // Var 2 is true
 *  ts.atMostOne({0,\tilde1,2}); // <= 1 of vars 0, \tilde1 and 2 are true
 *  ts.solve(); // Returns true iff it is solvable
 *  ts.values[0..N-1] holds the assigned values to the vars
 * Time: O(N+E), where N is the number of boolean variables, and E is the number of clauses.
 * Status: stress-tested
 */
struct TwoSat {
  ll N;
  vector<vi> gr;
  vi values; // 0 = false, 1 = true

  TwoSat(ll n = 0) : N(n), gr(2*n) {}

  ll addVar() { // (optional)
    gr.emplace_back();
    gr.emplace_back();
    return N++;
  }

  void either(ll f, ll j) {
    f = max(2*f, -1-2*f);
    j = max(2*j, -1-2*j);
    gr[f].push_back(j^1);
    gr[j].push_back(f^1);
  }
  void setValue(ll x) { either(x, x); }

/*   void atMostOne(const vi& li) { // (optional)
    if (sz(li) <= 1) return;
    ll cur = ~li[0];
    fore(i,2,sz(li)) {
      ll next = addVar();
      either(cur, ~li[i]);
      either(cur, next);
      either(~li[i], next);
      cur = ~next;
    }
    either(cur, ~li[1]);
  } */

  vi val, comp, z; ll time = 0;
  ll dfs(ll i) {
    ll low = val[i] = ++time, x; z.push_back(i);
    for(ll e : gr[i]) if (!comp[e])
      low = min(low, val[e] ?: dfs(e));
    if (low == val[i]) do {
      x = z.back(); z.pop_back();
      comp[x] = low;
      if (values[x>>1] == -1)
        values[x>>1] = x&1;
    } while (x != i);
    return val[i] = low;
  }

  bool solve() {
    values.assign(N, -1);
    val.assign(2*N, 0); comp = val;
    fore(i,0,2*N) if (!comp[i]) dfs(i);
    fore(i,0,N) if (comp[2*i] == comp[2*i+1]) return 0;
    return 1;
  }
};

bool posibbleWith(ull n, const vuu& edges, ull k) {
  if (k <= 1) {
    return true;
  }

  if (k == 2) {
    TwoSat ts(n);
    for (auto& [u, v] : edges) {
      ts.either(u, v);
    }
    fore(i, 0, n - 1) {
      ts.either(~i, ~(i + 1));
    }
    return ts.solve();
  } else {
    DBG(k);
    TwoSat ts(2 * n);

    for (auto& [u, v] : edges) {
      ts.either(n + u, n + v);
      //cerr << n + u << " | " << n + v << '\n';
    }

    fore(i, 1, n) {
      ts.either(i, ~(2 * i));
      ts.either(i, ~(2 * i + 1));
      //cerr << "!" << i << " → !" << 2 * i << '\n';
      //cerr << "!" << i << " → !" << 2 * i + 1 << '\n';
    }

    fore(i, 0, n) {
      vuu lrs = {
        {max(n + i - k + 1, n), n + i},
        {n + i + 1, min(n + i + k, 2 * n)}
      };
      for (auto [l, r] : lrs) {
        for (; l < r; l /= 2, r /= 2) {
          if (l % 2) {
            ts.either(~(n + i), ~l);
            //cerr << (n + i) << " → !" << l << '\n';
            l++;
          }
          if (r % 2) {
            --r;
            ts.either(~(n + i), ~r);
            //cerr << (n + i) << " → !" << r << '\n';
          }
        }
      }
    }

    //cerr << "---------------\n";
    return ts.solve();
  }
}

ull solve1(ull n, const vuu& edges) {
  if (n == 1) {
    return 1;
  }

  ull l = 1, r = n + 1;

  while (l + 1 < r) {
    ull m = (l + r) / 2;
    if (posibbleWith(n, edges, m)) {
      l = m;
    } else {
      r = m;
    }
  }

  return l;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, m;
    cin >> n >> m;

    vuu edges(m);
    for (auto& [u, v] : edges) {
      cin >> u >> v;
      u--, v--;
    }

    auto ans = solve1(n, edges);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
