// https://codeforces.com/contest/1833/problem/D

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

vector<ull> parse1(void) {
  ull n;
  cin >> n;

  vector<ull> ps(n);
  fore(i, 0, n) {
    cin >> ps[i];
  }

  return ps;
}

vector<ull> solve1(vector<ull> ps) {
  ull n = ps.size();

  if (n == 1) {
    return ps;
  }

  ull max_index = 0;
  ull max = ps[0];
  fore(i, 1, n) {
    if (ps[i] > max) {
      max = ps[i];
      max_index = i;
    }
  }

  if (max_index == 0) {
    ull second_max_index = 1;
    ull second_max = ps[1];
    fore(i, 2, n) {
      if (ps[i] > second_max) {
        second_max = ps[i];
        second_max_index = i;
      }
    }

    max_index = second_max_index;
    max = second_max;
  }

  vector<ull> ans0;
  ans0.reserve(n);

  { // Option that r = max_index - 1
    fore(i, max_index, n) {
      ans0.push_back(ps[i]);
    }

    ull r = max_index - 1;
    ull l = r;
    ans0.push_back(ps[l]);
    l--;

    while (l <= n && ps[l] >= ps[0]) {
      ans0.push_back(ps[l]);
      l--;
    }

    fore(i, 0, l + 1) {
      ans0.push_back(ps[i]);
    }
  }

  vector<ull> ans1;
  ans1.reserve(n);

  if (max_index == n - 1) { // Option that r = l = max_index = n-1
    ans1.push_back(ps[max_index]);

    fore(i, 0, max_index) {
      ans1.push_back(ps[i]);
    }
    if (ans0 > ans1) {
      return ans0;
    } else {
      return ans1;
    }
  }

  return ans0;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    vector<ull> ps = parse1();
    vector<ull> ans = solve1(ps);
    fore(j, 0, ans.size()) {
      cout << ans[j] << ' ';
    }
    cout << '\n';
  }

  return EXIT_SUCCESS;
}
