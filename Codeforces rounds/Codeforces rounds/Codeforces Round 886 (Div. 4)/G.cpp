// https://codeforces.com/contest/1850/problem/G

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

ull solve1(vector<pair<ll, ll>> xys) {
  map<ll, ull> vertical, horizontal, diagonalUp, diagonalDown;

  for(auto [x, y] : xys) {
    vertical[x]++, horizontal[y]++;
    diagonalUp[x - y]++, diagonalDown[x + y]++;
  }

  ull ans = 0;
  for(auto [_, v] : vertical) {
    ans += v * (v - 1);
  }
  for(auto [_, v] : horizontal) {
    ans += v * (v - 1);
  }
  for(auto [_, v] : diagonalUp) {
    ans += v * (v - 1);
  }
  for(auto [_, v] : diagonalDown) {
    ans += v * (v - 1);
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;
    vector<pair<ll, ll>> xys(n);
    fore(i, 0, n) {
      cin >> xys[i].first >> xys[i].second;
    }

    auto ans = solve1(xys);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
