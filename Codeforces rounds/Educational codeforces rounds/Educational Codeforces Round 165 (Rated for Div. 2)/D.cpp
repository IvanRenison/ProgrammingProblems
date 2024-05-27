// https://codeforces.com/contest/1969/problem/D

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

ull force(ull k, const vu& as, const vu& bs) {
  ull n = as.size();

  ull ans = 0;
  fore(x, 0, 1 << n) {
    ull alice = 0;
    vu bs_;
    fore(i, 0, n) {
      if (x & (1 << i)) {
        alice += as[i];
        bs_.push_back(bs[i]);
      }
    }

    sort(ALL(bs_));
    reverse(ALL(bs_));

    ull bob = 0;
    fore(i, k, bs_.size()) {
      bob += bs_[i];
    }

    if (bob > alice) {
      ans = max(ans, bob - alice);
    }
  }

  return ans;
}

template <typename T>
using rpriority_queue = priority_queue<T, vector<T>, greater<T>>;

ull solve(ull k, const vu& as, const vu& bs) {
  ull n = as.size();

  vuu pos;
  fore(i, 0, n) {
    ull a = as[i], b = bs[i];
    if (a <= b) {
      pos.push_back({a, b});
    }
  }

  ull m = pos.size();

  if (m <= k) {
    return 0;
  }

  sort(ALL(pos), [](const uu& x, const uu& y) {
    return x.first < y.first || (x.first == y.first && x.second > y.second);
  });

  rpriority_queue<ull> free_bob;

  ull alice = 0;
  fore(i, 0, k) {
    alice += pos[i].first;
    free_bob.push(pos[i].second);
  }

  ull ans = 0;

  ull bob = 0;
  fore(i, k, m) {
    auto [a, b] = pos[i];
    alice += a;

    free_bob.push(b);

    ull t = free_bob.top();
    free_bob.pop();

    bob += t;

    if (bob > alice) {
      ans = max(ans, bob - alice);
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
    ull n, k;
    cin >> n >> k;
    vu as(n), bs(n);
    fore(j, 0, n) {
      cin >> as[j];
    }
    fore(j, 0, n) {
      cin >> bs[j];
    }

    auto ans = solve(k, as, bs);
    cout << ans << '\n';
  }

/*   fore(_, 0, 10000) {
    ull n = rand() % 10 + 1;
    ull k = rand() % n;

    vu as(n), bs(n);
    fore(i, 0, n) {
      as[i] = rand() % 10 + 1;
      bs[i] = rand() % 10 + 1;
    }

    auto ans1 = solve(k, as, bs);
    auto ans2 = force(k, as, bs);
    if (ans1 != ans2) {
      cerr << "Mismatch: " << ans1 << " " << ans2 << '\n';
      cerr << n << " " << k << '\n';
      fore(i, 0, n) {
        cerr << as[i] << " ";
      }
      cerr << '\n';
      fore(i, 0, n) {
        cerr << bs[i] << " ";
      }
      cerr << '\n';
      return EXIT_FAILURE;
    }
  } */

  return EXIT_SUCCESS;
}
