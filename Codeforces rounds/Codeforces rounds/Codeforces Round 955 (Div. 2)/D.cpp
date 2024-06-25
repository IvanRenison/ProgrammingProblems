// https://codeforces.com/contest/1982/problem/D

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


bool solve(ull k, const vector<vu>& ass, const vector<vb>& tys) {
  ull n = ass.size(), m = ass[0].size();

  ull sumTrue = 0, sumFalse = 0;

  fore(i, 0, n) {
    fore(j, 0, m) {
      if (tys[i][j]) {
        sumTrue += ass[i][j];
      } else {
        sumFalse += ass[i][j];
      }
    }
  }

  ull d = sumTrue > sumFalse ? sumTrue - sumFalse : sumFalse - sumTrue;

  if (d == 0) {
    return true;
  }

  vector<vu> sums0(n + 1, vu(m + 1)), sums1(n + 1, vu(m + 1));
  fore(i, 0, n) {
    fore(j, 0, m) {
      sums0[i + 1][j + 1] = (!tys[i][j]) + sums0[i + 1][j] + sums0[i][j + 1] - sums0[i][j];
      sums1[i + 1][j + 1] = tys[i][j] + sums1[i + 1][j] + sums1[i][j + 1] - sums1[i][j];
    }
  }

  vu possible_subDiffs;
  fore(i, k, n + 1) {
    fore(j, k, m + 1) {
      ull zeros = sums0[i][j] - sums0[i - k][j] - sums0[i][j - k] + sums0[i - k][j - k];
      ull ones = sums1[i][j] - sums1[i - k][j] - sums1[i][j - k] + sums1[i - k][j - k];
      ull diff = ones > zeros ? ones - zeros : zeros - ones;
      if (diff != 0) {
        possible_subDiffs.push_back(diff);
      }
    }
  }

  if (possible_subDiffs.empty()) {
    return false;
  }

  ull g = possible_subDiffs[0];
  fore(i, 1, possible_subDiffs.size()) {
    g = gcd(g, possible_subDiffs[i]);
  }

  return d % g == 0;

}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, m, k;
    cin >> n >> m >> k;
    vector<vu> ass(n, vu(m));
    fore(i, 0, n) {
      fore(j, 0, m) {
        cin >> ass[i][j];
      }
    }
    vector<vb> tys(n, vb(m));
    fore(i, 0, n) {
      fore(j, 0, m) {
        char c;
        cin >> c;
        tys[i][j] = c == '1';
      }
    }

    bool ans = solve(k, ass, tys);
    if (ans) {
      cout << "Yes\n";
    } else {
      cout << "No\n";
    }
  }

}
