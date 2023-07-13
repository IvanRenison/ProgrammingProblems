// https://codeforces.com/contest/1820/problem/D

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

vector<pair<ull, ull>> parse1(void) {
  ull n;
  cin >> n;

  vector<pair<ull, ull>> abs(n);
  fore(i, 0, n) {
    ull a, b;
    cin >> a >> b;
    abs[i] = {a, b};
  }

  return abs;
}

vector<pair<ull, ull>> solve1(vector<pair<ull, ull>> abs) {
  ull sum = 0;
  for (auto [a, b] : abs) {
    sum += a * b;
  }

  vector<pair<ull, ull>> ans;
  {
    multiset<pair<ull, ull>> s_abs;
    multiset<pair<ull, ull>> s_bas;

    for (auto [a, b] : abs) {
      s_abs.insert({a, b});
      s_bas.insert({b, a});
    }

    auto s_abs_last = s_abs.end();
    s_abs_last--;

    if (sum % s_abs_last->first == 0) {
      // The first cut was vertical

      auto [a, b] = *s_abs_last;

      ull h = a;
      ull w = sum / a;

      ull h_ = h;
      ull w_ = w;

      if (b <= w) {
        w -= b;

        // Remove only one occurrence of {a, b} from s_abs and one occurrence of {b, a} from s_bas
        s_abs.erase(s_abs.find({a, b}));
        s_bas.erase(s_bas.find({b, a}));

        bool posible = true;

        while (s_abs.size() > 0) {
          auto s_abs_last = s_abs.end();
          s_abs_last--;
          auto [a, b] = *s_abs_last;

          if (a == h) {
            if (b > w) {
              posible = false;
              break;
            }

            w -= b;

            s_abs.erase(s_abs.find({a, b}));
            s_bas.erase(s_bas.find({b, a}));
            continue;
          }

          auto s_bas_last = s_bas.end();
          s_bas_last--;

          b = s_bas_last->first;
          a = s_bas_last->second;

          if (b != w || a > h) {
            posible = false;
            break;
          }

          h -= a;
          s_abs.erase(s_abs.find({a, b}));
          s_bas.erase(s_bas.find({b, a}));
        }

        if (posible && (w == 0 || h == 0)) {
          ans.push_back({h_, w_});
        }
      }
    }
  }
  {
    multiset<pair<ull, ull>> s_abs;
    multiset<pair<ull, ull>> s_bas;

    for (auto [a, b] : abs) {
      s_abs.insert({a, b});
      s_bas.insert({b, a});
    }
    auto s_bas_last = s_bas.end();
    s_bas_last--;
    if (sum % s_bas_last->first == 0) {
      // The first cut was horizontal

      auto [b, a] = *s_bas_last;

      ull w = b;
      ull h = sum / b;

      ull w_ = w;
      ull h_ = h;

      if (a <= h) {
        h -= a;

        // Remove only one occurrence of {b, a} from s_bas and one occurrence of {a, b} from s_abs
        s_abs.erase(s_abs.find({a, b}));
        s_bas.erase(s_bas.find({b, a}));

        bool posible = true;

        while (s_bas.size() > 0) {
          auto s_bas_last = s_bas.end();
          s_bas_last--;
          auto [b, a] = *s_bas_last;

          if (b == w) {
            if (a > h) {
              posible = false;
              break;
            }

            h -= a;

            s_abs.erase(s_abs.find({a, b}));
            s_bas.erase(s_bas.find({b, a}));
            continue;
          }

          auto s_abs_last = s_abs.end();
          s_abs_last--;

          a = s_abs_last->first;
          b = s_abs_last->second;

          if (a != h || b > w) {
            posible = false;
            break;
          }

          w -= b;
          s_abs.erase(s_abs.find({a, b}));
          s_bas.erase(s_bas.find({b, a}));
        }

        if (posible && (h == 0 || w == 0)) {
          ans.push_back({h_, w_});
        }
      }
    }
  }
  if (ans.size() == 2 && ans[0] == ans[1]) {
    ans.pop_back();
  }
  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    vector<pair<ull, ull>> ans = solve1(parse1());
    cout << ans.size() << "\n";
    for (auto [h, w] : ans) {
      cout << h << " " << w << "\n";
    }
  }

  return EXIT_SUCCESS;
}
