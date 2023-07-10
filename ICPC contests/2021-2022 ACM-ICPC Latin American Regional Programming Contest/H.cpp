// https://codeforces.com/gym/103640/problem/H

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define fore(i, a, b) for (ll i = a; i < b; i++)

/**
 * Author: Benjamin Qi, chilli
 * Date: 2020-04-04
 * License: CC0
 * Source: https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Matching/Hungarian.h
 * Description: Given a weighted bipartite graph, matches every node on
 * the left with a node on the right such that no
 * nodes are in two matchings and the sum of the edge weights is minimal. Takes
 * cost[N][M], where cost[i][j] = cost for L[i] to be matched with R[j] and
 * returns (min cost, match), where L[i] is matched with
 * R[match[i]]. Negate costs for max cost. Requires $N \le M$.
 * Time: O(N^2M)
 * Status: Tested on kattis:cordonbleu, stress-tested
 */
pair<ll, vector<ll>> hungarian(const vector<vector<ll>>& a) {
  if (a.empty())
    return {0, {}};
  ll n = a.size() + 1, m = a[0].size() + 1;
  vector<ll> u(n), v(m), p(m), ans(n - 1);
  fore(i, 1, n) {
    p[0] = i;
    ll j0 = 0; // add "dummy" worker 0
    vector<ll> dist(m, INT_MAX), pre(m, -1);
    vector<bool> done(m + 1);
    do { // dijkstra
      done[j0] = true;
      ll i0 = p[j0], j1, delta = INT_MAX;
      fore(j, 1, m) if (!done[j]) {
        auto cur = a[i0 - 1][j - 1] - u[i0] - v[j];
        if (cur < dist[j])
          dist[j] = cur, pre[j] = j0;
        if (dist[j] < delta)
          delta = dist[j], j1 = j;
      }
      fore(j, 0, m) {
        if (done[j])
          u[p[j]] += delta, v[j] -= delta;
        else
          dist[j] -= delta;
      }
      j0 = j1;
    } while (p[j0]);
    while (j0) { // update alternating path
      ll j1 = pre[j0];
      p[j0] = p[j1], j0 = j1;
    }
  }
  fore(j, 1, m) if (p[j]) ans[p[j] - 1] = j - 1;
  return {-v[0], ans}; // min cost
}

ll solve(vector<vector<ll>>& L) {
  ll N = L.size();
  ll evens = (N + 1) / 2;
  vector<vector<ll>> D(evens, vector<ll>(evens));

  fore(j, 0, evens) {
    D[0][j] = L[1][2 * j];
  }

  fore(i, 1, N / 2) {
    fore(j, 0, evens) {
      D[i][j] = L[2 * i - 1][2 * j] + L[2 * i + 1][2 * j];
    }
  }
  if (N % 2 == 1) {
    fore(j, 0, evens) {
      D[evens - 1][j] = L[N - 2][2 * j];
    }
  }

  auto [cost, match] = hungarian(D);

  return cost;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ll N;
  cin >> N;

  vector<vector<ll>> L(N, vector<ll>(N));
  fore(i, 0, N) {
    fore(j, 0, N) {
      cin >> L[i][j];
    }
  }

  cout << solve(L) << '\n';

  return EXIT_SUCCESS;
}
