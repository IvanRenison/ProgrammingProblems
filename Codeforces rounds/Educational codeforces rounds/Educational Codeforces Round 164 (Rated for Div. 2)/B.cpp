// https://codeforces.com/contest/1954/problem/B

#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

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
typedef tuple<ull, ull, ull, ull, ull> uuuuu;
typedef vector<uuuuu> vuuuuu;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;
typedef tuple<ll, ll, ll, ll> iiii;
typedef vector<iiii> viiii;
typedef tuple<ll, ll, ll, ll, ll> iiiii;
typedef vector<iiiii> viiiii;
typedef long double ld;
typedef vector<ld> vd;
typedef pair<ld, ld> dd;
typedef vector<dd> vdd;
typedef tuple<ld, ld, ld> ddd;
typedef vector<ddd> vddd;
typedef tuple<ld, ld, ld, ld> dddd;
typedef vector<dddd> vdddd;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;
const ld eps = 1e-7;

bool beautiful(vu as) {
  ull c = as[0];

  if (as.back() != c) {
    return false;
  }

  if (as.size() == 1) {
    return true;
  }

  fore(i, 0, as.size() - 2) {
    if (as[i + 1] != c) {
      if (as[i + 2] != c) {
        return false;
      }
      as[i + 1] = c;
    }
  }

  return true;
}

optional<ull> force(const vu& as) {
  ull n = as.size();

  ull ans = inf;

  fore(x, 0, (1 << n) - 1) {
    vu bs;
    fore(i, 0, n) {
      if (!(x & (1 << i))) {
        bs.push_back(as[i]);
      }
    }

    if (!beautiful(bs)) {
      ans = min(ans, (ull)__builtin_popcountll(x));
    }
  }

  if (ans == inf) {
    return {};
  }
  return ans;

}


optional<ull> solve(const vu& as) {
  ull n = SZ(as);

  set<ull> s;
  fore(i, 0, n) {
    s.insert(as[i]);
  }

/*   if (s.size() >= 3) {
    return 1;
  } */
  if (s.size() == 1) {
    return {};
  }

  ull c = as[0];

  ull dist_to_not_c = 0;

  fore(i, 1, n) {
    if (as[i] != c) {
      dist_to_not_c = i;
      break;
    }
  }

  ull dist_to_not_c_back = 0;

  fore(i, 0, n) {
    if (as[n - 1 - i] != c) {
      dist_to_not_c_back = i;
      break;
    }
  }

  ull ans = min(dist_to_not_c, dist_to_not_c_back);

  ull last_no_c = dist_to_not_c;
  fore(i, dist_to_not_c + 1, n) {
    if (as[i] != c) {
      ans = min(ans, i - last_no_c - 1);
      last_no_c = i;
    }
  }

  return ans;
}



int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  fore(i, 0, t) {

    ull n;
    cin >> n;

    vu as(n);
    fore(j, 0, n) {
      cin >> as[j];
    }

    auto ans = solve(as);

    if (ans.has_value()) {
      cout << *ans << '\n';
    } else {
      cout << "-1\n";
    }
  }

/*   fore(_, 0, 10000) {
    ull n = rand() % 10 + 1;

    vu as(n);
    fore(i, 0, n) {
      as[i] = rand() % 5;
    }

    if (beautiful(as)) {

      auto ans1 = solve(as);
      auto ans2 = force(as);

      if (ans1 != ans2) {
        cerr << "FAIL\n";
        cerr << n << '\n';
        for (auto a : as) {
          cerr << a << ' ';
        }
        cerr << '\n';
        cerr << "ans1 = " << ans1.value_or(-1) << '\n';
        cerr << "ans2 = " << ans2.value_or(-1) << '\n';
        return EXIT_FAILURE;
      }
    }
  } */

  return EXIT_SUCCESS;
}
