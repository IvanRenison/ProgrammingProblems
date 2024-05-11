// https://codeforces.com/group/4zVk9dZl6Q/contest/390414/problem/I

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

ull my_random(void) {
  ull x = 0;
  fore(i, 0, 4) {
    x = (x << 16) ^ rand();
  }
  return ~x;
}

vector<optional<pair<ull, optional<ull>>>> values;

pair<ull, optional<ull>> query(ull i) {
  if (values[i].has_value()) {
    return values[i].value();
  }

  cout << "? " << i + 1 << endl;
  ll value, next;
  cin >> value >> next;

  values[i] = {
      ull(value), (next == -1 ? nullopt : optional<ull>(ull(next - 1)))};

  return values[i].value();
}

optional<ull> solve(ull n, ull start, ull x) {
  query(start);
  if (n < 2000) {
    fore(i, 0, n) {
      if (i != start) {
        query(i);
      }
    }
  } else {
    // generate 1000 distinct random numbers between 0 and n - 1
    set<ull> randoms;
    while (randoms.size() < 1000) {
      randoms.insert(my_random() % n);
    }

    for (ull i : randoms) {
      if (i != start) {
        query(i);
      }
    }
  }

  optional<ull> i;
  fore(j, 0, n) {
    if (values[j].has_value()) {
      auto [v, n] = values[j].value();
      if (v == x) {
        return x;
      } else if (v < x) {
        if (!i.has_value() || v > values[i.value()].value().first) {
          i = j;
        }
      }
    }
  }

  if (!i.has_value()) {
    return values[start].value().first;
  }

  ull j = i.value();

  while (true) {
    auto [v, next] = values[j].value();

    if (v >= x) {
      return v;
    }

    if (!next.has_value()) {
      return {};
    }

    query(next.value());

    j = next.value();
  }
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  srand(time(NULL));

  ull n, start, x;

  cin >> n >> start >> x;
  start--;

  values = vector<optional<pair<ull, optional<ull>>>>(n);

  optional<ull> ans = solve(n, start, x);

  if (ans.has_value()) {
    cout << "! " << ans.value() << endl;
  } else {
    cout << "! -1" << endl;
  }

  return EXIT_SUCCESS;
}
