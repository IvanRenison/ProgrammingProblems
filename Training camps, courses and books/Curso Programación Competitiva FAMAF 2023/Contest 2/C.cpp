// https://codeforces.com/group/id8eYTCwzg/contest/439354/problem/C

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

ull solve(ull n) {
  ull ans = 0;
  for (ull i : {100, 20, 10, 5, 1}) {
    ans += n / i;
    n = n % i;
  }
  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull n;
  cin >> n;

  cout << solve(n) << "\n";

  return EXIT_SUCCESS;
}
