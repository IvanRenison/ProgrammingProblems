// https://codeforces.com/group/gmV7IkT2pN/contest/530194/problem/E

#include <bits/stdc++.h>
using namespace std;
typedef unsigned int uint;
typedef vector<int> vi;
#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; i++)

const int inf = 1 << 30;

struct T {
  int m, M;
};
T f(T a, T b) {
  return {min(a.m, b.m), max(a.M, b.M)};
}
struct RMQ {
  vector<vector<T>> jmp;
  RMQ(const vector<T>& V) : jmp(1, V) {
    for (uint pw = 1, k = 1; pw * 2 <= V.size(); pw *= 2, ++k) {
      jmp.emplace_back(V.size() - pw * 2 + 1);
      fore(j,0,jmp[k].size())
        jmp[k][j] = f(jmp[k - 1][j], jmp[k - 1][j + pw]);
    }
  }
  T query(uint a, uint b) {
    if (a >= b) return {inf, -inf};
    uint dep = 31 - __builtin_clz(b - a);
    return f(jmp[dep][a], jmp[dep][b - (1 << dep)]);
  }
};

void Case() {
  uint n, m;
  cin >> n >> m;
  vi s(n);
  fore(i, 0, n) {
    char c;
    cin >> c;
    s[i] = c == '+' ? 1 : -1;
  }

  vector<T> as(n + 1);
  fore(i, 0, n) {
    as[i + 1].M = as[i + 1].m = as[i].m + s[i];
  }

  RMQ rmq(as);

  while (m--) {
    uint l, r;
    cin >> l >> r;
    l--;

    auto [m, M] = rmq.query(0, l + 1);
    int al = as[l].m, ar = as[r].m;
    int d = ar - al;
    auto [m1, M1] = rmq.query(r + 1, n + 1);
    m = min(m, m1 - d);
    M = max(M, M1 - d);

    uint ans = M - m + 1;

    cout << ans << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  uint t;
  cin >> t;

  while (t--) {
    Case();
  }
}
