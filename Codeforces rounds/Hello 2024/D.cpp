// https://codeforces.com/contest/1919/problem/D

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

const ull inf = 1ull << 60;

bool solve1(const vu& as) {
  ull n = as.size();

  vu nexts(n, inf), prevs(n, inf);
  nexts[0] = 1;
  fore(i, 1, n - 1) {
    nexts[i] = i + 1;
    prevs[i] = i - 1;
  }
  prevs[n - 1] = n - 2;

  vector<vu> dists(n);
  fore(i, 0, n) {
    dists[as[i]].push_back(i);
  }

  vb vis(n, false);
  for (ull a = n - 1; a > 0; a--) {
    if (dists[a].size() > 0) {
      vu s;
      for (ull i : dists[a]) {
        if (prevs[i] != inf && as[i] - as[prevs[i]] == 1) {
          s.push_back(i);
          vis[i] = true;
        } else if (nexts[i] != inf && as[i] - as[nexts[i]] == 1) {
          s.push_back(i);
          vis[i] = true;
        }
      }

      while (!s.empty()) {
        ull i = s.back();
        s.pop_back();

        if (prevs[i] != inf) {
          nexts[prevs[i]] = nexts[i];
          if (nexts[i] != inf) {
            prevs[nexts[i]] = prevs[i];
            if (as[prevs[i]] == a && !vis[prevs[i]] && a - as[nexts[i]] == 1) {
              s.push_back(prevs[i]);
              vis[prevs[i]] = true;
            }
            if (as[nexts[i]] == a && !vis[nexts[i]] && a - as[prevs[i]] == 1) {
              s.push_back(nexts[i]);
              vis[nexts[i]] = true;
            }
          }
        } else if (nexts[i] != inf) {
          prevs[nexts[i]] = prevs[i];
          if (prevs[i] != inf) {
            nexts[prevs[i]] = nexts[i];
            if (as[nexts[i]] == a && !vis[nexts[i]] && a - as[prevs[i]] == 1) {
              s.push_back(nexts[i]);
              vis[nexts[i]] = true;
            }
            if (as[prevs[i]] == a && !vis[prevs[i]] && a - as[nexts[i]] == 1) {
              s.push_back(prevs[i]);
              vis[prevs[i]] = true;
            }
          }
        }
      }

      for (ull i : dists[a]) {
        if (!vis[i]) {
          return false;
        }
      }
    }
  }

  ull count0 = 0;
  fore(i, 0, n) {
    if (as[i] == 0) {
      count0++;
    } else {
      if (!vis[i]) {
        return false;
      }
    }
  }

  return count0 == 1;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;
    vu as(n);
    fore(i, 0, n) {
      cin >> as[i];
    }

    bool ans = solve1(as);
    if (ans) {
      cout << "Yes\n";
    } else {
      cout << "No\n";
    }
  }

  return EXIT_SUCCESS;
}
