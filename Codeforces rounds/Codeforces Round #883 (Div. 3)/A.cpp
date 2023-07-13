// https://codeforces.com/contest/1846/problem/A

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

vector<pair<ull, ull>> parse1(void) {
  ull n;
  cin >> n;
  vector<pair<ull, ull>> abs(n);
  for (auto& [a, b] : abs) {
    cin >> a >> b;
  }
  return abs;
}

ull solve1(vector<pair<ull, ull>> abs) {
  ull count = 0;
  for (auto [a, b] : abs) {
    if (b < a) {
      count++;
    }
  }
  return count;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    auto x = parse1();
    auto ans = solve1(x);
    cout << ans << "\n";
  }

  return EXIT_SUCCESS;
}
