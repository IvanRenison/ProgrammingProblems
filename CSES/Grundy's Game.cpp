// https://cses.fi/problemset/task/2207

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

/* #define SMALL_N 100000

vector<ll> small_sols(SMALL_N);

void init() {
  small_sols[1] = small_sols[2] = 0;
  small_sols[3] = 1;
  small_sols[4] = 0;

  fore(i, 5, SMALL_N) {
    vector<bool> mexs(i/2 + 1, false);
    fore(j, 1, (i + 1)/2) {
      mexs[small_sols[j] ^ small_sols[i - j]] = true;
    }

    fore(j, 0, i/2 + 1) {
      if (!mexs[j]) {
        small_sols[i] = j;
        break;
      }
    }
  }
}
 */

set<ull> falses = {
  1,
  2,
  4,
  7,
  10,
  20,
  23,
  26,
  50,
  53,
  270,
  273,
  276,
  282,
  285,
  288,
  316,
  334,
  337,
  340,
  346,
  359,
  362,
  365,
  386,
  389,
  392,
  566,
  630,
  633,
  636,
  639,
  673,
  676,
  682,
  685,
  923,
  926,
  929,
  932,
  1222
};

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  //init();

/*   fore(i, 1, SMALL_N) {
    if (small_sols[i] == 0)
    cerr << i << " " << small_sols[i] << endl;
  } */

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;

    if (!falses.count(n)) {
      cout << "first\n";
    } else {
      cout << "second\n";
    }
  }

  return EXIT_SUCCESS;
}
