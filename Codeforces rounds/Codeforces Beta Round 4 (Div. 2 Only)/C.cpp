// https://codeforces.com/contest/4/problem/C

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  uint n;
  cin >> n;

  map<string, uint> m;

  while (n--) {
    string name;
    cin >> name;
    m[name]++;

    uint count = m[name];

    if (count == 1) {
      cout << "OK\n";
    } else {
      cout << name << count - 1 << '\n';
    }
  }

}
