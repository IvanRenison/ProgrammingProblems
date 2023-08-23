// https://codeforces.com/group/hzSLIARNBN/contest/464702/problem/B

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

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
		int to, rev;
		ll c, oc;
		ll flow() { return max(oc - c, 0LL); } // if you need flows
	};
	vector<int> lvl, ptr, q;
	vector<vector<Edge>> adj;
	Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
	void addEdge(int a, int b, ll c, ll rcap = 0) {
		adj[a].push_back({b, (int)adj[b].size(), c, c});
		adj[b].push_back({a, (int)adj[a].size() - 1, rcap, rcap});
	}
	ll dfs(int v, int t, ll f) {
		if (v == t || !f) return f;
		for (int& i = ptr[v]; i < adj[v].size(); i++) {
			Edge& e = adj[v][i];
			if (lvl[e.to] == lvl[v] + 1)
				if (ll p = dfs(e.to, t, min(f, e.c))) {
					e.c -= p, adj[e.to][e.rev].c += p;
					return p;
				}
		}
		return 0;
	}
	ll calc(int s, int t) {
		ll flow = 0; q[0] = s;
		fore(L,0,31) do { // 'int L=30' maybe faster for random data
			lvl = ptr = vector<int>(q.size());
			int qi = 0, qe = lvl[s] = 1;
			while (qi < qe && !lvl[t]) {
				int v = q[qi++];
				for (Edge e : adj[v])
					if (!lvl[e.to] && e.c >> (30 - L))
						q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
			}
			while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
		} while (lvl[t]);
		return flow;
	}
	bool leftOfMinCut(int a) { return lvl[a] != 0; }
};


bool solveBranches(ull m, const vector<ull>& Hs, const vector<bool>& origin, ull T) {
  ull n = Hs.size();

  Dinic dinic(2*n + 2);

  fore(u, 0, n) {
    dinic.addEdge(2*u, 2*u+1, 1);
  }

  fore(u, 0, n) {
    fore(v, u+1, n) {
      if (Hs[u] - Hs[v] < T) {
        dinic.addEdge(2*u+1, 2*v, 1);
      }
    }
  }

  for(ull u = 0, count = 0; count < m; u++) {
    if (u >= n) {
      return false;
    }
    if (origin[u]) {
      dinic.addEdge(2*n, 2*u, 1);
      count++;
    }
  }

  for(ull u = n-1, count = 0; count < m; u--) {
    if (u >= n) {
      return false;
    }
    if (!origin[u]) {
      dinic.addEdge(2*u+1, 2*n +1, 1);
      count++;
    }
  }

  ll flow = dinic.calc(2*n, 2*n+1);

  return flow >= m;
}

pair<vector<ull>, vector<bool>> join(const vector<ull>& HAs, const vector<ull>& HBs) {
  ull nA = HAs.size(), nB = HBs.size();
  vector<ull> Hs = {HAs[0]};
  vector<bool> origin = {true};

  ull i = 1, j = 0;

  while (j < nB && HBs[j] > Hs[0]) {
    j++;
  }

  while (j < nB && Hs.back() >= HBs.back()) {
    if (i < nA && HAs[i] >= HBs[j]) {
      Hs.push_back(HAs[i]);
      origin.push_back(true);
      i++;
    } else {
      Hs.push_back(HBs[j]);
      origin.push_back(false);
      j++;
    }
  }

  return {Hs, origin};
}

bool solve(ull m, vector<ull>& HAs, vector<ull>& HBs, ull T) {
  sort(HAs.begin(), HAs.end()), reverse(HAs.begin(), HAs.end());
  sort(HBs.begin(), HBs.end()), reverse(HBs.begin(), HBs.end());

  auto [HAB, origin_AB] = join(HAs, HBs);
  auto [HBA, origin_BA] = join(HBs, HAs);

  return solveBranches(m, HAB, origin_AB, T) ||
         solveBranches(m, HBA, origin_BA, T);
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull m, nA, nB, T;
  cin >> m >> nA >> nB >> T;
  vector<ull> HAs(nA), HBs(nB);
  for (ull& hA : HAs) {
    cin >> hA;
  }
  for (ull& hB : HBs) {
    cin >> hB;
  }

  if (solve(m, HAs, HBs, T)) {
    cout << "S\n";
  } else {
    cout << "N\n";
  }

  return EXIT_SUCCESS;
}

/*
2 6 7 4

8
4
5
2
9
11

2
2
8
3
12
3
12




12
11

9
88


5
4
33
2




*/
