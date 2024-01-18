// https://codeforces.com/gym/104603/problem/B
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(), x.end()
#define SZ(x) ((int)x.size())
#define fore(i, a, b) for (int i = a, gmat = b; i < gmat; ++i)
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define mst(a, v) memset((a), (v), sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int main() {
  FIN;

  ull N;
  cin >> N;
  ull ans = 0;
  vector<string> ss(N);
  for (string& s : ss) {
    cin >> s;

    for (ull i = 0; i < N - 1;) {
      if (s[i] == 'N' && s[i + 1] == 'N') {
        ans += 1;
        i += 2;
      } else {
        i++;
      }
    }
  }

  cout << ans << '\n';

  return 0;
}
