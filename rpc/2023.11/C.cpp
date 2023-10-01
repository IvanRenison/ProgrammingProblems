// https://redprogramacioncompetitiva.com/contests/2023/11

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


string solve(ll n, string s) {
  assert(n % 2 == 1);
  vector<vector<char>> v(n, vector<char>(n, '#'));

  /*
  0 = RIGHT
  1 = DOWN
  2 = LEFT
  3 = UP
  */
  ull direction = 3;
  bool directionNextChange = false;

  ll i = n/2, j = n/2;
  for (char c : s) {
    v[i][j] = c;


    if (abs(i - n/2) == abs(j - n/2) && direction != 3) {
      direction++;
    } else if (abs(i - n/2) == abs(j - n/2)) {
      directionNextChange = true;
    } else if (directionNextChange) {
      directionNextChange = false;
      direction = 0;
    }

    if (direction == 0) {
      j++;
    } else if (direction == 1) {
      i++;
    } else if (direction == 2) {
      j--;
    } else if (direction == 3) {
      i--;
    }


/*     fore(i, 0, n) {
      fore(j, 0, n) {
        cerr << v[i][j];
      }
      cerr << '\n';
    }
    cerr << '\n'; */
  }

  string ans;

  fore(i, 0, n) {
    fore(j, 0, n) {
      if (v[i][j] != '#') {
        ans += v[i][j];
      }
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n;
  string s;
  cin >> n >> s;

  auto ans = solve(n, s);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
