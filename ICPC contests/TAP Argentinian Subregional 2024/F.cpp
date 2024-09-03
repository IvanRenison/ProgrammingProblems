// https://codeforces.com/gym/105321/problem/F
#include <bits/stdc++.h>
#define ALL(x) x.begin(), x.end()
#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; ++i)
#define SZ(x) (ll) x.size()
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef long double ld;

ll solve(const vi& Rs) {
  ll ans = 0;
  ll streak = 0;
  for (ll R : Rs) {
    if (R) {
      ans++;
      streak++;
      ans += streak >= 3;
    } else {
      ans--;
      streak = 0;
    }
  }
  return ans;
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);

  ll N;
  cin >> N;
  vi Rs(N);
  for (ll& R : Rs) {
    cin >> R;
  }
  cout << solve(Rs) << '\n';
}
