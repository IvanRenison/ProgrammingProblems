// https://codeforces.com/gym/101047/problem/G
#include <bits/stdc++.h>
#define pb push_back
#define fst first
#define snd second
#define fore(i, a, b) for (int i = a, gmat = b; i < gmat; ++i)
#define SZ(x) ((int)x.size())
#define mset(a, v) memset((a), (v), sizeof(a))
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

bool solve1(ull N, const vector<ull>& fs) {
  for (ull f : fs) {
    while (true) {
      ull g = __gcd(N, f);
      if (g == 1) {
        break;
      }
      N /= g;
    }
  }
  return N == 1;
}

int main() {
  FIN;

  ull T;
  cin >> T;
  while (T--) {
    ull N, K;
    cin >> N >> K;
    vector<ull> fs(K);
    for (ull& f : fs) {
      cin >> f;
    }
    if (solve1(N, fs)) {
      cout << "Y\n";
    } else {
      cout << "N\n";
    }
  }

  return 0;
}