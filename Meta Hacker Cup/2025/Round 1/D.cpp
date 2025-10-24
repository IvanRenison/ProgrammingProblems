// https://www.facebook.com/codingcompetitions/hacker-cup/2025/round-1/problems/D

#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef tuple<ull, ull, ull> uuu;
typedef vector<uuu> vuuu;
typedef tuple<ull, ull, ull, ull> uuuu;
typedef vector<uuuu> vuuuu;
typedef tuple<ull, ull, ull, ull, ull> uuuuu;
typedef vector<uuuuu> vuuuuu;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;
typedef tuple<ll, ll, ll, ll> iiii;
typedef vector<iiii> viiii;
typedef tuple<ll, ll, ll, ll, ll> iiiii;
typedef vector<iiiii> viiiii;
typedef long double ld;
typedef vector<ld> vd;
typedef pair<ld, ld> dd;
typedef vector<dd> vdd;
typedef tuple<ld, ld, ld> ddd;
typedef vector<ddd> vddd;
typedef tuple<ld, ld, ld, ld> dddd;
typedef vector<dddd> vdddd;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;
const ld eps = 1e-7;


bool solve(string& s) {
  ull N = s.size();

  vu count_A_end(N + 1);
  vu count_B_end(N + 1);
  for (ull i = N; i--;) {
    count_A_end[i] = count_A_end[i + 1] + (s[i] == 'A');
    count_B_end[i] = count_B_end[i + 1] + (s[i] == 'B');
  }

  fore(i, 0, N) {
    if (count_A_end[i] > count_B_end[i]) {
      return true;
    }
  }

  return false;
}

bool slow(string& s) {
  ull N = s.size();

  vector<vector<vb>> dp(2, vector<vb>(N + 1, vb(N + 1, false))); // 0 le toca a Alice
  fore(l, 1, N + 1) {
    fore(i, 0, N - l + 1) {
      ull j = i + l;

      { // Alice
        bool this_ans = false;
        fore(k, i + 1, j + 1) {
          if (s[k - 1] == 'A') {
            if (!dp[1][k][j]) {
              this_ans = true;
              break;
            }
          }
        }
        dp[0][i][j] = this_ans;
      }
      { // Bob
        bool this_ans = false;
        fore(k, i, j) {
          if (s[k] == 'B') {
            if (!dp[0][i][k]) {
              this_ans = true;
              break;
            }
          }
        }
        dp[1][i][j] = this_ans;
      }
    }
  }

  bool ans = dp[0][0][N];
  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
#ifndef TEST
  ull t;
  cin >> t;

  fore(testCase, 0, t) {
    ull N;
    cin >> N;
    string s;
    cin >> s;

    bool ans = solve(s);

    cout << "Case #" << testCase + 1 << ": ";
    if (ans) {
      cout << "Alice\n";
    } else {
      cout << "Bob\n";
    }
  }

#else
  fore(N, 1, 21) {
    fore(x, 0, 1 << N) {
      string s;
      fore(i, 0, N) {
        if (x & (1 << i)) {
          s += 'A';
        } else {
          s += 'B';
        }
      }
      //reverse(ALL(s));

      //cout << s << " ";
      bool ans = slow(s);
      bool ans2 = solve(s);
      assert(ans == ans2);
      //if (ans) {
      //  cout << "Alice\n";
      //} else {
      //  cout << "Bob\n";
      //}
    }
  }
#endif
}
