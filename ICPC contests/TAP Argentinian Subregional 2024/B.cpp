// https://codeforces.com/gym/105321/problem/B
#include <bits/stdc++.h>
#define ALL(x) x.begin(), x.end()
#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; ++i)
#define SZ(x) (ll) x.size()
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

vii solve(ll N) {
  vi primes;
  ll n = N;
  fore(i, 2, n + 1) {
    if (n > 0 && n % i == 0) {
      primes.push_back(i);
      while (n % i == 0) {
        n /= i;
      }
    }
  }

  vii ans;
  for (ll p : primes) {
    ans.push_back({0, N / p});
  }

  return ans;
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);

  ll N;
  cin >> N;
  vii ans = solve(N);
  cout << ans.size() << '\n';
  for (auto [L, R] : ans) {
    cout << L + 1 << ' ' << R << '\n';
  }

}
