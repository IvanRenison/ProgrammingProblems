// https://codeforces.com/group/hzSLIARNBN/contest/465113/problem/I

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

constexpr ull MAXR = 10000;

ull skip_bit(ull i, ull bits) {
  ull n = 64 - __builtin_clz(bits);
  ull ans = 0;

  fore(j, 0, i) {
    ans |= bits & (1ull << j);
  }
  fore(j, i, n) {
    ans |= (bits << 1) & (1ull << (j + 1));
  }

  return ans;
}

double prob_x_with_max_bits(const vector<pair<ull, ull>>& LRs, ull x, ull bits) {
  ull n = LRs.size();
  assert(__builtin_popcount(bits) >= 2);

  double ans = 1.0;
  fore(i, 0, n) {
    auto [Li, Ri] = LRs[i];
    if ((bits & (1 << i)) != 0) {
      if (Ri < x || Li > x) {
        return 0.0;
      }
      ans *= 1.0 / (double)(Ri - Li + 1);
    } else {
      if (Li > x) {
        return 0.0;
      }
      ans *= (double)(min(x - 1, Ri) - Li + 1) / (double)(Ri - Li + 1);
    }
  }

  return ans;
}

/* Probability that the answer is x with the maximum beeing in i (i > x)
 * and the other being == x if bits[j] == 1, < x else
 * bits[i] is ignored */
double prob_x_with_max_i_bits(const vector<pair<ull, ull>>& LRs, ull x, ull i, ull bits) {
  ull n = LRs.size();

  auto [Li, Ri] = LRs[i];

  if (Ri <= x) {
    return 0.0;
  }

  double ans = (double)(Ri - max(x + 1, Li) + 1) / (double)(Ri - Li + 1);

  fore(j, 0, n) if (i != j) {
    if ((bits & (1 << j)) != 0) {
      auto [Lj, Rj] = LRs[j];
      if (Rj < x || Lj > x) {
        return 0.0;
      }
      ans *= 1.0 / (double)(Rj - Lj + 1);
    } else {
      auto [Lj, Rj] = LRs[j];
      if (Lj > x) {
        return 0.0;
      }
      ans *= (double)(min(x - 1, Rj) - Lj + 1) / (double)(Rj - Lj + 1);
    }
  }

  return ans;
}

/* Probability that the answer is x */
double prob_x(const vector<pair<ull, ull>>& LRs, ull x) {
  ull n = LRs.size();

  double ans = 0.0;

  fore(bits, 0, 1 << n) if (__builtin_popcount(bits) >= 2) {
    ans += prob_x_with_max_bits(LRs, x, bits);
  }

  fore(i, 0, n) {
    fore(bits, 0, 1 << (n - 1)) if (__builtin_popcount(bits) >= 1) {
      ans += prob_x_with_max_i_bits(LRs, x, i, skip_bit(i, bits));
    }
  }

  return ans;
}

double solve(const vector<pair<ull, ull>>& LRs) {
  vector<double> probs(MAXR);

  double ans = 0.0;

  fore(x, 1, MAXR + 1) {
    double prob = prob_x(LRs, x);
    ans += (double)x * prob;
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  cout << setprecision(10);

  ull n;
  cin >> n;

  vector<pair<ull, ull>> LRs(n);
  for (auto& [L, R] : LRs) {
    cin >> L >> R;
  }

  auto ans = solve(LRs);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
