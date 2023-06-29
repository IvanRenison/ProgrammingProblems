// https://codeforces.com/group/id8eYTCwzg/contest/447739/problem/C

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

struct P {
  vector<ull> pfs;
  ull n;

  P(vector<ull> ps) : n(ps.size()), pfs(ps.size() + 1) {
    sort(ps.begin(), ps.end());

    fore(i, 0, n) {
      pfs[i+1] = pfs[i] + ps[i];
    }
  }

  ull query(ull x, ull y) {
    return pfs[n - x + y] - pfs[n - x];
  }
};

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n, q;
  cin >> n >> q;
  vector<ull> ps(n);
  fore(i, 0, n) {
    cin >> ps[i];
  }

  P p(ps);

  fore(i, 0, q) {
    ull x, y;
    cin >> x >> y;
    cout << p.query(x, y) << '\n';
  }

  return EXIT_SUCCESS;
}
