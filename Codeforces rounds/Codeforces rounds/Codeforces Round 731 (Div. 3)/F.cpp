// https://codeforces.com/contest/1547/problem/F

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

typedef ull T;
struct RMQ {
  vector<vector<T>> jmp;
  RMQ(const vector<T>& V) : jmp(1, V) {
    for (ull pw = 1, k = 1; pw * 2 <= V.size(); pw *= 2, ++k) {
      jmp.emplace_back(V.size() - pw * 2 + 1);
      fore(j,0,jmp[k].size())
        jmp[k][j] = gcd(jmp[k - 1][j], jmp[k - 1][j + pw]);
    }
  }
  T query(ull a, ull b) {
    assert(a < b);
    ull dep = 63 - __builtin_clzll(b - a);
    return gcd(jmp[dep][a], jmp[dep][b - (1 << dep)]);
  }
};

ull solve(const vu& as) {
  ull n = as.size();

  vu as2(2 * n);
  fore(i, 0, n) {
    as2[i] = as[i];
    as2[i + n] = as[i];
  }

  RMQ rmq(as2);

  auto can = [&](ull t) -> bool {
    ull val = rmq.query(0, t);
    fore(i, 1, n) {
      ull this_val = rmq.query(i, i + t);
      if (this_val != val) {
        return false;
      }
    }
    return true;
  };

  ull l = 0, r = n;
  while (l + 1 < r) {
    ull m = (l + r) / 2;
    if (can(m)) {
      r = m;
    } else {
      l = m;
    }
  }

  return l;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;

    vu as(n);

    for (ull& a : as) {
      cin >> a;
    }

    ull ans = solve(as);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
