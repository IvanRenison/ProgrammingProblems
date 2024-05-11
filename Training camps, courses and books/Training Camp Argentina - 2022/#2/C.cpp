#include<bits/stdc++.h>
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,gmat=b; i<gmat;++i)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(),x.end()
#define mset(a,v) memset((a), (v), sizeof(a))
#define FIN ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
using namespace std;
typedef unsigned long long ull;
typedef long long ll;


set<pair<ull, ull>> allowed;

vector<pair<ull, ull>> neighbors(pair<ull, ull> p) {
  auto [r, c] = p;

  vector<pair<ull, ull>> ans;
  vector<pair<ll, ll>> dirs = {
    {-1,-1},{-1,0},{-1,1},
    {0,-1},{0,0},{0,1},
    {1,-1},{1,0},{1,1}
  };

  for(auto [dr, dc] : dirs) {
    ull nr = ull(ll(r) + dr);
    ull nc = ull(ll(c) + dc);

    if (allowed.find({nr, nc}) != allowed.end()) {
      ans.push_back({nr, nc});
    }
  }

  return ans;
}

optional<ull> solve(ull x0, ull y0, ull x1, ull y1, vector<tuple<ull, ull, ull>> rabs) {

  for(auto [r, a, b] : rabs) {
    fore(c, a, b+1) {
      allowed.insert({r, c});
    }
  }

  // bfs
  set<pair<ull, ull>> visited = {{x0, y0}};
  vector<pair<ull, ull>> next = {{x0, y0}};
  ull level = 0;

  while (!next.empty()) {
    vector<pair<ull, ull>> thi = next;
    next = {};
    level++;

    for(auto p : thi) {
      for(auto q : neighbors(p)) {
        if (q == make_pair(x1, y1)) {
          return level;
        }
        if (visited.find(q) == visited.end()) {
          visited.insert(q);
          next.push_back(q);
        }
      }
    }
  }

  return {};
}

int main() {

  ull x0, y0, x1, y1, n;
  cin >> x0 >> y0 >> x1 >> y1 >> n;

  vector<tuple<ull, ull, ull>> rabs(n);
  fore(i, 0, n) {
    ull r, a, b;
    cin >> r >> a >> b;
    rabs[i] = {r, a, b};
  }

  auto ans = solve(x0, y0, x1, y1, rabs);
  if (ans.has_value()) {
    cout << *ans << '\n';
  } else {
    cout << "-1\n";
  }

  return 0;
}
