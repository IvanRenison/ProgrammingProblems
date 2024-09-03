// https://codeforces.com/gym/105321/problem/G
#include <bits/stdc++.h>
#define ALL(x) x.begin(), x.end()
#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; ++i)
#define SZ(x) (ll) x.size()
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef long double ld;

ll solve(const string& S) {
  ll T = 0, P = 0, AU = 0;
  for (char c : S) {
    T += c == 'T';
    P += c == 'P';
    AU += c == 'A' || c == 'U';
  }

  return min({T, P, AU});
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);

  string S;
  cin >> S;
  cout << solve(S) << '\n';
}
