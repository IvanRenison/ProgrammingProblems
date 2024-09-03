// https://codeforces.com/gym/105321/problem/N
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

ll solve(vi& Vs) {

  ll M = *max_element(ALL(Vs));
  ll m = *min_element(ALL(Vs));

  ll ans = M * M + m * m + m * m - M * m - M * m - m * m;

  return ans;
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);

  ll N;
  cin >> N;
  vi Vs(N);
  for (ll& V : Vs) {
    cin >> V;
  }

  cout << solve(Vs) << '\n';

}
