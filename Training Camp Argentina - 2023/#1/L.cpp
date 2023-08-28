// https://codeforces.com/group/hzSLIARNBN/contest/464702/problem/L

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)


ull solve(const vector<pair<ull, vector<ull>>>& tlss) {
  vector<vector<ull>> positives, negatives;

  for (auto& [t, ls] : tlss) {
    if (t == 1) {
      positives.push_back(ls);
    } else {
      negatives.push_back(ls);
    }
  }

  if (positives.empty()) {
    set<ull> unliked;
    for (auto& ls : negatives) {
      for (ull l : ls) {
        unliked.insert(l);
      }
    }

    return 1000000000000000000ull - unliked.size();
  }

  set<ull> liked;
  for (ull l : positives[0]) {
    liked.insert(l);
  }

  fore(i, 1, positives.size()) {
    auto& ls = positives[i];
    set<ull> new_liked;
    for (ull l : ls) {
      if (liked.count(l)) {
        new_liked.insert(l);
      }
    }
    liked = new_liked;
  }

  for (auto& ls : negatives) {
    for (ull l : ls) {
      liked.erase(l);
    }
  }

  return liked.size();
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N;
  cin >> N;
  vector<pair<ull, vector<ull>>> tlss(N);
  for (auto& [t, ls] : tlss) {
    ull s;
    cin >> t >> s;
    ls = vector<ull>(s);
    for (auto& l : ls) {
      cin >> l;
    }
  }

  auto ans = solve(tlss);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
