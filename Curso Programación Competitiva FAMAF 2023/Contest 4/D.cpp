// https://codeforces.com/group/id8eYTCwzg/contest/444404/problem/D

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

#define MOD (ull(1e9 + 7))

ull add_mod(ull x, ull y) {
  return x + y < MOD ? x + y : x + y - MOD;
}

#define MAXN (ull(4 * 1e4))

ull parse1(void) {
  ull n;
  cin >> n;
  return n;
}

/*

Notar que la cantidad de palindromos menores que 4⋅10^4 es bastante poco

dp[x][y] = Formas de sumar y usando los primeros x palindromos

Parecido al problema de la mochila

dp[x][y] = dp[x][y - palindromo[x]] + dp[x-1][y]

*/

ull solutions[MAXN + 1];

bool is_palindrome(int x) {
  int x1 = x;
  int r = 0;
  while (x1 != 0) {
    int c = x1 % 10;
    r = r * 10 + c;
    x1 = x1 / 10;
  }
  return r == x;
}

void init(void) {
  vector<ull> palindromes;
  fore(x, 0, MAXN + 1) {
    if (is_palindrome(x)) {
      palindromes.push_back(x);
    }
  }

  ull x = palindromes.size();

  vector<array<ull, MAXN + 1>> dp(x);

  fore(i, 0, x) {
    dp[i][0] = 1;
  }

  fore(j, 1, MAXN + 1) {
    dp[0][j] = 0;
  }

  fore(i, 1, x) {
    ull p = palindromes[i];
    fore(j, 1, MAXN + 1) {
      if (p <= j) {
        dp[i][j] = add_mod(dp[i - 1][j], dp[i][j - p]);
      } else {
        dp[i][j] = dp[i - 1][j];
      }
    }
  }

  fore(j, 0, MAXN + 1) {
    solutions[j] = dp[x - 1][j];
  }
}

ull solve1(ull n) {
  return solutions[n];
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  init();

  ull t;

  cin >> t;

  fore(i, 0, t) {
    auto x = parse1();
    auto ans = solve1(x);
    cout << ans << "\n";
  }

  return EXIT_SUCCESS;
}
