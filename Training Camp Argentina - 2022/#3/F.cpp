// https://codeforces.com/group/4zVk9dZl6Q/contest/390849/problem/F
#include <bits/stdc++.h>
#define pb push_back
#define fore(i, a, b) for (int i = a, ggdem = b; i < ggdem; ++i)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(), x.end()
#define FIN                                                                    \
  ios::sync_with_stdio(0);                                                     \
  cin.tie(0);                                                                  \
  cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

optional<vector<string>> solve(ull k, string q) {

  set<char> found;

  vector<string> ans;

  for (char c : q) {
    if (found.size() < k && found.find(c) == found.end()) {
      ans.push_back("");
      found.insert(c);
    }

    ans.back() += c;
  }

  if (found.size() < k) {
    return {};
  } else {
    return ans;
  }
}

int main(void) {
  FIN;
  ull k;
  cin >> k;
  string q;
  cin >> q;

  optional<vector<string>> ans = solve(k, q);

  if (ans.has_value()) {
    cout << "YES\n";
    for (string s : ans.value()) {
      cout << s << '\n';
    }
  } else {
    cout << "NO\n";
  }

  return 0;
}