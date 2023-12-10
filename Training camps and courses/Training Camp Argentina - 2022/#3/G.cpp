// https://codeforces.com/group/4zVk9dZl6Q/contest/390849/problem/G

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

vector<vector<ull>> next(vector<ull> ds) {
  cout << "next";
  for (ull d : ds) {
    cout << ' ' << d;
  }
  cout << endl;

  ull k;
  cin >> k;

  vector<vector<ull>> ans(k);
  fore(i, 0, k) {
    string s;
    cin >> s;
    for (char c : s) {
      ans[i].push_back(c - '0');
    }
  }

  return ans;
}

#define FIRST 0
#define BEHIND 1
#define ALL                                                                    \
  { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }

bool first_and_behind_are_same(vector<vector<ull>> dss) {
  for (vector<ull> ds : dss) {
    if (find(ds.begin(), ds.end(), FIRST) != ds.end() &&
        find(ds.begin(), ds.end(), BEHIND) != ds.end()) {
      return true;
    }
  }

  return false;
}

void solve(void) {

  ull first_nexts = 0;
  ull behind_nexts = 0;

  while (true) {
    next({FIRST, BEHIND});
    vector<vector<ull>> dss = next({FIRST});
    first_nexts += 2;
    behind_nexts += 1;

    if (first_and_behind_are_same(dss)) {
      break;
    }
  }

  /*

  first_nexts = 2*behind_nexts

  behind_nexts = t + k
    k < c

  first_nexts = t + r*c + k
  first_nexts = 2*t + k'

  let x be de distance from the vertex they meet to the end
  k + x = c

  first_nexts = 2*t + 2*k


  t + r*c + k = 2*t + 2*k
  r*c = t + k
  t ≡ k               (mod c)
  t ≡ (c - x)         (mod c)
  t + x ≡ c           (mod c)
  t + x ≡ 0           (mod c)

  No se cuanto es t ni cuanto es x, pero hago avanzar todos hasta que estén en el mismo
    (Y espero que las querys alcancen)
  */

  while (true) {
    vector<vector<ull>> dss = next(ALL);

    if (dss.size() == 1) {
      break;
    }
  }
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  solve();

  cout << "done" << endl;

  return EXIT_SUCCESS;
}
