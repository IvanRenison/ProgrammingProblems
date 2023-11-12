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

/*
int myHash(string s) {
  ull n = s.size();
  int ans = 0;
  int _31_i = 1;
  for (ull i = n - 1; i < n; i--, _31_i *= 31) {
    ans += _31_i * s[i];
  }
  return ans;
}
*/

string get(ull i) {
  string ans = "edededededededededededed";
  fore(j, 0, 12) {
    if ((i & (1 << j)) != 0) {
      ans[2 * j] = 'f', ans[2 * j + 1] = 'E';
    }
  }

  return ans;
}

int main() {
  FIN;
#ifdef ONLINE_JUDGE
  freopen("hash.in", "r", stdin);
  freopen("hash.out", "w", stdout);
#endif

  ull n;
  cin >> n;
  fore(i, 0, n) {
    string s = get(i);
    cout << s << '\n';
  }

  return 0;
}