// https://codeforces.com/gym/101889

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

/**
 * Author: chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://cp-algorithms.com/graph/dinic.html
 * Description: Flow algorithm with complexity $O(VE\log U)$ where $U = \max |\text{cap}|$.
 * $O(\min(E^{1/2}, V^{2/3})E)$ if $U = 1$; $O(\sqrt{V}E)$ for bipartite matching.
 * Status: Tested on SPOJ FASTFLOW and SPOJ MATCHING, stress-tested
 */
struct Dinic {
	struct Edge {
		ll to, rev;
		ll c, oc;
		ll flow() { return max(oc - c, 0LL); } // if you need flows
	};
	vi lvl, ptr, q;
	vector<vector<Edge>> adj;
	Dinic(ll n) : lvl(n), ptr(n), q(n), adj(n) {}
	void addEdge(ll a, ll b, ll c, ll rcap = 0) {
		adj[a].push_back({b, (ll)adj[b].size(), c, c});
		adj[b].push_back({a, (ll)adj[a].size() - 1, rcap, rcap});
	}
	ll dfs(ll v, ll t, ll f) {
		if (v == t || !f) return f;
		for (ll& i = ptr[v]; i < adj[v].size(); i++) {
			Edge& e = adj[v][i];
			if (lvl[e.to] == lvl[v] + 1)
				if (ll p = dfs(e.to, t, min(f, e.c))) {
					e.c -= p, adj[e.to][e.rev].c += p;
					return p;
				}
		}
		return 0;
	}
	ll calc(ll s, ll t) {
		ll flow = 0; q[0] = s;
		fore(L,0,31) do { // 'll L=30' maybe faster for random data
			lvl = ptr = vi(q.size());
			ll qi = 0, qe = lvl[s] = 1;
			while (qi < qe && !lvl[t]) {
				ll v = q[qi++];
				for (Edge e : adj[v])
					if (!lvl[e.to] && e.c >> (30 - L))
						q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
			}
			while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
		} while (lvl[t]);
		return flow;
	}
	bool leftOfMinCut(ll a) { return lvl[a] != 0; }
};


bool solve(vector<vector<char>> grid) {
  ull R = grid.size(), C = grid[0].size();

  auto toi = [&](ull i, ull j) {
    return i*C + j;
  };

  auto top = [&](ull i) {
    return uu{i / C, i % C};
  };

  Dinic d(R*C + 2);
  ull count_points = 0;
  fore(i, 0, R) fore(j, 0, C) if ((i + j) % 2 == 0) {
    vu neighbors;
    if (i > 0) {
      neighbors.push_back(toi(i-1, j));
    }
    if (i + 1 < R) {
      neighbors.push_back(toi(i+1, j));
    }
    if (j > 0) {
      neighbors.push_back(toi(i, j-1));
    }
    if (j + 1 < C) {
      neighbors.push_back(toi(i, j+1));
    }

    for (ull k : neighbors) {
      d.addEdge(toi(i, j), k, 2);
    }
  }

  fore(i, 0, R) fore(j, 0, C) {
    if (grid[i][j] == 'o') {
      count_points++;
    }
    if ((i + j) % 2 == 0) {
      d.addEdge(R*C, toi(i, j), grid[i][j] == 'o' ? 1 : 2);
    } else {
      d.addEdge(toi(i, j), R*C + 1, grid[i][j] == 'o' ? 1 : 2);
    }
  }

  if (count_points % 2 != 0) {
    return false;
  }

  ull f = d.calc(R*C, R*C + 1);

  return f == R*C - count_points/2;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull R, C;
  cin >> R >> C;
  vector<vector<char>> grid(R, vector<char>(C));
  for(auto& row : grid) {
    for (char& c : row) {
      cin >> c;
    }
  }

  if (solve(grid)) {
    cout << "Y\n";
  } else {
    cout << "N\n";
  }

  return EXIT_SUCCESS;
}
