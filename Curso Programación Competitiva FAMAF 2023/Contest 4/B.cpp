// https://codeforces.com/group/id8eYTCwzg/contest/444404/problem/B

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

vector<ull> parse1(void) {
  ull n;
  cin >> n;

  vector<ull> bs(n);

  fore(i, 0, n) {
    cin >> bs[i];
  }

  return bs;
}

vector<ull> solve1(vector<ull> bs) {
  ull n = bs.size();

  vector<ull> as(n);

  fore(i, 0, n) {
    as[i] = i % 2 == 0 ? bs[i / 2] : bs[n - i / 2 - 1];
  }

  return as;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    auto x = parse1();
    auto ans = solve1(x);
    for (ull a : ans) {
      cout << a << ' ';
    }
    cout << '\n';
  }

  return EXIT_SUCCESS;
}
