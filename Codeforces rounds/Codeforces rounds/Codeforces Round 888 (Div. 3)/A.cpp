// https://codeforces.com/contest/1851/problem/A

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

ull solve1(ull n, ull m, ull k, ull H, vector<ull> hs) {
  ull ans = 0;
  for (ull h : hs) {
    ull delta = max(H, h) - min(H, h);
    if (h != H && delta <= (m - 1) * k && delta % k == 0) {
      ans++;
    }
  }
  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, m, k, H;
    cin >> n >> m >> k >> H;
    vector<ull> hs(n);
    fore(j, 0, n) {
      cin >> hs[j];
    }

    auto ans = solve1(n, m, k, H, hs);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
