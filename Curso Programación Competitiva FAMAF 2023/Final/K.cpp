// https://codeforces.com/group/id8eYTCwzg/contest/447739/problem/K

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

/*

El mcd tiene que dividir a a+k y b+k, por ende también a a+b (para cualquier k)

Hacer cuentas con esas cosas

  mcm = (a+k)*(b+k)/mcd
      = k*(a+b)/mcd

  mcd | (b - a)


  Para el divisor q de (b - a), cual es el mínimo k tal que mcd(a+k, b+k) = q?

    mcd(a+k, b+k) = q
  ⇔
    mcd(a-b, a+k) = q

  En particular: q | (a + k)

  O sea que quiero el k que haga llegar a 'a' a un múltiplo de q

  Esto es: q - (a % q)

*/

vector<ull> divs(ull x) {
  vector<ull> ans;
  for (ull i = 1; i * i <= x; i++) {
    if (x % i == 0) {
      ans.push_back(i);
      if (i * i != x) {
        ans.push_back(x / i);
      }
    }
  }

  sort(ans.begin(), ans.end());

  return ans;
}

ull solve(ull a, ull b) {
  if (a == b) {
    return 0;
  }
  if (a < b) {
    swap(a, b);
  }

  vector<ull> divs_ab = divs(a - b);

  ull best_k = 0;
  ull value = a * b / gcd(a, b);

  for (ull q : divs_ab) {
    ull k = q - a % q;
    ull this_value = (a + k) * (b + k) / gcd(a + k, b + k);
    if (this_value < value) {
      best_k = k;
      value = this_value;
    }
  }

  return best_k;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull a, b;
  cin >> a >> b;

  cout << solve(a, b) << '\n';

  return EXIT_SUCCESS;
}
