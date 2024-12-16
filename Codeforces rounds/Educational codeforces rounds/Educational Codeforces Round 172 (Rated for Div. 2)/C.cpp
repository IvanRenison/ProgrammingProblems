// https://codeforces.com/contest/2042/problem/C

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


optional<ull> solve(vb& bobs, ull k) {
  ull n = SZ(bobs);

  vu pos_bob(n + 1), pos_alice(n + 1);
  for (ull i = n; i--;) {
    pos_bob[i] = pos_bob[i + 1] + bobs[i];
    pos_alice[i] = pos_alice[i + 1] + !bobs[i];
  }

  ull alice = 0, bob = 0;
  fore(i, 0, n) {
    if (bobs[i]) {
      bob += i;
    } else {
      alice += i;
    }
  }

  ll delta = bob - alice;

  vector<pair<ll, ull>> diffs(n - 1);
  fore(i, 0, n - 1) {
    diffs[i] = {(ll)pos_alice[i + 1] - (ll)pos_bob[i + 1], i};
  }
  sort(ALL(diffs));
  reverse(ALL(diffs));

  ull ans = n;

  for (auto [diff, i] : diffs) {
    if (diff < 0 && delta + diff < (ll)k) {
      break;
    }
    ans--;
    alice -= pos_alice[i + 1];
    bob -= pos_bob[i + 1];
    delta = bob - alice;
  }

  if (delta < (ll)k) {
    return {};
  } else {
    return ans;
  }

}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, k;
    cin >> n >> k;
    vb bobs(n);
    fore(i, 0, n) {
      char c;
      cin >> c;
      bobs[i] = c == '1';
    }

    auto ans = solve(bobs, k);

    if (ans.has_value()) {
      cout << *ans << '\n';
    } else {
      cout << "-1\n";
    }
  }

}
