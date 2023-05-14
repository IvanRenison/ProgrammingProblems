//

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)


vector<ull> solve(vector<ull> as, vector<ull> ks) {
  ull n = as.size();
  ull q = ks.size();

  /*
    Ver que solo vale la pena una suma y el resto restan 1, (porque combine sumar y inmieditamente restar)

    Pero uno puede ver a cual le van a sumar en otro orden

    En particular primero sumar k, k-1, k - n(n-1) y después hacer las restas de 1

  */
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull n, q;
  cin >> n >> q;

  vector<ull> as(n);

  fore(i, 0, n) {
    cin >> as[i];
  }

  vector<ull> ks(q);

  fore(i, 0, q) {
    cin >> ks[i];
  }

  vector<ull> ans = solve(as, ks);

  fore(i, 0, q) {
    cout << ans[i] << ' ';
  }

  cout << '\n';

  return EXIT_SUCCESS;
}
