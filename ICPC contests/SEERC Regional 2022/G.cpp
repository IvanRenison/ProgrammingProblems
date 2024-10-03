// https://codeforces.com/gym/104114/problem/G

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
typedef long long ll;
typedef vector<ll> vi;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()

/*
If first radios is R:

r0 = R
r1 = diffs[0] - R
r2 = diffs[1] - diffs[0] + R
r3 = diffs[2] - diffs[1] + diffs[0] - R

*/

optional<vu> Try(ull R, ull p, vu& diffs, vu& vr) {
  ull n = vr.size();

  multiset<ull> rs(ALL(vr));
  vu ans;

  ull R1 = R;

  for (ull i = p; i--; ) {
    ull d = diffs[i];
    if (R1 >= d) {
      return {};
    }

    R1 = d - R1;

    auto it = rs.find(R1);
    if (it == rs.end()) {
      return {};
    }
    ans.push_back(R1);
    rs.erase(it);
  }

  if (!ans.empty()) {
    reverse(ALL(ans));
  }

  R1 = R;

  fore(i, p, n - 1) {
    auto it = rs.find(R1);
    if (it == rs.end()) {
      return {};
    }
    ans.push_back(R1);
    rs.erase(it);

    ull d = diffs[i];
    if (R1 >= d) {
      return {};
    }

    R1 = d - R1;
  }

  auto it = rs.find(R1);
  if (it == rs.end()) {
    return {};
  }
  ans.push_back(R1);
  rs.erase(it);

  assert(rs.empty());

  return ans;
}

vu solve(vu& vx, vu& vr) {
  ull n = vx.size();

  ull min_r = *min_element(ALL(vr));

  vu diffs(n - 1);
  fore(i, 0, n - 1) {
    diffs[i] = vx[i + 1] - vx[i];
  }

  vi accs(n - 1);
  accs[0] = diffs[0];
  fore(i, 1, n - 1) {
    accs[i] = diffs[i] - accs[i - 1];
  }

  ull min_odds_accs_i = 1;
  for (ull i = 3; i < n - 1; i += 2) {
    if (accs[i] < accs[min_odds_accs_i]) {
      min_odds_accs_i = i;
    }
  }
  ull min_even_accs_i = 0;
  for (ull i = 2; i < n - 1; i += 2) {
    if (accs[i] < accs[min_even_accs_i]) {
      min_even_accs_i = i;
    }
  }

  optional<vu> ans = Try(min_r, min_odds_accs_i + 1, diffs, vr);
  if (ans) return *ans;
  ans = Try(min_r, min_even_accs_i + 1, diffs, vr);
  if (ans) return *ans;
  ans = Try(min_r, 0, diffs, vr);
  if (ans) return *ans;

  assert(false);
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull n;
  cin >> n;
  vu vx(n), vr(n);
  for (ull& x : vx) {
    cin >> x;
  }
  for (ull& r : vr) {
    cin >> r;
  }

  vu ans = solve(vx, vr);
  for (ull s : ans) {
    cout << s << ' ';
  }
  cout << '\n';

}
