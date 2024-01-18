#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(), x.end()
#define SZ(x) ((int)x.size())
#define fore(i, a, b) for (int i = a, gmat = b; i < gmat; ++i)
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define mst(a, v) memset((a), (v), sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int main() {
  FIN;

  ull N;
  cin >> N;
  vector<ull> As(N), Bs(N);
  for (ull& A : As) {
    cin >> A;
  }
  for (ull& B : Bs) {
    cin >> B;
  }
  sort(ALL(As));
  sort(ALL(Bs));

  vector<ull> pints(N);

  ull ans = 1ll << 48;

  fore(i, 0, N) {
    pints[i] = As[i] + Bs[N - 1 - i];
  }

  sort(ALL(pints));

  ans = pints[N - 1] - pints[0];

  cout << ans << '\n';

  return 0;
}
