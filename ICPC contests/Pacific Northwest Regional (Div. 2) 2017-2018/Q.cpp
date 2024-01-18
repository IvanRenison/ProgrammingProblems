// https://codeforces.com/gym/101652

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;

static inline long long parse(void) {
  long long res;
  cin >> res;

  return res;
}

static inline long long solve(long long n) {
  long double res = ((long double)n - 1.0 / 2.0) -
                    sqrt((long double)(2 * n * n - 2 * n + 1)) / 2.0;

  return ceil(res);

  /*
    sum(i = 1 to n, n - i)
    = n - 1 + n - 2 + n - 3 + ... + n - n
    = n*n - n*(n+1)/2
    = n*n - n*n/2 - n/2
    = n*n/2 - n/2
    = n*(n-1)/2

    sum(i = 1 to x, n - i) = n*(n-1)/4
    sum(i = 1 to x, n) - sum(i = 1 to x, i) = n*(n-1)/4
    x*n - x*(x+1)/2 = n*(n-1)/4
    x*n - x*x/2 - x/2 = n*n/4 - n/4
    - x*x/2 + x*(n-1/2) - n*n/4 + n/4 = 0

    x = (- (n-1/2) +- sqrt((n-1/2)**2 - 4 * (-1/2) * (-n*n/4 + n/4)))/(2 * (-1/2))
    x = (n-1/2) +- sqrt((n-1/2)**2 - n*n/2 + n/2)
    x = (n-1/2) +- sqrt(n**2 - n + 1/4 - n*n/2 + n/2)
    x = (n-1/2) +- sqrt(n**2 / 2 - n/2 + 1/4)
    x = (n-1/2) +- sqrt(2*n**2 - 2*n + 1)/2
  */
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  long long res = solve(parse());

  cout << res << endl;

  return EXIT_SUCCESS;
}
