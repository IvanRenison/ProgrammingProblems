// https://codeforces.com/gym/100801
#include <bits/stdc++.h>
#define pb push_back
#define fst first
#define snd second
#define fore(i, a, b) for (int i = a, ggmat = b; i < ggmat; ++i)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(), x.end()
#define mset(a, v) memset((a), (v), sizeof(a))
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
typedef unsigned long long ull;
typedef long long ll;

double solve(double h, double w) {
  return max(max(min(h / 3, w), min(w / 3, h)), min(h / 2, w / 2));
}

int main() {
  FIN;
#ifdef ONLINE_JUDGE
  freopen("alex.in", "r", stdin);
  freopen("alex.out", "w", stdout);
#endif

  double h, w;
  cin >> h >> w;

  cout << setprecision(8);
  cout << solve(h, w) << '\n';

  return 0;
}
