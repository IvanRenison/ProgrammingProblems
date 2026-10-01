// https://codeforces.com/gym/106682/problem/A
#include <bits/stdc++.h>
using namespace std;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define mset(a, v) memset((a), (v), sizeof(a))
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef unsigned long long ull;
typedef pair<ull, ull> uu;
typedef vector<ull> vu;

int main() {
	cin.tie(0)->sync_with_stdio(0);

  ull H, M, S;
  cin >> H >> M >> S;

  char ans;
  if (H == 2 && M == 30 && S == 0) {
    ans = '=';
  } else if (H < 2 || (H == 2 && M < 30)) {
    ans = '-';
  } else {
    ans = '+';
  }

  cout << ans << '\n';
}

