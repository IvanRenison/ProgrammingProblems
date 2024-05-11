// https://codeforces.com/group/id8eYTCwzg/contest/442745/problem/A

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

ull solve(ull n, ull k) {
  fore(i, 0, k) {
    if (n % 10 != 0) {
      n--;
    } else {
      n = n / 10;
    }
  }

  return n;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull n, k;

  cin >> n >> k;

  cout << solve(n, k) << "\n";

  return EXIT_SUCCESS;
}