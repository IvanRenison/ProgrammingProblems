// https://codeforces.com/gym/102346
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) for (int i = a, gmat = b; i < gmat; i++)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(), x.end()
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ull solve(ull N) {
  return 1ull << __builtin_popcountll(N);
}

int main() {
  FIN;
  ull N;
  cin >> N;

  cout << solve(N) << '\n';

  return 0;
}