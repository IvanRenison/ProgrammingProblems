// https://codeforces.com/contest/2182/problem/E

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


ull solve(ull k, vu& as, vu& xs, vu& ys, vu& zs) {
  ull n = xs.size();

  fore(i, 0, n) {
    k -= ys[i];
    zs[i] -= ys[i];
    ys[i] = 0;
  }

  sort(ALL(as));

  vuu xzs(n);
  fore(i, 0, n) {
    xzs[i] = {xs[i], zs[i]};
  }
  sort(ALL(xzs));
  ull i_xz = 0;

  ull ans = 0;

  multiset<uu> toGive;
  for (ull a : as) {
    while (i_xz < n && xzs[i_xz].first <= a) {
      toGive.insert({xzs[i_xz].second, xzs[i_xz].first});
      i_xz++;
    }

    if (!toGive.empty()) {
      ans++;
      auto it = toGive.end();
      it--;
      toGive.erase(it);
    }
  }

  while (i_xz < n) {
    toGive.insert({xzs[i_xz].second, xzs[i_xz].first});
    i_xz++;
  }

  for (auto [z, x] : toGive) {
    if (z <= k) {
      k -= z;
      ans++;
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, m, k;
    cin >> n >> m >> k;
    vu as(m), xs(n), ys(n), zs(n);
    for (ull& a : as) {
      cin >> a;
    }
    fore(i, 0, n) {
      cin >> xs[i] >> ys[i] >> zs[i];
    }

    auto ans = solve(k, as, xs, ys, zs);
    cout << ans << '\n';
  }

}
/*
1
2 7 15
5 6 7 3 5 6 6
5 8 10
5 6 8



*/