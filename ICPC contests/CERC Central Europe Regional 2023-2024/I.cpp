// https://codeforces.com/gym/104871/problem/I

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

vu QUERY(vb q) {
  cout << "QUERY ";
  for (bool b : q) {
    cout << b;
  }
  cout << endl;

  vu ans(q.size());
  for (ull& a : ans) {
    cin >> a;
  }

  return ans;
}

ull searchFather(const vector<vu>& querys, ull u) {
  assert(querys.back()[u] == 1);

  ull ans = 0;
  fore(i, 0, querys.size() - 1) {
    if (querys[i][u] != 1) {
      ans |= (1 << i);
    }
  }

  return ans;
}

vuu solve(ull N) {

  vector<vu> querys;

  fore(i, 0, 65 - __builtin_clzll(N - 1)) {
    vb bs(N);
    fore(u, 0, N) {
      bs[u] = (u & (1 << i)) == 0;
    }
    querys.push_back(QUERY(bs));
  }

  vu s;
  fore(u, 0, N) {
    if (querys.back()[u] == 1) {
      s.push_back(u);
    }
  }

  vuu edges;

  while (!s.empty()) {
    ull u = s.back();
    s.pop_back();

    if (querys.back()[u] == 0) {
      assert(s.empty());
      break;
    }

    ull p = searchFather(querys, u);

    edges.push_back({u, p});

    fore(i, 0, querys.size()) {
      if ((u & (1 << i)) == 0) {
        querys[i][p]--;
      }
    }

    if (querys.back()[p] == 1) {
      s.push_back(p);
    }
  }

  return edges;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N;
  cin >> N;

  auto edges = solve(N);
  cout << "ANSWER\n";
  for (auto [u, v] : edges) {
    cout << u + 1 << ' ' << v + 1 << '\n';
  }

  return EXIT_SUCCESS;
}
