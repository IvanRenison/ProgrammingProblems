// https://codeforces.com/gym/105123/problem/D2

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


vuu solve(ull a, ull b, const vu& ps) {
  ull n = SZ(ps);

  vu ps_copy = ps;
  sort(ALL(ps_copy));

  vuu ans(n);

  fore(i, 0, n) {
    ull p = ps[i];


    if (p > a) {
      auto it_a = upper_bound(ALL(ps_copy), p - a);
      auto it_b = p >= b ? upper_bound(ALL(ps_copy), p - b) : ps_copy.begin();

      ans[i].second = it_a - it_b;
    }

    {
      auto it_a = lower_bound(ALL(ps_copy), p + a);
      auto it_b = lower_bound(ALL(ps_copy), p + b);

      ans[i].first = it_b - it_a;
    }


  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull n, a, b;
  cin >> n >> a >> b;

  vu ps(n);
  for (ull& p : ps) {
    cin >> p;
  }


  vuu ans = solve(a, b, ps);
  for (auto [x, y] : ans) {
    cout << x << ' ' << y << '\n';
  }

  return EXIT_SUCCESS;
}
