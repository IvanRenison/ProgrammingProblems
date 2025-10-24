#include <bits/stdc++.h>
using namespace std;

#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) for (ll i = a, mpisp = b; i < mpisp; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (ll)(x).size()
typedef long long ll;
typedef pair<ll, ll> ii;
typedef tuple<ll, ll, ll> iii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef long double ld;


ll solve(ll t) {
  if (t <= 60 * 6) {
    return 0;
  }
  if (t <= 60 * 6 + 30) {
    return t - 60 * 6;
  }
  if (t <= 60 * 9 + 30) {
    return 30;
  }
  if (t <= 60 * 9 + 45) {
    return t - 60 * 9;
  }
  if (t <= 60 * 10 + 45) {
    return 45;
  }
  return t - 60 * 10;
}


int main() {
	cin.tie(0)->sync_with_stdio(0);

  ll t;
  cin >> t;
  auto ans = solve(t);
  cout << ans << '\n';

}
