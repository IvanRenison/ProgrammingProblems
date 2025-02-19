// https://codeforces.com/contest/2069/problem/D

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

ull solveSimp(string& s) {
  ull n = s.size();
  assert(n % 2 == 0);

  vu count(26, 0);
  for (auto c : s) {
    count[c - 'a']++;
  }

  vu curr_count(26, 0);

  fore(i, 0, n / 2) {
    curr_count[s[i] - 'a']++;
    bool valid = true;
    fore(c, 0, 26) {
      if (curr_count[c] > count[c] / 2) {
        valid = false;
        break;
      }
    }
    if (!valid) {
      return n - i;
    }
  }

  fore(i, n / 2, n) {
    if (s[i] != s[n - 1 - i]) {
      return n - i;
    }
  }

  return 0;
}

ull solve(string& s) {
  ull n = s.size();

  ull pal = 0;
  fore(i, 0, n / 2) {
    if (s[i] == s[n - 1 - i]) {
      pal++;
    } else {
      break;
    }
  }

  string t = s.substr(pal, n - 2 * pal);

  ull ans0 = solveSimp(t);
  reverse(ALL(t));
  ull ans1 = solveSimp(t);
  ull ans = min(ans0, ans1);


  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    string s;
    cin >> s;

    auto ans = solve(s);
    cout << ans << '\n';
  }

}
