// https://www.codechef.com/problems/FREQXOR

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


vuuu plane_ranges(ull L, ull R) {
  vuuu ranges;

  for (ull i = 0; L + (1ull << i) <= R; i++) {
    if (L & (1ull << i)) {
      ranges.push_back({L, L + (1ull << i), i});
      L += 1ull << i;
    }
  }
  for (ull i = 0; R - (1ull << i) >= L; i++) {
    if (R & (1ull << i)) {
      ranges.push_back({R - (1ull << i), R, i});
      R -= 1ull << i;
    }
  }

  assert(L == R);

  return ranges;
}

ull solve(ull X, ull L, ull R, ull M) {

  vuuu pl_ranges = plane_ranges(L, R);

  vuu ranges;
  for (auto [l, r, i] : pl_ranges) {
    //cerr << l << ' ' << r << ' ' << i << endl;
    ull x = X & ~((1ull << i) - 1);
    ranges.push_back({l ^ x, (l ^ x )+ (1ull << i)});
  }

  map<uu, ull> vals;

  for (auto [l, r] : ranges) {
    if (l >= M) {
      ull d = (l / M) * M;
      l -= d;
      r -= d;
    }

    if (r < M) {
      vals[{l, r}] += 1;
    } else {
      vals[{l, M}] += 1;
      l = 0, r -= M;
      if (r < M) {
        vals[{l, r}] += 1;
      } else {
        vals[{0, r % M}] += 1;
        vals[{0, M}] += r / M;
      }
    }
  }

  set<ull> starts;
  for (auto [lr, c] : vals) {
    starts.insert(lr.first);
  }


  ull ans = 0;

  for (ull l : starts) {
    ull this_ans = 0;
    for (auto [lr, c] : vals) {
      if (lr.first <= l && l < lr.second) {
        this_ans += c;
      }
    }
    ans = max(ans, this_ans);
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  fore(tc, 0, t) {
    ull X, L, R, M;
    cin >> X >> L >> R >> M;
    R++;

    auto ans = solve(X, L, R, M);
    cout << ans << '\n';
  }

}
