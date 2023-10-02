// https://codeforces.com/contest/191/problem/C

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef vector<ull> vu;
typedef vector<ll> vi;
typedef pair<ull, ull> uu;
typedef pair<ll, ll> ii;
typedef vector<uu> vuu;
typedef vector<ii> vii;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define sz(x) ((x).size())

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (ll pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			fore(j,0,sz(jmp[k]))
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(ll a, ll b) {
		assert(a < b); // or return inf if a == b
		ll dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

struct LCA {
	ll T = 0;
	vi time, path, ret;
	RMQ<ll> rmq;

	LCA(vector<vi>& C) : time(sz(C)), rmq((dfs(C,0,-1), ret)) {}
	void dfs(vector<vi>& C, ll v, ll par) {
		time[v] = T++;
		for (ll y : C[v]) if (y != par) {
			path.push_back(v), ret.push_back(time[v]);
			dfs(C, y, v);
		}
	}

	ll lca(ll a, ll b) {
		if (a == b) return a;
		tie(a, b) = minmax(time[a], time[b]);
		return path[rmq.query(a, b)];
	}
	//dist(a,b){return depth[a] + depth[b] - 2*depth[lca(a,b)];}
};


vi solve(vuu edges, vuu paths) {
  ull n = sz(edges) + 1;
  vector<vi> adj(n);
  vector<vector<pair<ull, ull>>> adj_e(n);
  fore(i, 0, n - 1) {
    auto [u, v] = edges[i];
    adj[u].push_back(v), adj[v].push_back(u);
    adj_e[u].push_back({v, i}), adj_e[v].push_back({u, i});
  }

  LCA lca(adj);
  vi pre_sums(n);

  for(auto [u, v] : paths) {
    ull l = lca.lca(u, v);
    pre_sums[l] -= 2;
    pre_sums[u]++, pre_sums[v]++;
  }

  vi ans(n - 1);

  function<void(ull, ull)> dfs = [&](ull u, ull i) {
    ll this_ans = 0;
    for(auto [v, j] : adj_e[u]) {
      if (i != j) {
        dfs(v, j);
        this_ans += ans[j];
      }
    }
    if (u != 0) {
      ans[i] = this_ans + pre_sums[u];
    }
  };

  dfs(0, -1);
  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n;
  cin >> n;
  vuu edges(n - 1);
  for(auto& [u, v] : edges) {
    cin >> u >> v;
    u--, v--;
  }
  ull k;
  cin >> k;
  vuu paths(k);
  for(auto& [u, v] : paths) {
    cin >> u >> v;
    u--, v--;
  }

  auto ans = solve(edges, paths);
  for(ull a : ans) {
    cout << a << ' ';
  }
  cout << '\n';

  return EXIT_SUCCESS;
}
