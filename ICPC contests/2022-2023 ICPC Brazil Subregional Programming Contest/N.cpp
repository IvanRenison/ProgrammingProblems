// https://codeforces.com/gym/103960/problem/N

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

ull solve(vector<ull> as, vector<ull> bs, ull K, ull L) {
  ull N = as.size();

  ull as_sum = 0;

  multiset<ull> bs_values_used;
  multiset<ull> bs_values_unused;

  fore(i, 0, K) {
    ull a = as[i];
    as_sum += a;
    bs_values_used.insert(bs[i]);
  }

  // Keep only L in bs_values_used
  while (bs_values_used.size() > L) {
    multiset<ull>::iterator it = bs_values_used.begin();
    bs_values_unused.insert(*it);
    bs_values_used.erase(it);
  }

  ull bs_used_sum = 0;

  for (ull b : bs_values_used) {
    bs_used_sum += b;
  }

  ull max_sum = as_sum + bs_used_sum;

  fore(i, 1, K + 1) {
    ull a_old = as[K - i];
    ull b_old = bs[K - i];
    ull a_new = as[N - i];
    ull b_new = bs[N - i];

    as_sum -= a_old;
    as_sum += a_new;

    multiset<ull>::iterator b_old_it = bs_values_used.find(b_old);

    if (b_old_it != bs_values_used.end()) {
      bs_values_unused.insert(b_new);
      bs_values_used.erase(b_old_it);
      bs_used_sum -= b_old;

      multiset<ull>::iterator bs_used_new = bs_values_unused.end();
      bs_used_new--;

      bs_values_used.insert(*bs_used_new);
      bs_used_sum += *bs_used_new;
      bs_values_unused.erase(bs_used_new);
    } else if (b_new > *bs_values_used.begin()) {
      multiset<ull>::iterator bs_unused_new = bs_values_used.begin();
      bs_values_unused.insert(*bs_unused_new);
      bs_values_used.erase(bs_unused_new);
      bs_used_sum -= *bs_unused_new;
      bs_values_used.insert(b_new);
      bs_used_sum += b_new;
    } else {
      bs_values_unused.erase(bs_values_unused.find(b_old));
      bs_values_unused.insert(b_new);
    }

    max_sum = max(max_sum, as_sum + bs_used_sum);
  }

  return max_sum;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull N;
  cin >> N;

  vector<ull> as(N);
  vector<ull> bs(N);

  fore(i, 0, N) {
    cin >> as[i];
  }
  fore(i, 0, N) {
    cin >> bs[i];
  }

  ull K, L;
  cin >> K >> L;

  cout << solve(as, bs, K, L) << endl;

  return EXIT_SUCCESS;
}
