// https://codeforces.com/contest/1882/problem/D


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

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl
#define pb push_back

const ull bits_lim = 20;

/**
 * Author: Pietro Palombini
 * Date: 2024-07-06
 * License: CC0
 * Source: https://codeforces.com/blog/entry/124286
 *
 * Description: \texttt{finalize} is applied before returning
 * answer for \texttt{node} if \texttt{g[node][p\_ei]} was its
 * parent; usually identity function.
 *
 * Let accumulated$(p, S) = a$ such that \texttt{finalize(a,
 * ...)} is the answer for $p$ if $S$ were its only children.
 * \texttt{merge} should, given accumulated$(p, S)$ and the
 * answer for \texttt{g[p][ei]}, compute
 * accumulated$(p,S\cup\{\texttt{g[p][ei]}\})$ in
 * \texttt{p\_ans}.
 *
 * \texttt{neuts[p]} should be accumulated$(p, \varnothing)$.
 *
 * Returns a tuple $(\texttt{rootDP}, \texttt{fdp},
 * \texttt{bdp})$ where \texttt{rootDP[v]} is the answer for
 * the whole tree with \texttt{v} as root, \texttt{fdp[v]} is
 * the answer for \texttt{g[v][ei]} if \texttt{v} is the root,
 * and \texttt{bdp[v]} is the answer for \texttt{v} if
 * \texttt{g[v][ei]} is the root.
 * Time: Fast O(n \log n) assuming O(1) lambdas.
 * Status: stress-tested
 */

vu global_as;
vector<vi> global_g;

struct Data {
	ull tam;
	array<ull, bits_lim> ans; // ans[i] = cost of maxing bit i the same as root
};
typedef vector<Data> vd;
Data finalize(Data& a, ll node, ll p_ei) {
	return a;
};
void acc(Data& p_ans, const Data& child_ans, ll p, ll ei) {
	ull a = global_as[p];
	ull a_child = global_as[global_g[p][ei]];
	fore(i, 0, bits_lim) {
		ull bit = (a >> i) & 1;
		ull bit_child = (a_child >> i) & 1;
		if (bit == bit_child) {
			p_ans.ans[i] += child_ans.ans[i];
		} else {
			p_ans.ans[i] += child_ans.ans[i] + child_ans.tam;
		}
	}
	p_ans.tam += child_ans.tam;
};

/* Equivalent to the following code, but for all roots:
Data dfs(ll u, ll p) {
	Data res = neuts[u];
	fore(ei, 0, SZ(g[u])) if (g[u][ei] != p)
		acc(res, dfs(g[u][ei], u), u, ei);
	ll pid = find(ALL(g[u]), p) - begin(g[u]);
	return finalize(res, u, pid);
}
*/

void exclusive(vd& exc, vd& a, Data& ne, ll v) {
	ll d = SZ(a);
	fill(begin(exc), begin(exc) + d, ne);
	for (ll b = bit_width((unsigned)d) - 1; b >= 0; b--) {
		for (ll i = d-1; i >= 0; i--)exc[i] = exc[i >> 1];
		fore(i,0,d-(d&!b))acc(exc[(i>>b)^1],a[i],v,i);
	}
};

vd reroot(vector<vi>& g, vd& neuts) {
	ll n = SZ(g), pei;
	if (n == 1) return neuts;
	vd root_dp(n), exc(n), dp = neuts;
	vector<vd> fdp(n), bdp(n);
	vi o, p(n);
	o.reserve(n), o.pb(0);
	fore(i, 0, n) for (ll v : g[o[i]]) if (v != p[o[i]])
		p[v] = o[i], o.pb(v);
	for (ll u : views::reverse(o)) {
		fore(ei, 0, SZ(g[u])) if (g[u][ei] == p[u]) pei = ei;
		else acc(dp[u], dp[g[u][ei]], u, ei);
		dp[u] = finalize(dp[u], u, u ? pei : -1);
	}
	for (ll u : o) {
		dp[p[u]] = dp[u];
		fdp[u].reserve(SZ(g[u])), bdp[u].reserve(SZ(g[u]));
		for (ll v : g[u]) fdp[u].pb(dp[v]);
		exclusive(exc, fdp[u], neuts[u], u);
		fore(i,0,SZ(fdp[u])) bdp[u].pb(finalize(exc[i], u, i));
		acc(exc[0], fdp[u][0], u, 0);
		root_dp[u] = finalize(n>1 ? exc[0] : neuts[u], u, -1);
		fore(i, 0, SZ(g[u])) dp[g[u][i]] = bdp[u][i];
	}
	return root_dp;
}



vu solve1(const vu& as, const vuu& edges) {
  ull n = as.size();

	global_as = as;

	vector<vi> adj(n);
	for (auto [u, v] : edges) {
		adj[u].pb(v), adj[v].pb(u);
	}

	global_g = adj;

	vd neuts(n, {1, {0}});

/* 	function<Data(ll, ll)> dfs = [&](ll u, ll p) -> Data {
		Data res = neuts[u];
		fore(ei, 0, SZ(adj[u])) if (adj[u][ei] != p) {
			Data rec = dfs(adj[u][ei], u);
			acc(res, rec, u, ei);
		}
		ll pid = find(ALL(adj[u]), p) - begin(adj[u]);
		return finalize(res, u, pid);
	}; */

	vd ans_ = reroot(adj, neuts);
/* 	fore(i, 0, n) {
		ans_[i] = dfs(i, -1);
	} */

	vu ans(n);
	fore(i, 0, n) {
		fore(j, 0, bits_lim) {
			ans[i] += ans_[i].ans[j] * (1ull << j);
		}
	}

	return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;
    vu as(n);
    fore(j, 0, n) {
      cin >> as[j];
    }
    vuu edges(n - 1);
    for (auto& [u, v] : edges) {
      cin >> u >> v;
      u--;
      v--;
    }

    auto ans = solve1(as, edges);
    for (ull x : ans) {
      cout << x << " ";
    }
    cout << "\n";
  }

  return EXIT_SUCCESS;
}
