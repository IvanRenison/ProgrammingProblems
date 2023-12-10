// https://codeforces.com/group/id8eYTCwzg/contest/439354/problem/F

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

vector<ull> parse1(void) {
  ull n;
  cin >> n;

  vector<ull> hs(n);
  fore(i, 0, n) {
    cin >> hs[i];
  }

  return hs;
}

/* Find the minimum index for witch f is true or or upper if none if true */
ull binary_search(function<bool(ull)> f, ull lower, ull upper) {
  if (f(lower)) {
    return lower;
  }
  if (!f(upper - 1)) {
    return upper;
  }
  while (lower + 1 < upper) {
    ull m = (lower + upper) / 2;
    if (f(m)) {
      upper = m;
    } else {
      lower = m;
    }
  }

  return upper;
}

bool posible_for_x(vector<ull> hs, ull x) {
  ull n = hs.size();
  vector<ull> hs2 = hs;

  for (ull i = n - 1; i >= 2; i--) {
    if (hs2[i] < x) {
      return false;
    }
    ull d = min(hs2[i] - x, hs[i]) / 3;
    hs2[i] -= d * 3;
    hs2[i - 1] += d;
    hs2[i - 2] += d * 2;
  }

  return hs2[0] >= x && hs2[1] >= x;
}

ull solve1(vector<ull> hs) {
  ull n = hs.size();

  ull ans = binary_search(
                [hs](ull x) { return !posible_for_x(hs, x); }, 1, 1000000001
            ) -
            1;

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    cout << solve1(parse1()) << "\n";
  }

  return EXIT_SUCCESS;
}

/*

_ * _ * _ * _ * _ * _

*/
