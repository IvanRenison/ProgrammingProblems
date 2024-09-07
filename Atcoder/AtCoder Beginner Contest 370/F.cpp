// https://atcoder.jp/contests/abc370/tasks/abc370_f

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


uu solve(ull K, vu& As) {
  ull N = As.size();
  vu As_sums(N + 1);
  fore(i, 0, N) {
    As_sums[i + 1] = As_sums[i] + As[i];
  }
  auto sum = [&](ull l, ull r) -> ull {
    return As_sums[r] - As_sums[l];
  };

  auto can = [&](ull w) -> bool {
    vu jumps(N, inf);

    fore(i, 0, N) {
      if (sum(i, N) < w) {
        break;
      }
      ull l = i + 1, r = N;
      if (sum(i, i + 1) >= w) {
        jumps[i] = i + 1;
        continue;
      }
      while (l + 1 < r) {
        ull m = (l + r) / 2;
        if (sum(i, m) >= w) {
          r = m;
        } else {
          l = m;
        }
      }
      jumps[i] = r;
    }

    vuu total_jumps(N);
    for(ull i = N; i--; ) {
      if (jumps[i] == inf) {
        total_jumps[i] = {inf, 0};
      } else if (jumps[i] == N) {
        total_jumps[i] = {N, 1};
      } else if (total_jumps[jumps[i]].first == inf) {
        total_jumps[i] = {jumps[i], 1};
      } else {
        total_jumps[i] = {total_jumps[jumps[i]].first, total_jumps[jumps[i]].second + 1};
      }
    }

    fore(i, 0, N) {
      auto [j, c] = total_jumps[i];
      if (j == inf) {
        break;
      }
      if (c >= K) {
        return true;
      } else if (c + 1 == K && sum(0, i) + sum(j, N) >= w) {
        return true;
      }
    }

    return false;
  };

  ull l = 0, r = As_sums[N];
  while (l + 1 < r) {
    ull m = (l + r) / 2;
    if (can(m)) {
      l = m;
    } else {
      r = m;
    }
  }


  {
    ull w = l;

    vu jumps(N, inf);

    fore(i, 0, N) {
      if (sum(i, N) < w) {
        break;
      }
      ull l = i + 1, r = N;
      if (sum(i, i + 1) >= w) {
        jumps[i] = i + 1;
        continue;
      }
      while (l + 1 < r) {
        ull m = (l + r) / 2;
        if (sum(i, m) >= w) {
          r = m;
        } else {
          l = m;
        }
      }
      jumps[i] = r;
    }

    vuu total_jumps(N);
    for(ull i = N; i--; ) {
      if (jumps[i] == inf) {
        total_jumps[i] = {inf, 0};
      } else if (jumps[i] == N) {
        total_jumps[i] = {N, 1};
      } else if (total_jumps[jumps[i]].first == inf) {
        total_jumps[i] = {jumps[i], 1};
      } else {
        total_jumps[i] = {total_jumps[jumps[i]].first, total_jumps[jumps[i]].second + 1};
      }
    }

    vu As_sums_rev(N + 1);
    reverse(ALL(As));
    fore(i, 0, N) {
      As_sums_rev[i + 1] = As_sums_rev[i] + As[i];
    }

    auto sum_rev = [&](ull l, ull r) -> ull {
      return As_sums_rev[r] - As_sums_rev[l];
    };

    vi jumps_rev(N, inf);
    fore(i, 0, N) {
      if (sum_rev(i, N) < w) {
        break;
      }
      ull l = i + 1, r = N;
      if (sum_rev(i, i + 1) >= w) {
        jumps_rev[i] = i + 1;
        continue;
      }
      while (l + 1 < r) {
        ull m = (l + r) / 2;
        if (sum_rev(i, m) >= w) {
          r = m;
        } else {
          l = m;
        }
      }
      jumps_rev[i] = r;
    }

    vii total_jumps_rev(N);
    for(ull i = N; i--; ) {
      if (jumps_rev[i] == inf) {
        total_jumps_rev[i] = {inf, 0};
      } else if (jumps_rev[i] == N) {
        total_jumps_rev[i] = {N, 1};
      } else if (total_jumps_rev[jumps_rev[i]].first == inf) {
        total_jumps_rev[i] = {jumps_rev[i], 1};
      } else {
        total_jumps_rev[i] = {total_jumps_rev[jumps_rev[i]].first, total_jumps_rev[jumps_rev[i]].second + 1};
      }
    }

    ull count = 0;

    {
      auto [j, c] = total_jumps[0];
      if (c >= K) {
        count++;
      }
    }
    fore(i, 1, N) {
      auto [j, c] = total_jumps[i];
      auto [j_rev, c_rev] = total_jumps_rev[N - i];
      if (c + c_rev >= K) {
        count++;
      } else {
        if (j == inf) {
          j = i;
        }
        if (j_rev == inf) {
          j_rev = N - i;
        }
        if (c + c_rev + 1 == K && sum(j, N) + sum_rev(j_rev, N) >= w) {
          count++;
        }
      }
    }


    count = N - count;
    return {w, count};
  }

}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull N, K;
  cin >> N >> K;
  vu As(N);
  fore(i, 0, N) {
    cin >> As[i];
  }

  auto [w, c] = solve(K, As);
  cout << w << ' ' << c << '\n';
}
