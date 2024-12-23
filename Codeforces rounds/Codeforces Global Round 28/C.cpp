// https://codeforces.com/contest/2048/problem/C

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


uuuu solve(vb& s) {
  ull n = s.size();

  ull fist_false = inf;
  fore(i, 0, n) {
    if (!s[i]) {
      fist_false = i;
      break;
    }
  }

  if (fist_false == inf) {
    return {0, n, 0, 1};
  }


  ull l1 = 0, r1 = n;
  vb best(n, false);

  ull o_sz = n - fist_false;

  fore(i, 0, n - o_sz + 1) {
    vb x = s;
    fore(j, 0, o_sz) {
      x[fist_false + j] = x[fist_false + j] ^ s[i + j];
    }
    if (x > best) {
      best = x;
      l1 = i;
      r1 = i + o_sz;
    }
  }

  return {0, n, l1, r1};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    string ss;
    cin >> ss;
    ull n = SZ(ss);
    vb s(n);
    fore(j, 0, n) {
      s[j] = ss[j] == '1';
    }


    auto [l0, r0, l1, r1] = solve(s);
    cout << l0 + 1 << " " << r0 << " " << l1 + 1 << " " << r1 << "\n";
  }

}
