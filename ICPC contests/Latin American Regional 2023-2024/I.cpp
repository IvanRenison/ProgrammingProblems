// https://codeforces.com/gym/104736/problem/I
#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef __uint128_t u128;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef long double ld;
typedef vector<ld> vd;
typedef pair<ld, ld> dd;
typedef vector<dd> vdd;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

const ull mod = 1e9 + 7;

ull solve(const string& S, u128 N) {

  vu counts(26);
  for(char c : S) {
    counts[c - 'a']++;
  }

  u128 ans = 0;

  vu counts_this(26);
  fore(i, 0, S.size()) {
    u128 all_after = 0;
    u128 this_after = 0;
    fore(c, S[i] - 'a' + 1, 26) {
      all_after = (all_after  + counts[c]) % mod;
      this_after = (this_after + counts_this[c]) % mod;
    }

    /*
      sum (j = 0 to N - 1) (j * c + c_this)
      c_this * N + c * sum (j = 0 to N - 1) j
      c_this * N + c * (N - 1) * N / 2
    */
    ans = (ans + this_after * N + all_after * (((N - 1) * N / 2) % mod)) % mod;

    counts_this[S[i] - 'a']++;
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  string S;
  ull N;
  cin >> S >> N;

  auto ans = solve(S, N);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
