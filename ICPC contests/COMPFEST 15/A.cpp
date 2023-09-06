// https://codeforces.com/contest/1866/problem/A
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
  ll N;
  cin >> N;

  ll m = 1ll << 30;

  vector<ll> as(N);
  for (ll& a : as) {
    cin >> a;
    a = abs(a);
    m = min(m, a);
  }

  cout << m << "\n";
  return EXIT_SUCCESS;
}