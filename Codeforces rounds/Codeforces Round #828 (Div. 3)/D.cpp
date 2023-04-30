// https://codeforces.com/contest/1744/problem/D

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

optional<ull> solve1(vector<ull> as) {
  ull n = as.size();

  ull amount_2s = 0;

  for(ull a : as) {
    amount_2s += __builtin_ctz(a);
  }

  vector<ull> i_amounts_2s(n);
  fore(i, 0, n) {
    i_amounts_2s[i] = __builtin_ctz(i+1);
  }

  sort(i_amounts_2s.begin(), i_amounts_2s.end(), greater());

  ull ans = 0;
  ull i = 0;

  while (amount_2s < n && i < n) {
    ull c2 = i_amounts_2s[i];
    if (c2 != 0) {
      amount_2s += c2;
      ans++;
    }
    i++;
  }

  if (amount_2s < n) {
    return {};
  }
  else {
    return ans;
  }
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    optional<ull> ans = solve1(parse1());
    if (ans.has_value()) {
        cout << ans.value() << "\n";
    }
    else {
        cout << -1 << "\n";
    }
  }

  return EXIT_SUCCESS;
}
