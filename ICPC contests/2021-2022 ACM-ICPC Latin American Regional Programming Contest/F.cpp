// https://codeforces.com/gym/103640/problem/F

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;

static inline pair<uint, vector<pair<uint, uint>>> parse(void) {

  uint n, m;

  cin >> n >> m;

  vector<pair<uint, uint>> uvs(m);

  for (uint i = 0; i < m; i++) {
    cin >> uvs[i].first >> uvs[i].second;
  }

  return {n, uvs};
}

static inline vector<char> solve(uint n, vector<pair<uint, uint>> uvs) {

  // neighbors until N-1
  map<uint, set<uint>> neighbors = {};

  for (pair<uint, uint> uv : uvs) {
    uint u = uv.first;
    uint v = uv.second;
    if (u != n && v != n) {
      neighbors[u].insert(v);
      neighbors[v].insert(u);
    }
  }

  set<uint> reachable_from_N_1 = {n-1};

  vector<uint> in_queue(n);
  in_queue.push_back(n-1);

  while (in_queue.size() > 0) {
    uint e = in_queue[in_queue.size() - 1];
    in_queue.pop_back();

    set<uint> e_neighbors = neighbors[e];
    if (e_neighbors.size() > 0) {

      for (uint e_ : e_neighbors) {

        std::pair<std::set<uint>::iterator, bool> inserted = reachable_from_N_1.insert(e_);

        if (inserted.second) {
          in_queue.push_back(e_);
        }
      }
    }
  }

  vector<char> ans(n);

  for (uint i = 0; i < n; i++) {
    ans[i] = 'A';
  }

  for (uint e : reachable_from_N_1) {
    ans[e - 1] = 'B';
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  pair<uint, vector<pair<uint, uint>>> in = parse();

  vector<char> ans = solve(in.first, in.second);

  for (char c : ans) {
    cout << c;
  }
  cout << endl;

  return EXIT_SUCCESS;
}
