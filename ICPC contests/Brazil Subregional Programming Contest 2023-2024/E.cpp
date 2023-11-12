// https://codeforces.com/gym/104555/problem/E
#include <bits/stdc++.h>
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; ++i)
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

constexpr ull FLIM = 1e6 + 1;

ull sumDigits(ull x) {
  ull ans = 0;
  while (x > 0) {
    ans += x % 10;
    x /= 10;
  }
  return ans;
}

ull solve(ull K, vector<ull> Fs) {
  vector<ull> suns(FLIM);
  fore(i, 1, FLIM) {
    suns[i] = i - sumDigits(i);
  }

  vector<ull> amounts(FLIM);
  for (ull F : Fs) {
    amounts[F] += 1;
  }

  for (ull i = FLIM - 1; i < FLIM; i--) {
    if (K >= amounts[i]) {
      amounts[suns[i]] += amounts[i];
      K -= amounts[i];
      amounts[i] = 0;
    } else {
      return sumDigits(i);
    }
  }

  return 0;
}

int main() {
  FIN;
  ull N, K;
  cin >> N >> K;
  K--;
  vector<ull> Fs(N);
  for (ull& F : Fs) {
    cin >> F;
  }

  cout << solve(K, Fs) << '\n';

  return 0;
}
