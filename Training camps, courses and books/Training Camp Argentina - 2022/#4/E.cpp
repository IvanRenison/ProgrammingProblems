#include <bits/stdc++.h>
#define pb push_back
#define fst first
#define snd second
#define fore(i, a, b) for (ull i = a, ggdem = b; i < ggdem; ++i)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(), x.end()
#define mset(a, v) memset((a), (v)sizeof(a))
#define FIN                                                                    \
  ios::sync_with_stdio(0);                                                     \
  cin.tie(0);                                                                  \
  cout.tie(0)
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
typedef vector<ll> vvl;

pair<string, ull> solve1(string s) {
  ull n = s.size();

  /*   fore(k, 1, n) {
    cout << "k = " << k << ": ";
    string s_ = s;

    fore(i, 0, n-k+1) {
      string s_pedaso = "";
      fore(j, i, i+k) {
        s_pedaso.push_back(s_[j]);
      }

      reverse(s_pedaso.begin(), s_pedaso.end());
      fore(j, i, i+k) {
        s_[j] = s_pedaso[j-i];
      }
    }

    cout << s_ << endl;
  }
  return {"", 0};  */

  ull k_best = 1;

  fore(k, 1, n+1) {
    //cout << "k = " << k << ": ";
    fore(i, 0, n) {
      ull s_i;
      if (i < n - k + 1) { //
        s_i = i + k - 1;
      } else if ((n - k) % 2 == 0) {
        s_i = n - i - 1;
      } else {
        s_i = i - (n - k + 1);
      }

      //cout << s[s_i];

      ull best_i;
      if (i < n - k_best + 1) { //
        best_i = i + k_best - 1;
      } else if ((n - k_best) % 2 == 0) {
        best_i = n - i - 1;
      } else {
        best_i = i - (n - k_best + 1);
      }

      if (s[best_i] < s[s_i]) {
        break;
      } else if (s[best_i] > s[s_i]) {
        k_best = k;
        break;
      }
    }
    //cout << endl;
  }

  string ans = "";
  fore(i, 0, n) {
    ull best_i;
      if (i < n - k_best + 1) { //
        best_i = i + k_best - 1;
      } else if ((n - k_best) % 2 == 0) {
        best_i = n - i - 1;
      } else {
        best_i = i - (n - k_best + 1);
      }
    ans.push_back(s[best_i]);
  }

  return {ans, k_best};
}

int main() {
  FIN;

  ull t;
  cin >> t;
  fore(i, 0, t) {
    ull n;
    cin >> n;
    string s;
    cin >> s;
    auto [ans, k] = solve1(s);
    cout << ans << '\n' << k << '\n';
  }
}

/*

1
10
abcdefghij
k = 1: abcdefghij
k = 2: bcdefghija
k = 3: cdefghijab
k = 4: defghijcba
k = 5: efghijabcd
k = 6: fghijedcba
k = 7: ghijabcdef
k = 8: hijgfedcba
k = 9: ijabcdefgh


*/
