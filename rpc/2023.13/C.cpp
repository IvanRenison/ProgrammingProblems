// https://redprogramacioncompetitiva.com/contests/2023/13
#include <bits/stdc++.h>
#define fore(i, a, b) for (int i = a, thxMat = b; i < thxMat; ++i)
#define FIN ios::sync_with_stdio(0); cin.tie(0); cout.tie(0)
using namespace std;
typedef __uint128_t ull;

istream& operator>>(istream& is, __uint128_t& value) {
  unsigned long long x;
  is >> x;
  value = x;
  return is;
}

ostream& operator<<(ostream& os, __uint128_t value) {
  if (value >= 10) {
    os << (value / 10);
  }
  os << (char)(value % 10 + '0');
  return os;
}

ull solve(ull a, ull b, ull c, ull n) {
  if (a == 0 || b == 0 || c == 0) {
    return n;
  }
  a++, b++, c++;
  ull lcm_ab = a * b / __gcd(a, b);
  ull lcm_ac = a * c / __gcd(a, c);
  ull lcm_bc = b * c / __gcd(b, c);
  ull lcm_todos = a * lcm_bc / (__gcd(a, lcm_bc));
  ull res = n / a + n / b + n / c - n / lcm_ab - n / lcm_ac - n / lcm_bc +
            n / lcm_todos;
  return res;
}

int main() {FIN;
  ull t;
  cin >> t;
  while (t--) {
    ull a, b, c, n;
    cin >> a >> b >> c >> n;
    cout << solve(a, b, c, n) << '\n';
  }
  return 0;
}
