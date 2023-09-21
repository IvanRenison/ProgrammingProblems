// https://codeforces.com/gym/104603/problem/M

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

  ull N, T;
  cin >> N >> T;
  ull sum = 0;
  fore(i, 0, N) {
    char c;
    ull X;
    cin >> c >> X;
    sum += X;
  }

  double ans = (double)sum / T;

  cout << setprecision(9);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
