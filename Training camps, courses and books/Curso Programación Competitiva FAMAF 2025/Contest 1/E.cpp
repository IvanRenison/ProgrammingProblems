// https://codeforces.com/group/Xaa6lwRoge/contest/604333/problem/E

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



int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull n;
  cin >> n;
  vb as(n);
  fore(i, 0, n) {
    char c;
    cin >> c;
    as[i] = c == '1';
  }

  vu odd_zeros(n + 1), odd_ones(n + 1), even_zeros(n + 1), even_ones(n + 1);
  fore(i, 0, n) {
    odd_zeros[i + 1] = odd_zeros[i];
    odd_ones[i + 1] = odd_ones[i];
    even_zeros[i + 1] = even_zeros[i];
    even_ones[i + 1] = even_ones[i];
    if (i % 2 == 1) {
      odd_zeros[i + 1] += (as[i] == 0);
      odd_ones[i + 1] += (as[i] == 1);
    } else {
      even_zeros[i + 1] += (as[i] == 0);
      even_ones[i + 1] += (as[i] == 1);
    }
  }

  ull q;
  cin >> q;
  while (q--) {
    ull l, r;
    cin >> l >> r;
    l--;

    ll d = r - l;

    ull ans0 = (odd_zeros[r] - odd_zeros[l]) + (even_ones[r] - even_ones[l]);
    ull ans1 = (odd_ones[r] - odd_ones[l]) + (even_zeros[r] - even_zeros[l]);
    ull ans = min(ans0, ans1);
    cout << ans << '\n';
  }

}
