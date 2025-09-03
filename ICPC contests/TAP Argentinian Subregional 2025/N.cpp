// https://codeforces.com/gym/106054/problem/N
#include <bits/stdc++.h>
using namespace std;

#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) for (ll i = a, teo = b; i < teo; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (ll)(x).size()
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;

const ll inf = 1ll << 60;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  ll N;
  cin >> N;
  ll min_X = inf, max_X = -inf, min_Y = inf, max_Y = -inf;
  fore(_, 0, N) {
    ll X, Y;
    cin >> X >> Y;
    if (X < min_X) {
      min_X = X;
    }
    if (Y < min_Y) {
      min_Y = Y;
    }
    if (X > max_X) {
      max_X = X;
    }
    if (Y > max_Y) {
      max_Y = Y;
    }
  }

  min_X--, min_Y--, max_X++, max_Y++;



  ll ans = (max_Y - min_Y) * 2 + (max_X - min_X) * 2;
  cout << ans << '\n';

}