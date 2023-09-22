// https://codeforces.com/gym/104603/problem/E

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



/*
  Let x be the amount of terms (x > 0 ∧ l + (x - 1)*D < R)

  S = l*x + D* x*(x-1)/2
  0 = D*x*x/2 + l*x - D*x/2 + S
  0 = D/2 * x² + (l - D)/2 * x + S
  x = ((D-l)/2 ± √((l - D)²/4 - 4 * D/2 * S))/(2 * D/2)
  x = ((D-l)/2 ± √((l - D)²/4 - 2 * D * S))/D
*/
bool valid(ull A, ull S, ull l, ull R, ull D) {
  if (l == S) {
    return true;
  }

  ull lower = 1, upper = (R - l + 1)/D + 1;

  while (lower + 1 < upper) {
    ull m = (lower + upper) / 2;
    if (l*m + D*m*(m-1)/2 >= S) {
      upper = m;
    } else {
      lower = m;
    }
  }

  return l + (upper - 1)*D >= A && l + (upper - 1)*D < R && l*upper + D*upper*(upper-1)/2 == S;
}

ull solve(ull A, ull S, ull L, ull R) {
  if (S < A) {
    return 0;
  }
  if (S == A) {
    return 1;
  }
  ull n = R - L;
  ull ans = 0;
  fore(D, 1, n + 1) {
    ull start = L + (A - L) % D;
    for(ull l = start; l <= A; l += D) {
      if (valid(A, S, l, R, D)) {
        // cerr << "l: " << l << ", D: " << D << endl;
        ans++;
      }
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull A, S, L, R;
  cin >> A >> S >> L >> R;

  auto ans = solve(A, S, L, R + 1);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
