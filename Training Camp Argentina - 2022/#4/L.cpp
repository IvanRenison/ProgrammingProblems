// https://codeforces.com/group/4zVk9dZl6Q/contest/391067/problem/L
#include <bits/stdc++.h>
#define pb push_back
#define fst first
#define snd second
#define fore(i, a, b) for (ull i = a, ggdem = b; i < ggdem; ++i)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(), x.end()
#define mset(a, v) memset((a), (v)sizeof(a))
#define FIN                                                                    \
  ios::sync_with_stdio(0);                                                     \
  cin.tie(0);                                                                  \
  cout.tie(0)
using namespace std;
typedef unsigned long long ull;
typedef long long ll;

pair<ull, vector<ull>> solve(ull A, ull cf, ull cm, ull m, vector<ull>& as) {
  ull n = as.size();

  vector<pair<ull, ull>> asi(n);
  fore(i, 0, n) {
    asi[i] = {as[i], i};
  }

  sort(asi.begin(), asi.end());

  // Count trailing As
  ull trailing_As = 0;
  for (ull i = n - 1; i < n; i--) {
    if (asi[i].first == A) {
      trailing_As++;
    } else {
      break;
    }
  }

  ull base_force = trailing_As * cf + asi[0].first * cm;
  ull small_n = n - trailing_As;

  if (small_n == 0) {
    // Case in which everything is at maximum
    return {base_force, as};
  }

  vector<ull> prefixes_sum(small_n + 1);
  fore(i, 0, small_n) {
    prefixes_sum[i + 1] = prefixes_sum[i] + asi[i].first;
  }

  if (A * small_n - prefixes_sum[small_n] <= m) {
    // We can increase everything to maximum
    return {n * cf + A * cm, vector<ull>(n, A)};
  }

  // Increase min
  ull increase_min_extra_force = 0;
  ull increase_min_count = 0;
  ull increase_min_value = asi[0].first;
  ull increase_min_cost = 0;
  fore(i, 0, small_n) {
    ull a = asi[i].first;
    ull a_next = i + 1 == small_n ? A : asi[i + 1].first;

    if (a == a_next) {
      continue;
    }

    ull available_coins = m - increase_min_cost;
    ull available_increase = available_coins / (i + 1);
    if (available_increase == 0) {
      break;
    }
    ull increase = min(a_next - a, available_increase);
    increase_min_value += increase;
    increase_min_extra_force += increase * cm;
    increase_min_cost += increase * (i + 1);
    increase_min_count = i + 1;
    if (increase == available_increase) {
      break;
    }
  }

  ull best_n_max = 0;
  ull best_extra_force = increase_min_extra_force;
  ull best_min = increase_min_value;

  // Take some to max ans go decreasing min
  ull take_to_max_cost = 0;
  ull take_to_max_extra_force = 0;
  fore(n_max, 0, small_n) {
    // n_max+1 = amount that we will take to A (without counting trailing_As)
    ull i = small_n - n_max - 1;
    ull a = asi[i].first;
    if (i + 1 == increase_min_count) {
      increase_min_count--;
      increase_min_cost -= (increase_min_value - a);
    }

    take_to_max_cost += A - a;
    take_to_max_extra_force += cf;

    while (increase_min_count > 0 && increase_min_cost + take_to_max_cost > m) {
      // These will probable cause a TLE
      increase_min_value--;
      increase_min_cost -= increase_min_count;
      increase_min_extra_force -= cm;
      while (increase_min_count > 0 &&
             increase_min_value == asi[increase_min_count - 1].first) {
        increase_min_count--;
      }
    }

    if (increase_min_cost + take_to_max_cost > m) {
      break;
    }

    if (increase_min_extra_force + take_to_max_extra_force > best_extra_force) {
      best_extra_force = increase_min_extra_force + take_to_max_extra_force;
      best_n_max = n_max + 1;
      best_min = increase_min_value;
    }
  }

  // Reconstruct answer
  vector<ull> ans(n);
  fore(j, 0, n) {
    auto [a, i] = asi[j];
    if (j >= small_n - best_n_max) {
      ans[i] = A;
    } else if (a < best_min) {
      ans[i] = best_min;
    } else {
      ans[i] = a;
    }
  }

  return {base_force + best_extra_force, ans};
}

/*

3 5 10 1 5
1 3 1


1 1 3
  2 2 3   -- 2 coins +1force
    3 3 3   -- 4 coins +2force
    ❌2 2 5   -- 6 coins +11coins
  1 1 5  -- 2 coins +10force
    2 2 5  -- 4 coins +11force
      ❌3 3 5  -- 6 coins ...
    ❌1 5 5  -- 6 coins +10force



3 5 1 10 5
1 3 1

1 1 3
  2 2 3   -- 2 coins + 10force



Vamos bien, pero es más fácil iterar por (cuantos llevo al máximo)


*/

int main() {
  FIN;

  ull n, A, cf, cm, m;
  cin >> n >> A >> cf >> cm >> m;

  vector<ull> as(n);
  for (ull& a : as) {
    cin >> a;
  }

  auto [k, as_] = solve(A, cf, cm, m, as);
  cout << k << '\n';
  fore(i, 0, n) {
    cout << as_[i];
    if (i + 1 != n) {
      cout << ' ';
    }
  }
  cout << '\n';

  return 0;
}
