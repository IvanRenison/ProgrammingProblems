// https://codeforces.com/contest/1851/problem/E

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

/**
 * Author: Unknown
 * Date: 2002-09-13
 * Source: predates tinyKACTL
 * Description: Topological sorting. Given is an oriented graph.
 * Output is an ordering of vertices, such that there are edges only from left to right.
 * If there are cycles, the returned list will have size smaller than $n$ -- nodes reachable
 * from cycles will not be returned.
 * Time: $O(|V|+|E|)$
 * Status: stress-tested
 */
vector<ull> topoSort(const vector<vector<ull>>& gr) {
	vector<ull> indeg(gr.size()), ret;
	for (auto& li : gr) for (ull x : li) indeg[x]++;
	queue<ull> q; // use priority_queue for lexic. largest ans.
	fore(i,0,gr.size()) if (indeg[i] == 0) q.push(i);
	while (!q.empty()) {
		ull i = q.front(); // top() for priority queue
		ret.push_back(i);
		q.pop();
		for (ull x : gr[i])
			if (--indeg[x] == 0) q.push(x);
	}
	return ret;
}

vector<ull> solve1(vector<ull> cs, vector<ull> ps, vector<vector<ull>> ess) {
  ull n = cs.size();

  vector<bool> inf_sup(n, false);
  for(ull p : ps) {
    inf_sup[p] = true;
  }

  vector<ull> ord = topoSort(ess);
  reverse(ord.begin(), ord.end());

  vector<ull> costs(n);
  for(ull i : ord) {
    if(inf_sup[i]) {
      costs[i] = 0;
    } else if (ess[i].empty()) {
      costs[i] = cs[i];
    } else {
      ull make_cost = 0;
      for(ull j : ess[i]) {
        make_cost += costs[j];
      }
      costs[i] = min(make_cost, cs[i]);
    }
  }

  return costs;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull k, n;
    cin >> n >> k;
    vector<ull> cs(n), ps(k);
    fore(i, 0, n) {
      cin >> cs[i];
    }
    fore(i, 0, k) {
      cin >> ps[i];
      ps[i]--;
    }

    vector<vector<ull>> ess(n);
    fore(i, 0, n) {
      ull m;
      cin >> m;
      ess[i].resize(m);
      fore(j, 0, m) {
        cin >> ess[i][j];
        ess[i][j]--;
      }
    }

    auto ans = solve1(cs, ps, ess);
    fore(i, 0, n) {
      cout << ans[i] << " ";
    }
    cout << "\n";
  }

  return EXIT_SUCCESS;
}
