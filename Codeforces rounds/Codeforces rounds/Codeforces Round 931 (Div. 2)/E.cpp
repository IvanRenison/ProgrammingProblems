// https://codeforces.com/contest/1934/problem/E

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef tuple<ull, ull, ull> uuu;
typedef vector<uuu> vuuu;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)


vuuu solve1(ull n) {
  switch (n) {
  case 3:
    return {{0, 1, 2}}; // 6 3 2
  case 4:
    return {{0, 2, 3}}; // 12 2 4 3
  case 5:
    return {{2, 3, 4}}; // 1 2 20 15 12
  case 6:
    return {{0, 2, 4}, {1, 3, 5}};
  case 7:
    return {{0, 5, 6}, {2, 3, 4}};
  case 8:
    return {{0, 4, 6}, {1, 5, 7}}; // 35 12 3 4 7 8 5 6
  case 9:
    return {{1, 5, 7}, {4, 6, 8}}; // 1 24 3 4 63 8 45 6 35
  case 10:
    return {{0, 6, 8}, {5, 7, 9}};
  case 11:
    return {{5, 7, 9}, {6, 8, 10}};
  case 12:
    return {{0, 4, 7}, {2, 9, 11}, {6, 8, 10}};
  }

  vuuu ans;

  ull m = n;

  if (n % 4 == 0) {
    ans.push_back({0, n - 2, n - 1});
    m -= 2;
  } else if (n % 4 == 3) {
    ans.push_back({0, 1, n - 1});
    m--;
  }

  while (m > n/2) {
    m -= 12;

    if (m % 4 == 1) {
      ans.push_back({m, m + 4, m + 8});
      ans.push_back({m + 1, m + 2, m + 3});
      ans.push_back({m + 5, m + 6, m + 7});
      ans.push_back({m + 9, m + 10, m + 11});
    } else if (m % 4 == 2) {
      ans.push_back({m, m + 1, m + 2});
      ans.push_back({m + 3, m + 7, m + 11});
      ans.push_back({m + 4, m + 5, m + 6});
      ans.push_back({m + 8, m + 9, m + 10});
    }
  }

  return ans;
}


int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;

    auto ans = solve1(n);
    ull k = ans.size();
    assert(k <= n/6 + 5);
    cout << k << '\n';
    for (auto [i, j, k] : ans) {
      cout << i + 1 << ' ' << j + 1 << ' ' << k + 1 << '\n';
    }
  }

  return EXIT_SUCCESS;
}
