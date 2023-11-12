// https://codeforces.com/gym/101243
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(), x.end()
#define SZ(x) ((int)x.size())
#define fore(i, a, b) for (int i = a, thxMat = b; i < thxMat; ++i)
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int main() {
  FIN;

#ifdef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

  ll n, k;
  cin >> n >> k;
  cout << max(2ll, (n * 2 + k - 1) / k) << "\n";
  return 0;
}