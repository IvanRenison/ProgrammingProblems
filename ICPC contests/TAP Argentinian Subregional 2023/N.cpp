// https://codeforces.com/gym/104603/problem/N
#include <bits/stdc++.h>
#define fore(i, a, b) for (int i = a, gmat = b; i < gmat; ++i)
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ll solve(vector<ll> Cs) {
  ll N = Cs.size();

  vector<ll> counts(5);
  for (ll C : Cs) {
    counts[C]++;
  }

  ll ans = 0;
  ans += counts[0];

  // 1,4
  ll i = min(counts[1], counts[4]);
  ans += i;
  counts[1] -= i, counts[4] -= i;

  // 2,3
  i = min(counts[2], counts[3]);
  ans += i;
  counts[2] -= i, counts[3] -= i;

  // 1,1,3
  i = min(counts[1] / 2, counts[3]);
  ans += i;
  counts[1] -= i * 2, counts[3] -= i;

  // 1,2,2
  i = min(counts[1], counts[2] / 2);
  ans += i;
  counts[1] -= i, counts[2] -= i * 2;

  // 2,4,4
  i = min(counts[2], counts[4] / 2);
  ans += i;
  counts[2] -= i, counts[4] -= i * 2;

  // 3,3,4
  i = min(counts[3] / 2, counts[4]);
  ans += i;
  counts[3] -= i * 2, counts[4] -= i;

  // 1,1,1,2
  i = min(counts[1] / 3, counts[2]);
  ans += i;
  counts[1] -= i * 3, counts[2] -= i;

  // 1,3,3,3
  i = min(counts[1], counts[3] / 3);
  ans += i;
  counts[1] -= i, counts[3] -= i * 3;

  // 2,2,2,4
  i = min(counts[2] / 3, counts[4]);
  ans += i;
  counts[2] -= i * 3, counts[4] -= i;

  // 3,4,4,4
  i = min(counts[3], counts[4] / 3);
  ans += i;
  counts[3] -= i, counts[4] -= i * 3;

  fore(j, 1, 5) {
    i = counts[j] / 5;
    ans += i;
    counts[j] -= i * 5;
  }

  return ans;
}

int main() {
  FIN;

  ll n;
  cin >> n;
  vector<ll> c(n);
  fore(i, 0, n) {
    cin >> c[i];
    c[i] = c[i] % 5;
  }
  cout << solve(c) << '\n';
  return 0;
}
