//

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

vector<ull> parse1(void) {
  ull n;
  cin >> n;

  vector<ull> as(n);
  fore(i, 0, n) {
    cin >> as[i];
  }

  return as;
}

bool is_palindrome(vector<ull> as) {
  ull n = as.size();

  fore(i, 0, n / 2) {
    if (as[i] != as[n - i - 1]) {
      return false;
    }
  }

  return true;
}

ull solve1(vector<ull> as) {
  ull n = as.size();

  if (is_palindrome(as)) {
    return 0;
  }

  ull n_div_2 = n / 2;
  vector<ull> a_difs(n_div_2);
  fore(i, 0, n_div_2) {
    if (as[i] > as[n - i - 1]) {
      a_difs[i] = as[i] - as[n - i - 1];
    } else {
      a_difs[i] = as[n - i - 1] - as[i];
    }
  }

  ull common_gcd = a_difs[0];
  fore(i, 1, n_div_2) {
    common_gcd = __gcd(common_gcd, a_difs[i]);
  }

  return common_gcd;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    cout << solve1(parse1()) << "\n";
  }

  return EXIT_SUCCESS;
}
