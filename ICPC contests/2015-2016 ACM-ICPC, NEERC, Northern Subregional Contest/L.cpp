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

ull solve(vector<vector<ull>> m) {
  ull r = m.size(), c = m[0].size();
  ull ans = 0;
  fore(i, 0, r) {
    fore(j, 0, c) {
      bool left = true;
      fore(i2, 0, i) {
        if (m[i2][j] >= m[i][j]) {
          left = false;
          break;
        }
      }
      bool up = true;
      fore(j2, 0, j) {
        if (m[i][j2] >= m[i][j]) {
          up = false;
          break;
        }
      }
      bool right = true;
      fore(i2, i + 1, r) {
        if (m[i2][j] >= m[i][j]) {
          right = false;
          break;
        }
      }
      bool down = true;
      fore(j2, j + 1, c) {
        if (m[i][j2] >= m[i][j]) {
          down = false;
          break;
        }
      }
      if (left) {
        ans++;
      }
      if (up) {
        ans++;
      }
      if (right) {
        ans++;
      }
      if (down) {
        ans++;
      }
    }
  }
  return ans;
}

int main() {
  FIN;
#ifdef ONLINE_JUDGE
  freopen("lucky.in", "r", stdin);
  freopen("lucky.out", "w", stdout);
#endif

  ull r, c;
  cin >> r >> c;
  vector<vector<ull>> m(r, vector<ull>(c));
  fore(i, 0, r) {
    fore(j, 0, c) {
      cin >> m[i][j];
    }
  }

  cout << solve(m) << '\n';

  return 0;
}