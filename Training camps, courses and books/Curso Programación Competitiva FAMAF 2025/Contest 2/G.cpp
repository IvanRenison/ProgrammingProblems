// https://codeforces.com/group/Xaa6lwRoge/contest/609355/problem/G
/*
#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif
 */
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

bool pos(ull k, const vu& as, ull val) {
  ull n = as.size();

  vi sums(n + 1);
  fore(i, 0, n) {
    sums[i + 1] = sums[i] + (as[i] >= val ? 1 : -1);
  }

  ll m = 0;
  fore(i, k - 1, n) {
    m = min(m, sums[i - k + 1]);
    if (sums[i + 1] > m) {
      return true;
    }
  }

  return false;
}


ull solve(ull k, const vu& as) {
  ull n = as.size();

  ull l = 1, r = n + 2;
  while (l + 1 < r) {
    ull m = (l + r) / 2;

    if (pos(k, as, m)) {
      l = m;
    } else {
      r = m;
    }
  }

  return l;
}

ull force(ull k, const vu& as) {
  ull n = as.size();
  ull ans = 0;
  fore(i, 0, n) {
    fore(j, i + k, n + 1) {
      vu arr;
      fore(l, i, j) {
        arr.push_back(as[l]);
      }

      sort(ALL(arr));

      ull m = arr[(arr.size() + 1) / 2 - 1];
      ans = max(ans, m);
    }
  }
  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

#ifndef TEST
  ull n, k;
  cin >> n >> k;
  vu as(n);
  for (ull& a : as) {
    cin >> a;
  }

  auto ans = solve(k, as);
  cout << ans << '\n';

#else
  fore(_, 0, 1000) {
    ull n = rand() % 10 + 1;
    ull k = rand() % n + 1;

    vu as(n);
    for(ull& a : as) {
      a = rand() % n + 1;
    }

    ull ans = solve(k, as);
    ull ansf = force(k, as);

    if (ans != ansf) {
      cout << "ERROR:\n" << n << ' ' << k << '\n';
      for (ull a : as) {
        cout << a << ' ';
      }
      cout << '\n' << ans << '\n' << ansf << '\n';
      return 1;
    }
  }
#endif
}
