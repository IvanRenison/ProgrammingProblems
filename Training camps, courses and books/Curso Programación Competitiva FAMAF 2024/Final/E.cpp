// https://codeforces.com/group/gmV7IkT2pN/contest/531946/problem/E

#include <bits/stdc++.h>
using namespace std;
typedef unsigned int uint;
typedef vector<uint> vu;
#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; i++)

optional<uint> solve(const vu& as) {
  uint n = as.size();

  uint have = 0;
  for (uint a : as) {
    have += __builtin_ctz(a);
  }

  vu extras;
  fore(i, 1, n + 1) {
    uint k = __builtin_ctz(i);
    if (k > 0) {
      extras.push_back(k);
    }
  }

  sort(extras.begin(), extras.end());

  uint ans = 0;

  while (!extras.empty() && have < n) {
    uint k = extras.back();
    extras.pop_back();
    have += k;
    ans++;
  }

  if (have < n) {
    return {};
  } else {
    return ans;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  uint t;
  cin >> t;

  while (t--) {
    uint n;
    cin >> n;
    vu as(n);
    for (uint& a : as) {
      cin >> a;
    }

    optional<uint> ans = solve(as);
    if (ans) {
      cout << *ans << '\n';
    } else {
      cout << "-1\n";
    }
  }
}
