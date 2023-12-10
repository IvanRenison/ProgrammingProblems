// https://codeforces.com/group/id8eYTCwzg/contest/442745/problem/B

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

bool solve(vector<ull> ps) {
  ull n = ps.size() + 1;

  vector<vector<ull>> suns(n);

  fore(i, 0, n - 1) {
    ull p = ps[i];
    suns[p - 1].push_back(i + 1);
  }

  vector<bool> isLeaf(n, false);

  fore(i, 0, n) {
    if (suns[i].size() == 0) {
      isLeaf[i] = true;
    }
  }

  fore(i, 0, n) {
    if (isLeaf[i]) {
      continue;
    }
    ull amount_of_leafs_suns = 0;
    for (ull j : suns[i]) {
      if (isLeaf[j]) {
        amount_of_leafs_suns++;
      }
    }
    if (amount_of_leafs_suns < 3) {
      return false;
    }
  }
  return true;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull n;
  cin >> n;
  vector<ull> ps(n - 1);
  fore(i, 0, n - 1) {
    cin >> ps[i];
  }

  if (solve(ps)) {
    cout << "Yes\n";
  } else {
    cout << "No\n";
  }

  return EXIT_SUCCESS;
}