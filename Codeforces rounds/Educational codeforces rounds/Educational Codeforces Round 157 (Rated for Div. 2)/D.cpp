// https://codeforces.com/contest/1895/problem/D

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


vu solve(vu& as) {
  ull n = as.size() + 1;

  ull bits = bit_width(n);

  vu as_xors(n);
  fore(i, 0, n - 1) {
    as_xors[i + 1] = as_xors[i] ^ as[i];
  }

  vu as_xors_sorted = as_xors;
  sort(ALL(as_xors_sorted));

  auto max_xor = [&](ull x) -> ull { // max(x ^ as_xors[i])
    ull l = 1, r = n;
    for (ull i = bits; i--;) {
      if (l + 1 == r) {
        return x ^ as_xors_sorted[l];
      }
      assert(l < r);

      if ((as_xors_sorted[l] & (1 << i)) != (as_xors_sorted[r - 1] & (1 << i))) {
        ull m_x = as_xors_sorted[l];
        m_x &= ~(1 << i);
        m_x |= (1 << i) - 1;
        auto it = upper_bound(as_xors_sorted.begin() + l, as_xors_sorted.begin() + r, m_x);
        assert(it != as_xors_sorted.begin() + r);
        if (x & (1 << i)) {
          r = it - as_xors_sorted.begin();
        } else {
          l = it - as_xors_sorted.begin();
        }
      }
    }

    assert(l + 1 == r);

    return x ^ as_xors_sorted[l];
  };

  vu bs(n);
  fore(x, 0, n) {
    if (max_xor(x) < n) {
      bs[0] = x;
      fore(i, 0, n - 1) {
        bs[i + 1] = x ^ as_xors[i + 1];
        if (bs[i + 1] >= n) {
          assert(false);
        }
      }

      return bs;
    }
  }

  return bs;
}

vu gen(ull n) {
  vu bs(n);
  iota(ALL(bs), 1);
  random_shuffle(ALL(bs));
  vu as(n - 1);
  fore(i, 0, n - 1) {
    as[i] = bs[i] ^ bs[i + 1];
  }
  return as;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

/*   fore(_, 0, 50) {
    ull n = 16;
    vu as = gen(n);
    for (ull a : as) {
      cout << a << " ";
    }
    cout << '\n';
  }
  return 0; */

  ull n;
  cin >> n;
  vu as(n - 1);
  fore(i, 0, n - 1) {
    cin >> as[i];
  }

  auto ans = solve(as);
  for (ull a : ans) {
    cout << a << " ";
  }
  cout << '\n';

}
