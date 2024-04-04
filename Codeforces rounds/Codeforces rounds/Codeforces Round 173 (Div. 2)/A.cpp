// https://codeforces.com/contest/282/problem/A

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  uint n;
  cin >> n;

  int x = 0;

  for (uint i = 0; i < n; i++) {
    char a, b, c;
    cin >> a >> b >> c;

    if (b == '+') {
      x++;
    } else {
      x--;
    }
  }

  cout << x << '\n';
}
