// https://codeforces.com/contest/1850/problem/E

#include <bits/stdc++.h>

using namespace std;

typedef __uint128_t ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

// Define >> and << for __uint128_t making input to unsigned long long
// and casting to __uint128_t
istream &operator>>(istream &is, __uint128_t &value) {
  unsigned long long x;
  is >> x;
  value = x;
  return is;
}

ostream &operator<<(ostream &os, __uint128_t value) {
  if (value >= 10) {
    os << (value / 10);
  }
  os << (char)(value % 10 + '0');
  return os;
}


/* Find the minimum index for witch f is true or upper if none if true */
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

ull solve1(ull c, vector<ull> s) {
  ull n = s.size();

  auto posible_with = [&](ull k) {
    ull sum = 0;
    fore(i, 0, n) {
      sum += (s[i] + 2 * k) * (s[i] + 2 * k);
    }
    return sum >= c;
  };

  ull k = binary_search(posible_with, 0, c / n + 1);
  return k;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, c;
    cin >> n >> c;
    vector<ull> s(n);
    fore(j, 0, n) {
      cin >> s[j];
    }

    auto ans = solve1(c, s);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
