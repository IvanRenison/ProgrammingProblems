#include <bits/stdc++.h>
#define fore(i, a, b) for (int i = a, gmat = b; i < gmat; i++)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(), x.end()
#define mset(a, v) memset((a), (v), sizeof(a))
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;

int main() {
  FIN;

  ull N, X;
  cin >> N >> X;
  vi As(N);
  for (ll& a : As) {
    cin >> a;
  }

  ull ans = 0;

  fore(i, 0, N) {
    ull this_ans = 1;
    fore(j, i + 1, N) {
      if (As[j] - As[j - 1] > X) {
        break;
      }
      this_ans++;
    }
    ans = max(ans, this_ans);
  }

  cout << ans << '\n';

  return 0;
}
