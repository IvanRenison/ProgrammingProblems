// https://codeforces.com/gym/103640/problem/K

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;

static inline vector<string> parse(void) {
  uint N;
  cin >> N;

  vector<string> ans(N);

  for (uint i = 0; i < N; i++) {
    cin >> ans[i];
  }

  return ans;
}

static inline bool solve(vector<string> as) {
  set<char> initials = {};

  for (string a : as) {
    initials.insert(a[0]);
  }

  for (string a : as) {
    bool a_is_acronym = true;

    for (char c : a) {
      if (initials.find(c) == initials.end()) {
        a_is_acronym = false;
        break;
      }
    }

    if (a_is_acronym) {
      return true;
    }
  }

  return false;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cout << (solve(parse()) ? 'Y' : 'N') << endl;

  return EXIT_SUCCESS;
}
