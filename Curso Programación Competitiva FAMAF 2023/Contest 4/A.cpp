// https://codeforces.com/group/id8eYTCwzg/contest/444404/problem/A

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define fore(i, a, b) for (ll i = a; i < b; i++)

void solve(void) {}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  array<ll, 4> x;

  cin >> x[0] >> x[1] >> x[2] >> x[3];

  /*
    a + b = x0
    b + c = x1
    a + c = x2
    a + b + c = x3

    x0 + c = x3


  */

  sort(x.begin(), x.end());

  ll a = abs(x[3] - x[0]);
  ll b = abs(x[3] - x[1]);
  ll c = abs(x[3] - x[2]);

  cout << a << ' ' << b << ' ' << c << '\n';

  return EXIT_SUCCESS;
}
