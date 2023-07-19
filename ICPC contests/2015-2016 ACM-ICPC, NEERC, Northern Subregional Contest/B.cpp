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

const int MAXN = 1e5 + 7;

char mat[4][MAXN];
char c[2] = {'@', '.'};

void f(int k, int r) {
  fore(i, 0, r) mat[k][i] = c[i % 2];
}

int main() {
  FIN;
#ifdef ONLINE_JUDGE
  freopen("file.in", "r", stdin);
  freopen("file.out", "w", stdout);
#endif

  int b, w;
  cin >> b >> w;
  if (w > b) {
    swap(b, w);
    c[0] = '.';
    c[1] = '@';
  }
  f(0, 2 * (b - 1));
  fore(i, 0, 2 * (b - 1)) mat[1][i] = c[0];
  fore(i, 0, 2 * (b - 1)) mat[2][i] = c[1];
  f(3, 2 * (w - 1));
  fore(i, 2 * (w - 1), 2 * (b - 1)) mat[2][i] = c[0];

  cout << 4 << ' ' << 2 * (b - 1) << '\n';
  fore(i, 0, 4) {
    fore(j, 0, 2 * (b - 1)) cout << mat[i][j];
    cout << '\n';
  }

  return 0;
}