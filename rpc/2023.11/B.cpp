// https://redprogramacioncompetitiva.com/contests/2023/11

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef vector<ull> vu;
typedef vector<ll> vi;
typedef pair<ull, ull> uu;
typedef pair<ll, ll> ii;
typedef tuple<ull, ull, ull> uuu;
typedef vector<uu> vuu;
typedef vector<ii> vii;
typedef vector<uuu> vuuu;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)


vu solve(vuuu v) {
  vu ans;
  ull t = 0;

  fore(i, 0, v.size()) {
    auto [a, b, c] = v[i];
    if (t > a + c) {
      continue;
    }

    ans.push_back(i);
    t = max(a, t) + b;
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n;
  cin >> n;
  vuuu v(n);
  fore(i, 0, n) {
    ull a, b, c;
    cin >> a >> a >> b >> c;
    v[i] = {a, b, c};
  }

  auto ans = solve(v);
  fore(i, 0, ans.size()) {
    cout << ans[i] + 1 << '\n';
  }

  return EXIT_SUCCESS;
}
