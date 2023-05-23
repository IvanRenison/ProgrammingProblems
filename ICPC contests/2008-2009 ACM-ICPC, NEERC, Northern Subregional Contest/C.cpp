#include <bits/stdc++.h>
#define fore(i, a, b) for (ll i = a; i < b; i++)

typedef long long ll;
using namespace std;

int main(void) {

  // Open file holes.in
  freopen("class.in", "r", stdin);

  ll n, r, c;
  cin >> n >> r >> c;

  ll nm = min({r, c, n / 2 + (n % 2)});
  char grid[r][c];
  fore(i, 0, r) fore(j, 0, c) grid[i][j] = '-';
  fore(i, 0, nm) {
    grid[i][0] = '#';
    --n;
  }
  fore(i, 1, nm) {
    grid[0][i] = '#';
    --n;
  }
  fore(i, 0, r) fore(j, 0, c) {
    if (grid[i][j] == '#')
      continue;
    else if (n > 0) {
      grid[i][j] = '#';
      --n;
    } else
      grid[i][j] = '.';
  }

  // Open file holes.out
  freopen("class.out", "w", stdout);
  cout << nm << "\n";
  fore(i, 0, r) {
    fore(j, 0, c) {
      cout << grid[i][j];
    }
    cout << "\n";
  }
  cout << "\n";

  return 0;
}
