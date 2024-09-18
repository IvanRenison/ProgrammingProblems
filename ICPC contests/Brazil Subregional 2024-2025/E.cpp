// https://codeforces.com/gym/105327/problem/E
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



ll solve(vector<vi>& Kss) {
  ll N = Kss.size();

  ll ans;
  if (Kss[0][0] > Kss[0].back() && Kss[0][0] > Kss.back()[0]) {
    ans = 2;
  } else if (Kss[0].back() > Kss[0][0] && Kss[0].back() > Kss.back().back()) {
    ans = 3;
  } else if (Kss.back().back() > Kss[0].back() && Kss.back().back() > Kss.back()[0]) {
    ans = 0;
  } else {
    ans = 1;
  }

  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  ll N;
  cin >> N;
  vector<vi> Kss(N, vi(N));
  for (vi& Ks : Kss) {
    for (ll& K : Ks) {
      cin >> K;
    }
  }

  auto ans = solve(Kss);
  cout << ans << '\n';

}
