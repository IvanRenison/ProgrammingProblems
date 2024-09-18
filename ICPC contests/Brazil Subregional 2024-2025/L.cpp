// https://codeforces.com/gym/105327/problem/L
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



vi solve(vi& as) {
  ll N = as.size();
  vi count(32, 0);

  for (ll a : as) {
    fore(i, 0, 32) {
      if (a & (1ull << i)) {
        count[i]++;
      }
    }
  }

  vi ans(N);
  fore(i, 0, 32) {
    fore(j, 0, count[i]) {
      ans[j] |= (1ull << i);
    }
  }

  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  ll N;
  cin >> N;
  vi as(N);
  for (ll& a : as) {
    cin >> a;
  }

  auto ans = solve(as);
  for (ll a : ans) {
    cout << a << ' ';
  }
  cout << '\n';

}
