// https://www.facebook.com/codingcompetitions/hacker-cup/2023/practice-round/problems/A1?source=codeforces

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

bool solve1(ull S, ull D, ull K) {
  ull buns = 2 * (S + D);
  ull patties = S + 2 * D;

  return patties >= K && buns > K;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull S, D, K;
    cin >> S >> D >> K;

    if (solve1(S, D, K)) {
      cout << "Case #" << i + 1 << ": YES\n";
    } else {
      cout << "Case #" << i + 1 << ": NO\n";
    }
  }

  return EXIT_SUCCESS;
}
