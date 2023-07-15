// https://atcoder.jp/contests/abc310/tasks/abc310_a

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N, P, Q;
  cin >> N >> P >> Q;
  vector<ull> Ds(N);
  fore(i, 0, N) {
    cin >> Ds[i];
  }

  ull minD = Ds[0];
  fore(i, 1, N) {
    if (Ds[i] < minD) {
      minD = Ds[i];
    }
  }

  cout << min(P, minD + Q) << endl;

  return EXIT_SUCCESS;
}
