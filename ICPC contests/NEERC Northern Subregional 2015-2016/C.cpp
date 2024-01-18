# https://codeforces.com/gym/100801
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

ull solve(string s0, string s1) {
  ull n = s0.size(), m = s1.size();

  map<char, ull> count0, count1;
  fore(i, 1, n) {
    count0[s0[i]]++;
  }
  fore(i, 0, m - 1) {
    count1[s1[i]]++;
  }

  ull ans = n * m;
  for (char c = 'a'; c <= 'z'; c++) {
    ans -= count0[c] * count1[c];
  }

  return ans;
}

int main() {
  FIN;
#ifdef ONLINE_JUDGE
  freopen("concatenation.in", "r", stdin);
  freopen("concatenation.out", "w", stdout);
#endif

  string s1, s2;
  cin >> s1 >> s2;

  cout << solve(s1, s2) << '\n';

  return 0;
}