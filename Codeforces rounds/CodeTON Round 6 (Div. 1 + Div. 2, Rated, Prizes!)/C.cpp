// https://codeforces.com/contest/1870/problem/C

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

vector<ull> solve1(ull k, vector<ull> as) {
  ull n = as.size();

  vector<bool> colors(k, false);

  vector<pair<ull, ull>> crecientes_init = {{as[0], 0}};
  colors[as[0]] = true;
  fore(i, 1, n) {
    colors[as[i]] = true;
    if (as[i] > crecientes_init.back().first) {
      crecientes_init.push_back({as[i], i});
    }
  }

  vector<pair<ull, ull>> crecientes_back = {{as[n-1], n-1}};
  for(ull i = n-2; i < n; i--) {
    if (as[i] > crecientes_back.back().first) {
      crecientes_back.push_back({as[i], i});
    }
  }

  vector<ull> ans(k);

  fore(c, 0, k) {
    if (colors[c]) {
      auto it_l = lower_bound(crecientes_init.begin(), crecientes_init.end(), make_pair(c,0ull));
      auto it_r = lower_bound(crecientes_back.begin(), crecientes_back.end(), make_pair(c,0ull));

      ull l = it_l->second;
      ull r = it_r->second;

      ull d = r - l + 1;
      ans[c] = d+d;
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {

    ull n, k;
    cin >> n >> k;
    vector<ull> as(n);
    fore(i, 0, n) {
      cin >> as[i];
      as[i]--;
    }

    auto ans = solve1(k, as);
    for(auto a : ans) {
      cout << a << ' ';
    }
    cout << '\n';
  }

  return EXIT_SUCCESS;
}
