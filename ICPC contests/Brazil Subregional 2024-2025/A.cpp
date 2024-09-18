// https://codeforces.com/gym/105327/problem/A
#include <bits/stdc++.h>
using namespace std;

#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; i++)
#define ALL(x) begin(x), end(x)
#define SZ(x) (ll)(x).size()

typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef long double ld;



ll solve(ll N, ll K) {
  return (K + 1) / N - 1;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  ll N, K;
  cin >> N >> K;

  auto ans = solve(N, K);
  cout << ans << '\n';

}
