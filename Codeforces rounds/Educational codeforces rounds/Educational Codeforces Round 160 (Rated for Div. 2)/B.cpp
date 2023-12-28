// https://codeforces.com/contest/1913/problem/B

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
#define all(x) x.begin(), x.end()
#define sz(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;
const ld eps = 1e-7;


ull solve1(string s) {
/*   ull n0 = 0, n1 = 0;
  for (char c : s) {
    if (c == '0') n0++;
    else n1++;
  }

  ull t = 2 * min(n0, n1);

  ull m0 = 0, m1 = 0;

  fore(i, 0, t) {
    if (s[i] == '0') m0++;
    else m1++;
  } */

  ull c0 = 0, c1 = 0;
  fore(i, 0, s.size()) {
    if (s[i] == '0') c0++;
    else c1++;
  }

  ull ans = 0;
  while (c0 + c1 > 0) {
    ull n0 = 0, n1 = 0;
    fore(i, 0, c0 + c1) {
      if (s[i] == '0') n0++;
      else n1++;
    }
    assert(n0 + n1 == c0 + c1);
    if (n0 == c1 && n1 == c0) {
      return ans;
    } else if (n0 < c1) {
      ans += c1 - n0;
      c1 = n0;
    } else {
      ans += c0 - n1;
      c0 = n1;
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    string s;
    cin >> s;

    auto ans = solve1(s);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
