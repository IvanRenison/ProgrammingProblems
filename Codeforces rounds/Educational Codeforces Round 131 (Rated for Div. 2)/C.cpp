// https://codeforces.com/contest/1701/problem/C

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

pair<ull, vector<ull>> parse1(void) {
  ull n, m;

  cin >> n >> m;

  vector<ull> as(m);
  fore(i, 0, m) {
    ull a;
    cin >> a;
    as[i] = a - 1;
  }

  return {n, as};
}

bool possible_for_time(ull n, vector<ull> as, ull t) {
  ull m = as.size();

  vector<ull> good_at(n);
  for (ull a : as) {
    good_at[a] += 1;
  }

  ull done_tasks = 0;

  for (ull p_ga : good_at) {
    if (p_ga >= t) {
      done_tasks += t;
    } else {
      done_tasks += p_ga + (t - p_ga) / 2;
    }
  }

  return done_tasks >= m;
}

template <typename T> ull bin_search(function<bool(T)> f, vector<T> it) {
  ull lower = 0;
  ull upper = it.size();
  if (f(it[lower])) {
    return lower;
  }
  if (!f(it[upper - 1])) {
    return upper;
  }
  while (lower + 1 < upper) {
    ull m = (lower + upper) / 2;
    if (f(it[m])) {
      upper = m;
    } else {
      lower = m;
    }
  }

  return upper;
}

ull solve1(ull n, vector<ull> as) {
  ull m = as.size();

  vector<ull> it(m / n + 2);

  fore(i, 0, m / n + 2) {
    it[i] = i + m / n;
  }

  // Lambda function
  ull i_ans =
      bin_search<ull>([&](ull t) { return possible_for_time(n, as, t); }, it);

  return it[i_ans];
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    auto [n, as] = parse1();
    cout << solve1(n, as) << "\n";
  }

  return EXIT_SUCCESS;
}
