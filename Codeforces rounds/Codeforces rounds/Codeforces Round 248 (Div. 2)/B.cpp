// https://codeforces.com/contest/433/problem/B

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull n;
  cin >> n;
  vu vs(n);
  for (ull& v : vs) {
    cin >> v;
  }

  vu vs_ord = vs;
  sort(ALL(vs_ord));

  vu vs_sums(n + 1), vs_ord_sums(n + 1);
  fore(i, 0, n) {
    vs_sums[i + 1] = vs_sums[i] + vs[i];
    vs_ord_sums[i + 1] = vs_ord_sums[i] + vs_ord[i];
  }

  ull m;
  cin >> m;
  while (m--) {
    ull type, l, r;
    cin >> type >> l >> r;
    l--;

    ull ans;
    if (type == 1) {
      ans = vs_sums[r] - vs_sums[l];
    } else {
      ans = vs_ord_sums[r] - vs_ord_sums[l];
    }

    cout << ans << '\n';
  }
}
