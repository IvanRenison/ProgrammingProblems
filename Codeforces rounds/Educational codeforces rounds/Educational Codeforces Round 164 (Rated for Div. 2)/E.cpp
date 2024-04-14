// https://codeforces.com/contest/1954/problem/E

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef tuple<ull, ull, ull> uuu;
typedef vector<uuu> vuuu;
typedef tuple<ull, ull, ull, ull> uuuu;
typedef vector<uuuu> vuuuu;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()


struct presums {
  typedef ull T;
  T op(T a, T b) { return a + b; }
  T rev(T a, T b) { return a - b; }
  constexpr static T neut = 0;
  // rev(op(a, b), b) = a

  ull n;
  vector<T> as;

  presums(ull n) : n(n), as(n + 1) {}

  void update(ull i, ull j, T v) { // [i, j)
    as[i] = op(as[i], v);
    as[j] = rev(as[j], v);
  }

  vector<T> build() {
    vector<T> ans(n);
    ans[0] = as[0];
    fore(i, 1, n) {
      ans[i] = op(ans[i - 1], as[i]);
    }
    return ans;
  }
};

vuuu calc_divs(ull a, ull k_max) {
  // divs[i] = {d, l, r} ⇔ ∀k ∈ [l, r) : ⌈a / k⌉ = d
  vuuu divs = {{a, 1, 2}};

  for (ull k = 2; k <= k_max;) {
    ull d = (a + k - 1) / k;

    ull k_ = d == 1 ? k_max + 1 : (a + d - 1 - 1) / (d - 1);

    divs.push_back({d, k, k_});

    k = k_;
  }

  return divs;
}

vuuuu intersect_divs(vuuu divs0, vuuu divs1) {
  ull n1 = divs1.size();
  vuuuu ans;

  ull i1 = 0;
  for (auto [d0, l0, r0] : divs0) {
    //assert(i1 < n1);
    auto [d1, l1, r1] = divs1[i1];

    while (r1 <= r0) {
      ans.push_back({d0, d1, l0, r1});
      l0 = r1;
      i1++;
      if (i1 == n1) {
        break;
      }
      tie(d1, l1, r1) = divs1[i1];
    }

    if (l0 < r0) {
      ans.push_back({d0, d1, l0, r0});
    }

  }

  return ans;
}


vu solve(const vu& as) {
  ull n = as.size();

  ull max_a = *max_element(ALL(as));

  presums ans(max_a);
  fore(k, 1, max_a + 1) {
    ans.update(k - 1, k, (as[0] + k - 1) / k);
  }

  vuuu last_divs = calc_divs(as[0], max_a);

  fore(i, 1, n) {
    ull a = as[i];
    if (a > as[i - 1]) {
      vuuu divs = calc_divs(a, max_a);
      vuuuu this_divs = intersect_divs(divs, last_divs);
      // this_divs[i] = {d, e, l, r} ⇔ ∀k ∈ [l, r) : ⌈a / k⌉ = d ∧ ⌈as[i - 1] / k⌉ = e

      for (auto [d, e, l, r] : this_divs) {
        //assert(d >= e);
        ans.update(l - 1, r - 1, d - e);
      }

      last_divs = move(divs);
    } else if (i + 1 != n && a < as[i + 1]) {
      last_divs = calc_divs(a, max_a);
    }
  }

  return ans.build();
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull n;
  cin >> n;
  vu as(n);
  for (ull& a : as) {
    cin >> a;
  }

  vu ans = solve(as);
  for (ull a : ans) {
    cout << a << ' ';
  }
  cout << '\n';

/*   ull n = 1e5;
  vu as(n);
  for (ull& a : as) {
    a = rand() % n + 1;
  }

  cout << n << '\n';
  for (ull a : as) {
    cout << a << ' ';
  }
  cout << '\n'; */

  return EXIT_SUCCESS;
}
