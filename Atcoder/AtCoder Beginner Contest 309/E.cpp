// https://atcoder.jp/contests/abc309/tasks/abc309_e

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define fore(i, a, b) for (ll i = a; i < b; i++)

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
vector<ll> topoSort(const vector<vector<ll>>& gr) {
  vector<ll> indeg(gr.size()), ret;
  for (auto& li : gr)
    for (int x : li)
      indeg[x]++;
  queue<int> q; // use priority_queue for lexic. largest ans.
  fore(i, 0, gr.size()) if (indeg[i] == 0) q.push(i);
  while (!q.empty()) {
    int i = q.front(); // top() for priority queue
    ret.push_back(i);
    q.pop();
    for (int x : gr[i])
      if (--indeg[x] == 0)
        q.push(x);
  }
  return ret;
}

ll solve(vector<ll> ps, vector<pair<ll, ll>> xys) {
  ll N = ps.size();

  vector<vector<ll>> suns(N);
  fore(i, 0, N) {
    if (i != ps[i]) {
      suns[ps[i]].push_back(i);
    }
  }

  vector<ll> dp(N, -1);
  for (auto [x, y] : xys) {
    dp[x] = max(dp[x], y);
  }

  vector<ll> order = topoSort(suns);
  for (ll i : order) {
    dp[i] = max(dp[i], dp[ps[i]] - 1);
  }

  ll ans = 0;
  fore(i, 0, N) {
    if (dp[i] >= 0) {
      ans++;
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ll N, M;
  cin >> N >> M;
  vector<ll> ps(N);
  fore(i, 1, N) {
    cin >> ps[i];
    ps[i]--;
  }
  vector<pair<ll, ll>> xys(M);
  fore(i, 0, M) {
    cin >> xys[i].first >> xys[i].second;
    xys[i].first--;
  }

  cout << solve(ps, xys) << '\n';

  return EXIT_SUCCESS;
}
