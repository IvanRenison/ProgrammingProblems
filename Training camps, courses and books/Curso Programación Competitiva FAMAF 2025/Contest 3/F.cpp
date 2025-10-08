// https://codeforces.com/group/Xaa6lwRoge/contest/613703/problem/F

/* #ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif */

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



ll max_subarr_sum(const vi& as, ull begin, ull end) {

  ll ans = 0;
  ll sum = 0;
  ll m_sum = 0;
  for (auto it = begin; it != end; ++it) {
    sum += as[it];
    if (sum < m_sum) {
      m_sum = sum;
    }
    if (sum - m_sum > ans) {
      ans = sum - m_sum;
    }
  }

  return ans;
}

ll max_subarr_sum_le_s(const vi& as, ull s) {
  ull n = as.size();
  assert(s <= n);
  ull ans = 0;
  fore(i, 0, n - s + 1) {
    ull this_ans = max_subarr_sum(as, i, i + s);
    if (this_ans > ans) {
      ans = this_ans;
    }
  }
  return ans;
}

ll max_subarr_sum_gt_s(const vi& as, ull s) {
  ull n = as.size();
  assert(s <= n);

  ll ans = -inf;
  ll sum = 0;
  fore(i, 0, s) {
    sum += as[i];
  }


  ll ssum = 0;
  ll min_ssum = 0;
  fore(i, s, n) {
    sum += as[i];
    ssum += as[i - s];
    if (ssum < min_ssum) {
      min_ssum = ssum;
    }
    ll this_ans = sum - min_ssum;
    if (this_ans > ans) {
      ans = this_ans;
    }
  }


  return ans;
}

ll solve(ull k, ll x, vi& as) {
  ull n = as.size();

  vi as_sums(n + 1);
  fore(i, 0, n) {
    as_sums[i + 1] = as_sums[i] + as[i];
  }


  ll ans = 0;
  if (x >= 0) {
    vi axs = as;
    for (ll& a : axs) {
      a -= x;
    }

    // solutions of size less or equal than k
    fore(i, 0, n) {
      ll sum = 0;
      fore(j, i, min(n, i + k)) {
        sum += as[j] + x;
        if (sum > ans) {
          ans = sum;
        }
      }
    }

    // solutions of size greater than k
    if (k < n) {
      ll this_ans = max_subarr_sum_gt_s(axs, k);
      this_ans += 2 * x * k;
      if (this_ans > ans) {
        ans = this_ans;
      }
    }

  } else {
    vi axs = as;
    for (ll& a : axs) {
      a -= x;
    }

    // Solutions of size less or equal than n - k
    if (k < n) {
      ans = max_subarr_sum_le_s(axs, n - k);
    }

    // Solutions of size greater than n - k
    fore(i, 0, k) {
      fore(j, i + n - k, n + 1) {
        ll this_sum = as_sums[j] - as_sums[i];
        this_sum += (n - k) * (-x) - ((j - i) - (n - k)) * (-x);
        if (this_sum > ans) {
          ans = this_sum;
        }
      }
    }

  }
  return ans;
}

ll force(ull k, ll x, const vi& as) {
  ull n = as.size();
  ll ans = 0;

  fore(mask, 0, 1 << n) if (__builtin_popcountll(mask) == k) {
    vi this_as = as;
    fore(i, 0, n) {
      if (mask & (1ull << i)) {
        this_as[i] += x;
      } else {
        this_as[i] -= x;
      }
    }

    fore(i, 0, n) fore(j, i + 1, n + 1) {
      ll this_sum = 0;
      fore(l, i, j) {
        this_sum += this_as[l];
      }
      if (this_sum > ans) {
        ans = this_sum;
      }
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

#ifndef TEST
  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, k;
    ll x;
    cin >> n >> k >> x;
    vi as(n);
    for (ll& a : as) {
      cin >> a;
    }

    auto ans = solve(k, x, as);
    cout << ans << '\n';
  }
#else
  fore(_, 0, 10000) {
    ull n = rand() % 3 + 1;
    ull k = rand() % (min(n, 20ull));

    vi as(n);
    fore(i, 0, n) {
      as[i] = rand() % 10 - 5;
    }
    ll x = rand() % 10 - 5;

    ll ans = solve(k, x, as);
    ll ansf = force(k, x, as);
    if (ans != ansf) {
      cout << "ERROR\n";
      cout << "1\n";
      cout << n << ' ' << k << ' ' << x << '\n';
      for (ll a : as) {
        cout << a << ' ';
      }
      cout << '\n';
      cout << "ans: " << ans << '\n';
      cout << "ansf: " << ansf << '\n';
      return 0;
    }
  }
#endif
}
