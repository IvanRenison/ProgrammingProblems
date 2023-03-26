// https://codeforces.com/contest/1744/problem/A

#include <iostream>

#include <string.h>

using namespace std;

typedef unsigned int uint;

bool solve1(uint n, uint* as, char* ss) {
  char cs[51];

  memset(cs, '\0', 51);

  for (uint i = 0; i < n; i++) {
    uint a = as[i];
    char s = ss[i];
    char c = cs[a];
    if (c == '\0') {
      cs[a] = s;
    } else if (c != s) {
      return false;
    }
  }

  return true;
}

int main(void) {

  uint t;
  cin >> t;

  for (uint i = 0; i < t; i++) {
    uint n;
    cin >> n;

    uint as[n];
    for (uint j = 0; j < n; j++) {
      cin >> as[j];
    }

    char ss[n];
    for (uint j = 0; j < n; j++) {
      cin >> ss[j];
    }

    bool res = solve1(n, as, ss);

    if (res) {
      cout << "Yes\n";
    } else {
      cout << "No\n";
    }
  }

  return EXIT_SUCCESS;
}
