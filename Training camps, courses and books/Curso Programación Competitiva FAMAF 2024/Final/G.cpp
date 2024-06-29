// https://codeforces.com/group/gmV7IkT2pN/contest/531946/problem/G

#include <bits/stdc++.h>
using namespace std;
typedef unsigned int uint;
typedef vector<uint> vu;
typedef pair<uint, uint> uu;
typedef vector<uu> vuu;
typedef tuple<uint, uint, uint> uuu;
#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; i++)

optional<uuu> solve(uint n) {
  vu ans;
  for (uint i = 2; i * i <= n && ans.size() < 2; i++) {
    if (n % i == 0) {
      ans.push_back(i);
      n /= i;
    }
  }

  if (n == 1 || ans.size() < 2) {
    return {};
  }
  uint a = ans[0], b = ans[1], c = n;
  if (c == b || c == a) {
    return {};
  }
  return {{a, b, c}};
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  uint t;
  cin >> t;

  while (t--) {
    uint n;
    cin >> n;

    optional<uuu> ans = solve(n);
    if (ans.has_value()) {
      auto [a, b, c] = ans.value();
      cout << "YES\n" << a << ' ' << b << ' ' << c << '\n';
    } else {
      cout << "NO\n";
    }
  }
}
