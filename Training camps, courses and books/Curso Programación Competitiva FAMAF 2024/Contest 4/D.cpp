// https://codeforces.com/group/gmV7IkT2pN/contest/525522/problem/D

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
typedef vector<uint> vu;
typedef pair<uint, uint> uu;
typedef vector<uu> vuu;

#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; i++)

uint solve(const vector<pair<string, string>>& reposteds) {
  map<string, uint> ids = {{"polycarp", 0}};

  for (const auto& [name0, name1] : reposteds) {
    if (!ids.count(name0)) {
      ids[name0] = ids.size();
    }
    if (!ids.count(name1)) {
      ids[name1] = ids.size();
    }
  }

  uint N = ids.size();
  uint M = reposteds.size();

  vuu edges(M);

  fore(i, 0, M) {
    const auto& [name0, name1] = reposteds[i];
    edges[i] = {ids[name1], ids[name0]};
  }

  vector<vu> adj(N);
  for (const auto& [u, v] : edges) {
    adj[u].push_back(v);
  }

  vu in_deg(N, 0);
  for (const auto& [_, v] : edges) {
    in_deg[v]++;
  }

  assert(in_deg[0] == 0);

  vu dist(N, 1);

  queue<uint> q;
  q.push(0);

  while (!q.empty()) {
    uint u = q.front();
    q.pop();

    uint d = dist[u];

    for (uint v : adj[u]) {
      dist[v] = max(dist[v], d + 1);
      in_deg[v]--;
      if (in_deg[v] == 0) {
        q.push(v);
      }
    }
  }

  uint ans = *max_element(dist.begin(), dist.end());

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  uint n;
  cin >> n;

  vector<pair<string, string>> reposteds(n);
  for (auto& [name0, name1] : reposteds) {
    string _;
    cin >> name0 >> _ >> name1;

    for (char& c : name0) {
      c = tolower(c);
    }
    for (char& c : name1) {
      c = tolower(c);
    }
  }


  uint ans = solve(reposteds);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
