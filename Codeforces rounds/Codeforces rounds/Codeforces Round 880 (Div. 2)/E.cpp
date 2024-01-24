// https://codeforces.com/contest/1836/problem/E

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef tuple<ull, ull, ull> uuu;
typedef vector<uuu> vuuu;
typedef tuple<ull, ull, ull, ull> uuuu;
typedef vector<uuuu> vuuuu;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

const ull inf = 1ull << 60;


optional<uuuu> solve1(vu gs) {
  ull n = gs.size();

  map<ull, ull> vals;
  fore(i, 0, n) {
    ull g = gs[i];
    if (vals.count(g)) {
      return {{vals[g], vals[g], i, i}};
    }
    vals[g] = i;
  }

  ull erased = inf;
  fore(i, 0, n) {
    if (gs[i] == 0) {
      gs.erase(gs.begin() + i);
      erased = i;
      break;
    }
  }

  n = gs.size();

  vu prexors(n + 1);
  fore(i, 0, n) {
    prexors[i + 1] = prexors[i] ^ gs[i];
  }

  map<ull, uu> xors;
  fore(i, 1, n + 1) {
    ull x = prexors[i];
    if (x == 0) {
      return {{0, 0, 1, i - (i <= erased)}};
    }
    if (xors.count(x)) {
      return {{xors[x].second + 1, xors[x].second + 1, xors[x].second + 2, i - (i <= erased)}};
    } else {
      xors[x] = {0, i - (i <= erased)};
    }
  }

  static random_device rd;
  static mt19937_64 gen(rd());
  uniform_int_distribution<ull> dis(0, n - 1);

  fore(_, 0, 2e7) {
    ull i0 = dis(gen), i1 = dis(gen);
    if (i0 > i1) {
      swap(i0, i1);
    }
    ull x = prexors[i1 + 1] ^ prexors[i0];

    i0 += i0 >= erased, i1 += i1 >= erased;
    if (xors.count(x)) {
      auto [j0, j1] = xors[x];
      if (j0 != i0 && j0 != i1) {
        if (i0 > j0) {
          swap(i0, j0), swap(i1, j1);
        }
        if (i0 <= j0 && j1 <= i1) {
          xors[x] = {j0, j1};
        } else {
          if (i1 >= j0) {
            swap(i1, j0);
            i1--, j0++;
          }
          return {{i0, i1, j0, j1}};
        }
      }
    } else {
      xors[x] = {i0, i1};
    }
  }

  return {};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull k;
    cin >> k;
    vu gs(2 << k);
    for (ull& g : gs) {
      cin >> g;
    }

    auto ans = solve1(gs);
    if (ans.has_value()) {
      auto [a, b, c, d] = *ans;
      cout << a + 1 << ' ' << b + 1 << ' ' << c + 1 << ' ' << d + 1;
    } else {
      cout << -1;
    }
    cout << '\n';
  }

  return EXIT_SUCCESS;
}
