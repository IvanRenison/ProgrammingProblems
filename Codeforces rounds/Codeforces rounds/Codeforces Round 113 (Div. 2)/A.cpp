// https://codeforces.com/contest/166/problem/A

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;

bool cmp(pair<uint, uint> a, pair<uint, uint> b) {
  auto [pa, ta] = a;
  auto [pb, tb] = b;

  return pa > pb || (pa == pb && ta < tb);
}

uint solve(vector<pair<uint, uint>> pts, uint k) {
  sort(pts.begin(), pts.end(), cmp);

  auto [pk, tk] = pts[k - 1];

  uint ans = 0;

  for (auto [p, t] : pts) {
    if (p == pk && t == tk) {
      ans++;
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  uint n, k;
  cin >> n >> k;

  vector<pair<uint, uint>> pts(n);
  for (auto& [p, t] : pts) {
    cin >> p >> t;
  }

  auto ans = solve(pts, k);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
