// https://codeforces.com/gym/102861/problem/B
#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; i++)
#define ALL(x) begin(x), end(x)
#define SZ(x) (ll)(x).size()
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  ll N;
  cin >> N;

  vector<vi> a(10, vi(10));

  bool ans = true;

  fore(i, 0, N) {
    ll D, L, R, C;
    cin >> D >> L >> R >> C;
    C--, R--;
    if (D == 0) {
      fore(i, 0, L) {
        if (C + i >= 10) {
          ans = false;
          break;
        }
        a[R][C + i]++;
      }
    } else {
      fore(i, 0, L) {
        if (R + i >= 10) {
          ans = false;
          break;
        }
        a[R + i][C]++;
      }
    }
  }

  fore(i, 0, 10) {
    fore(j, 0, 10) {
      if (a[i][j] > 1) {
        ans = false;
        break;
      }
    }
  }

  cout << (ans ? "Y" : "N") << '\n';

}
