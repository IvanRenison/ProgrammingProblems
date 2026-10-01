// https://codeforces.com/gym/106682/problem/D
#include <bits/stdc++.h>
#include <cassert>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()

struct BigInt {
  vu d;
  ull d_sum;

  BigInt(vu& d) : d(d), d_sum(accumulate(ALL(d), 0ull)) {}

  void addOne() {
    for (ull i = 0; i < d.size(); i++) {
      d[i]++, d_sum++;
      if (d[i] == 10) {
        d[i] = 0, d_sum -= 10;
      } else {
        break;
      }
    }
  }
};

ull solve(vu& s) {
  reverse(s.begin(), s.end());

  // s *= 9
  ull carry = 0;
  fore(i, 0, s.size()) {
    (s[i] *= 9) += carry, carry = s[i] / 10, s[i] %= 10;
  }
  if (carry) {
    s.push_back(carry);
  }

  BigInt n(s);

  ull ans = 0;
  while (ans < n.d_sum) {
    ans++;
    n.addOne();
  }

  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s_;
  cin >> s_;
  vu s(s_.size());
  fore(i, 0, s.size()) {
    s[i] = s_[i] - '0';
  }

  ull ans = solve(s);
  cout << ans << '\n';
}
