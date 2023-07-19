#https: //codeforces.com/gym/100801
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

int main() {
  FIN;
#ifdef ONLINE_JUDGE
  freopen("easy.in", "r", stdin);
  freopen("easy.out", "w", stdout);
#endif
  string s;
  cin >> s;
  bool ne = false;
  fore(i, 0, SZ(s)) {
    if (s[i] == '-') {
      ne = true;
      cout << s[i];
      continue;
    }
    if (s[i] == '+') {
      ne = false;
      cout << s[i];
      continue;
    }
    if (ne && s[i - 1] == '-') {
      cout << s[i];
      int j = i + 1;
      bool h = false;
      while (j < SZ(s) && s[j] == '0') {
        cout << '+' << s[j];
        ++j;
      }
      if (j < SZ(s) && s[j] != '+' && s[j] != '-') {
        cout << '+' << s[j];
      } else if (j < SZ(s)) {
        cout << s[j];
      }
      ne = false;
      i = j;
      continue;
    }
    cout << s[i];
  }
  cout << "\n";
  return 0;
}