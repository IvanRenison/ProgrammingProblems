// https://www.spoj.com/problems/DQUERY/

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
typedef vector<uint> vu;

#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; i++)

const uint maxn = 30000;

typedef bitset<maxn + 1> T;
T f(const T& a, const T& b) {
  return a | b;
}

struct RMQ {
  vector<vector<T>> jmp;
  RMQ(const vector<T>& V) : jmp(1, V) {
    for (int pw = 1, k = 1; pw * 2 <= V.size(); pw *= 2, ++k) {
      jmp.emplace_back(V.size() - pw * 2 + 1);
      fore(j,0,jmp[k].size())
        jmp[k][j] = f(jmp[k - 1][j], jmp[k - 1][j + pw]);
    }
  }
  T query(int a, int b) {
    assert(a < b); // or return inf if a == b
    int dep = 31 - __builtin_clz(b - a);
    return f(jmp[dep][a], jmp[dep][b - (1 << dep)]);
  }
};

pair<uint, vu> compress(const vu& xs) {
  uint n = xs.size();

  map<uint, vu> xs_map;
  fore(i, 0, n) {
    xs_map[xs[i]].push_back(i);
  }

  vu compressed_xs(n);

  uint i = 0;
  for (const auto& x_ks: xs_map) {
    const vu& ks = x_ks.second;
    for (uint k : ks) {
      compressed_xs[k] = i;
    }
    i++;
  }

  return {i - 1, compressed_xs};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  uint n;
  cin >> n;
  vu as(n);
  for (uint& a : as) {
    cin >> a;
  }

  vu cs = compress(as).second;

  vector<T> bs(n);
  fore(i, 0, n) {
    bs[i].set(cs[i]);
  }

  RMQ t(bs);

  uint q;
  cin >> q;

  fore(_, 0, q) {
    uint i, j;
    cin >> i >> j;
    i--;

    T bs = t.query(i, j);
    uint ans = bs.count();

    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
