// https://www.facebook.com/codingcompetitions/hacker-cup/2023/practice-round/problems/A2?source=codeforces

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

ull solve1(ull A, ull B, ull C) {
  if (C < min(A,B)) {
    return 0;
  }
  if (B <= A) {
    return 2 * (C / B) - 1;
  }
  if (2*A <= B) {
    return C / A;
  }
  if (C < B) {
    return 1;
  }
  return 2 * ((C - A) / B) + (A + (C - A) % B) / A;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull A, B, C;
    cin >> A >> B >> C;

    auto ans = solve1(A, B, C);
    cout  << "Case #" << i + 1 << ": " << ans << '\n';
  }

  return EXIT_SUCCESS;
}
