// https://cses.fi/problemset/task/1730

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef vector<ull> vu;
typedef vector<ll> vi;
typedef pair<ull, ull> uu;
typedef pair<ll, ll> ii;
typedef vector<uu> vuu;
typedef vector<ii> vii;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

bool solve1(vu xs) {
  ull x_or = 0;
  for(ull x : xs) {
    x_or ^= x;
  }

  return x_or != 0;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;
    vu xs(n);
    for(ull& x : xs) {
      cin >> x;
    }

    if (solve1(xs)) {
      cout << "first\n";
    } else {
      cout << "second\n";
    }
  }

  return EXIT_SUCCESS;
}
