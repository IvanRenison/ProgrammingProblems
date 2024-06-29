// https://codeforces.com/group/gmV7IkT2pN/contest/530194/problem/A

#include <bits/stdc++.h>
using namespace std;
typedef unsigned int uint;

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  uint n;
  cin >> n;

  set<string> names;
  while (n--) {
    string s;
    cin >> s;
    if (names.count(s)) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
      names.insert(s);
    }
  }
}
