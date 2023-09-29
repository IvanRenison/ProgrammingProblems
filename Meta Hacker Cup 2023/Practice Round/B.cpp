// https://www.facebook.com/codingcompetitions/hacker-cup/2023/practice-round/problems/B?source=codeforces

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

bool solve1(ull R, ull C) {
  return R > C;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull R, C, A, B;
    cin >> R >> C >> A >> B;

    if (solve1(R, C)) {
      cout << "Case #" << i + 1 << ": YES\n";
    } else {
      cout << "Case #" << i + 1 << ": NO\n";
    }
  }

  return EXIT_SUCCESS;
}
