// https://codeforces.com/gym/104603/problem/L

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

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull A1, P1, A2, P2;
  cin >> A1 >> P1 >> A2 >> P2;

  ull A = A1 + A2, P = P1 + P2;

  char ans = A == P ? 'D' : A > P ? 'A' : 'P';

  cout << ans << '\n';

  return EXIT_SUCCESS;
}
