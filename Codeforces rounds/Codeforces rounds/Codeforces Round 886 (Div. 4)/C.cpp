// https://codeforces.com/contest/1850/problem/C

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

string solve1(vector<string> ss) {
  fore(i, 0, 8) {
    fore(j, 0, 8) {
      if (ss[i][j] != '.') {
        string ans = "";
        fore(k, i, 8) {
          if (ss[k][j] != '.') {
            ans += ss[k][j];
          }
        }
        return ans;
      }
    }
  }
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    vector<string> ss(8);
    fore(j, 0, 8) {
      cin >> ss[j];
    }

    auto ans = solve1(ss);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
