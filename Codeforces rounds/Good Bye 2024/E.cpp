// https://codeforces.com/contest/2053/problem/E

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
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;

/** Author: Pietro Palombini
 * Date: 2024-07-06
 * License: CC0
 * Source: https://codeforces.com/blog/entry/124286
 * Description: define \texttt{Data}, \texttt{finalize},
 * \texttt{acc} (as explained below), adding any
 * necessary fields to \texttt{Reroot}. Then instantiate, add
 * the data, and call \texttt{reroot()}.
 *
 * \texttt{finalize} is applied before returning
 * answer for \texttt{p} if \texttt{g[p][ei]} was its
 * parent; usually identity function. When \texttt{p} is the
 * root, \texttt{ei} is -1.
 *
 * Let accumulated$(p, S) = a$ such that \texttt{finalize(a,
 * ...)} is the answer for p$ if S$ were its only children.
 * \texttt{acc} should, given accumulated$(p, S)$ and the
 * answer for \texttt{g[p][ei]}, compute
 * accumulated$(p,S\cup\{\texttt{g[p][ei]}})$ in
 * \texttt{p\_ans}.
 *
 * \texttt{neuts[p]} should be accumulated$(p, \varnothing)$.
 *
 * \texttt{root\_dp[v]} is the answer for the whole tree with
 * \texttt{v} as root, \texttt{fdp[v][ei]} is the answer for
 * \texttt{g[v][ei]} if \texttt{v} is the root and
 * \texttt{bdp[v][ei]} is the answer for \texttt{v} if
 * \texttt{g[v][ei]} is the root.
 *
 * Equivalent to the following code, but for all roots:
 *
 * \texttt{Data dfs(ll u, ll p) \{}
 *
 * \ \ \texttt{Data res = neuts[u];}
 *
 * \ \ \texttt{fore(ei, 0, SZ(g[u])) if (g[u][ei] != p)}
 *
 * \ \ \ \ \texttt{acc(res, dfs(g[u][ei], u), u, ei);}
 *
 * \ \ \texttt{ll pid = p == -1 ? -1 : find(ALL(g[u]), p) - begin(g[u]);}
 *
 * \ \ \texttt{return dp[u] = finalize(res, u, pid);}
 *
 * \texttt{}}
 * Time: Fast O(n \log n) assuming O(1) operations.
 * Status: stress-tested
 */
struct Data {
  bool soyHoja;
  ull hijosHoja;
  ull nietosHoja;
  ull desSinHijosHoja;
  ull desSinHijosHojaEnHijosDeNietosHoja;
  ull desNoHoja;
};
typedef vector<Data> vd;

struct Reroot {
  ll n; vector<vi>& g; vd& neuts;

  Data finalize(const Data& a, ll p, ll ei) {
    return a;
  }
  void acc(Data& p_ans, const Data& child_ans, ll p, ll ei) {
    if (child_ans.soyHoja) {
      p_ans.hijosHoja++;
    } else {
      if (child_ans.hijosHoja > 0) {
        p_ans.nietosHoja += child_ans.hijosHoja;
        p_ans.desSinHijosHojaEnHijosDeNietosHoja += child_ans.desSinHijosHoja;
      }
      p_ans.desSinHijosHoja += child_ans.desSinHijosHoja;
      if (child_ans.hijosHoja == 0) {
        p_ans.desSinHijosHoja++;
      }
      p_ans.desNoHoja += child_ans.desNoHoja + 1;
    }
  }

  vd root_dp; vector<vd> fdp, bdp;
  Reroot(vector<vi>& g, vd& neuts) : n(SZ(g)), g(g),
      neuts(neuts), root_dp(n), fdp(n), bdp(n) {}
  void reroot() {
    if (n==1) { root_dp[0]=finalize(neuts[0], 0, -1); return; }
    vd dp = neuts, e(n); vi o = {0}, p(n); o.reserve(n);
    fore(i, 0, n) for (ll v : g[o[i]]) if (v != p[o[i]])
      p[v] = o[i], o.push_back(v);
    for (ll u : views::reverse(o)) {
      ll pei = -1;
      fore(ei, 0, SZ(g[u]))
        if (g[u][ei] == p[u]) pei = ei;
        else acc(dp[u], dp[g[u][ei]], u, ei);
      dp[u] = finalize(dp[u], u, pei);
    }
    for (ll u : o) {
      dp[p[u]] = dp[u];
      fdp[u].reserve(SZ(g[u])), bdp[u].reserve(SZ(g[u]));
      for (ll v : g[u]) fdp[u].push_back(dp[v]);
      ex(e, fdp[u], neuts[u], u);
      fore(i, 0, SZ(fdp[u])) bdp[u].push_back(finalize(e[i], u, i));
      acc(e[0], fdp[u][0], u, 0);
      root_dp[u] = finalize(n > 1 ? e[0] : neuts[u], u, -1);
      fore(i, 0, SZ(g[u])) dp[g[u][i]] = bdp[u][i];
    }
  }
  void ex(vd& e, vd& a, Data& ne, ll v) {
    ll d = SZ(a); fill(begin(e), begin(e) + d, ne);
    for (ll b = bit_width((unsigned)d); b--;) {
      for (ll i = d; i--;) e[i] = e[i >> 1];
      fore(i, 0, d - (d & !b)) acc(e[(i >> b)^1], a[i], v, i);
    }
  }
};

ull solve(vuu& edges) {
  ull n = edges.size() + 1;

  vector<vi> g(n);
  for (auto [u, v] : edges) {
    g[u].push_back(v);
    g[v].push_back(u);
  }

  vd neuts(n);
  fore(i, 0, n) {
    neuts[i] = {g[i].size() == 1, 0, 0, 0, 0, 0};
  }

  Reroot rr(g, neuts);
  rr.reroot();

  ull ans = 0;
  fore(i, 0, n) {
    assert(neuts[i].soyHoja == rr.root_dp[i].soyHoja);
    if (neuts[i].soyHoja) {
      ans += rr.root_dp[i].desNoHoja;
    } else {
      ans += rr.root_dp[i].desSinHijosHojaEnHijosDeNietosHoja;
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;
    vuu edges(n - 1);
    for (auto& [u, v] : edges) {
      cin >> u >> v;
      u--, v--;
    }

    auto ans = solve(edges);
    cout << ans << '\n';
  }

}
