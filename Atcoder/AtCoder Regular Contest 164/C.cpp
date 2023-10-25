// https://atcoder.jp/contests/arc164/tasks/arc164_c

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

template <typename T0, typename T1>
istream& operator>>(istream& in, pair<T0, T1>& p) {
  in >> p.first >> p.second;
  return in;
}
template <typename T0, typename T1>
ostream& operator<<(ostream& out, pair<T0, T1>& p) {
  out << p.first << ' ' << p.second;
  return out;
}

template <typename T> istream& operator>>(istream& in, vector<T>& v) {
  for (auto& i : v)
    in >> i;
  return in;
}
template <typename T> ostream& operator<<(ostream& out, vector<T>& v) {
  for (auto& i : v)
    out << i << ' ';
  return out;
}

ull solve(vector<pair<ull, ull>> ABs) {
  ull equals_points = 0;

  vector<pair<ull, ull>> A_greater, B_greater;

  for (auto [A, B] : ABs) {
    if (A == B) {
      equals_points += A;
    } else if (A > B) {
      A_greater.push_back({A, B});
    } else {
      B_greater.push_back({A, B});
    }
  }

  // Sort A_greater by difference
  sort(A_greater.begin(), A_greater.end(), [](auto& a, auto& b) {
    return a.first - a.second > b.first - b.second;
  });

  ull A_greater_points = 0;
  fore(i, 0, A_greater.size()) {
    auto [A, B] = A_greater[i];
    if (i % 2 == 0) {
      B_greater.push_back({B, A});
    } else {
      A_greater_points += A;
    }
  }

  ull B_greater_points = 0;
  for (auto [A, B] : B_greater) {
    B_greater_points += B;
  }
  if (!(A_greater.size() % 2 == 0 || equals_points > 0) && B_greater.size() > 0) {
    ull min_diff = B_greater[0].second - B_greater[0].first;
    ull min_diff_i = 0;

    fore(i, 1, B_greater.size()) {
      auto [A, B] = B_greater[i];
      if (B - A < min_diff) {
        min_diff = B - A;
        min_diff_i = i;
      }
    }

    B_greater_points -= B_greater[min_diff_i].second - B_greater[min_diff_i].first;
  }

  return equals_points + A_greater_points + B_greater_points;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N;
  cin >> N;
  vector<pair<ull, ull>> ABs(N);
  cin >> ABs;

  cout << solve(ABs) << '\n';

  return EXIT_SUCCESS;
}
