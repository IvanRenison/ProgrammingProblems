//

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

tuple<ull, ull, ull> parse1(void) {
  ull n, k, g;
  cin >> n >> k >> g;
  return {n, k, g};
}

ull solve1(ull n, ull k, ull g) {

  /*
  Idea: Darle (g-1)/2 a cada uno salvo el último y darle el resto a ese
  */

  ull amount_firsts = (n - 1) * ((g - 1) / 2);

  if (amount_firsts > k * g) {
    return k * g;
  }

  ull amount_to_n = k * g - amount_firsts;

  ull r = amount_to_n % g;
  if (r >= (g+1) / 2) {
    return k * g - (amount_to_n + (g - r));
  } else {
    return k * g - (amount_to_n - r);
  }
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    auto [n, k, g] = parse1();
    auto ans = solve1(n, k, g);
    cout << ans << "\n";
  }

  return EXIT_SUCCESS;
}
