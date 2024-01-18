// https://codeforces.com/gym/100623

/*
Encontrar el número mas chico que no se puede escribir como suma

Subproblema mas simple: https://cses.fi/problemset/task/2183

Resolver m veces ese problema es la solución
*/

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

vector<ull> solve(ull m, vector<ull> as) {
  sort(as.begin(), as.end());

  ull not_sumed = 1;
  vector<ull> bs;
  bs.reserve(m);

  for (ull a : as) {
    while (a > not_sumed && bs.size() < m) {
      bs.push_back(not_sumed);
      not_sumed *= 2;
    }

    not_sumed += a;
  }

  while (bs.size() < m) {
    bs.push_back(not_sumed);
    not_sumed *= 2;
  }

  return bs;
}

int main(void) {
#ifdef ONLINE_JUDGE
  freopen("key.in", "r", stdin);
  freopen("key.out", "w", stdout);
#endif
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull n, m;

  cin >> n >> m;

  vector<ull> as(n);

  fore(i, 0, n) {
    cin >> as[i];
  }

  vector<ull> bs = solve(m, as);

  for (ull b : bs) {
    cout << b << ' ';
  }
  cout << '\n';

  return EXIT_SUCCESS;
}
