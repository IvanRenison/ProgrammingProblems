// https://codeforces.com/gym/101081/problem/C
#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef vector<ll> vi;

pair<ll, vi> solve(ll x0, vi& As) {
  ull n = As.size();
  vi qs(n - 1);
  for(ull k = n - 2; k < n; k--){
    qs[k] = As.back();
    As[k] += qs[k]*x0;
    As[k + 1] -= qs[k];
    As.pop_back();
  }
  ll r = As[0];

  return {r, qs};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull T;
  cin >> T;
  while (T--) {
    ull n, x0;
    cin >> n >> x0;
    vi As(n + 1);
    for (ll& a : As) {
      cin >> a;
    }

    auto [r, q] = solve(x0, As);
    cout << r << '\n';
    for (ull a : q) {
      cout << a << ' ';
    }
    cout << '\n';
  }

  return EXIT_SUCCESS;
}
