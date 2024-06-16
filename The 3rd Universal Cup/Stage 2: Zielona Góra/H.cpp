// https://qoj.ac/contest/1699/problem/8524
#include <bits/stdc++.h>
using namespace std;

#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; i++)
#define ALL(x) begin(x), end(x)
#define SZ(x) (ll)(x).size()
#define mset(a, v) memset((a), (v), sizeof(a))
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef long double ld;
typedef vector<ld> vd;

const ld eps = 1e-9;

typedef ld I;
ll lis(const vector<I>& S) {
  if (S.empty()) return {};
  ll n = S.size();
  vi prev(n);
  typedef pair<I, ll> p;
  vector<p> res;
  fore(i, 0, n) {
    auto it = lower_bound(ALL(res), p{S[i] - eps, i});
    if (it == res.end()) res.emplace_back(), it = res.end() - 1;
    *it = {S[i], i};
    prev[i] = it == res.begin() ? 0 : (it-1)->second;
  }
  ll L = SZ(res);
  return L;
}

ld solve(const vi& as, ll k) {
  ll n = as.size();

  auto can = [&](ld u) -> bool {
    vd as2(n);
    fore(i, 0, n) {
      as2[i] = (ld)as[i] - u;
    }

    vd as2_sums(n + 1, 0);
    fore(i, 0, n) {
      as2_sums[i + 1] = as2_sums[i] + as2[i];
    }

    vd as_final;
    for (ld a : as2_sums) {
      if (a >= -eps && a <= as2_sums.back() + eps) {
        as_final.pb(a);
      }
    }

    ll L = lis(as_final) - 1;
    return L >= k;
  };

  ld lo = 0, hi = 1000;
  fore(_, 0, 30) {
    ld mid = (lo + hi) / 2;
    if (can(mid)) {
      lo = mid;
    } else {
      hi = mid;
    }
  }

  return lo;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  ll n, k;
  cin >> n >> k;
  vi as(n);
  for (ll& a : as) {
    cin >> a;
  }

  ld ans = solve(as, k);
  cout << setprecision(6) << fixed;
  cout << ans << '\n';
}
