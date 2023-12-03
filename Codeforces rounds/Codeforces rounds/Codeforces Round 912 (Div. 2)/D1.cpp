// https://codeforces.com/contest/1903/D1

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef vector<ull> vu;
typedef vector<ll> vi;
typedef pair<ull, ull> uu;
typedef pair<ll, ll> ii;
typedef vector<uu> vuu;
typedef vector<ii> vii;
typedef tuple<ull, ull, ull> uuu;
typedef tuple<ll, ll, ll> iii;
typedef vector<uuu> vuuu;
typedef vector<iii> viii;
typedef tuple<ull, ull, ull, ull> uuuu;
typedef tuple<ll, ll, ll, ll> iiii;
typedef vector<uuuu> vuuuu;
typedef vector<iiii> viiii;
typedef tuple<ull, ull, ull, ull, ull> uuuuu;
typedef tuple<ll, ll, ll, ll, ll> iiiii;
typedef vector<uuuuu> vuuuuu;
typedef vector<iiiii> viiiii;
typedef long double ld;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()
#define DBG(x) cerr << #x << " = " << x << endl

const ull nbits = 61;
const ull inf = 1ull << 63;

vu solve(const vu& as, const vu& ks) {
  ull n = as.size(), q = ks.size();

  ull a_max = inf - 1;
  fore(i, 0, n) {
    a_max &= as[i];
  }

  vu cnt(nbits, inf);
  fore(x, 0, nbits) {
    if ((a_max & (1ull << x)) == 0) {
      cnt[x] = 0;
      fore(i, 0, n) {
        if (as[i] & (1ull << x)) {
          continue;
        }
        ull this_cnt = (1ull << x) - (as[i] & ((1ull << x) - 1));
        cnt[x] += this_cnt;
      }
    }
  }

  vu ans(q);
  fore(i, 0, q) {
    ull k = ks[i];


    ull max_x = inf;
    fore(x, 0, nbits) {
      if (cnt[x] != inf && cnt[x] <= k) {
        max_x = x;
      }
    }

    if (max_x == inf) {
      ans[i] = a_max;
      continue;
    }

    ull this_ans = 0;
    fore(x, max_x + 1, nbits) {
      this_ans |= ((1ull << x) & a_max);
    }
    this_ans |= (1ull << max_x);
    vu as_ = as;
    fore(j, 0, n) {
      if ((as_[j] & (1ull << max_x)) == 0) {
        as_[j] &= !((1ull << max_x) - 1);
        as_[j] |= (1ull << max_x);
      }
    }
    k -= cnt[max_x];
    for(; max_x < nbits; max_x--) {
      ull cost = 0;
      fore(j, 0, n) {
        if (as_[j] & (1ull << max_x)) {
          continue;
        }
        ull this_cnt = (1ull << max_x) - (as_[j] & ((1ull << max_x) - 1));
        cost += this_cnt;
      }

      if (cost <= k) {
        this_ans |= (1ull << max_x);
        fore(j, 0, n) {
          if ((as_[j] & (1ull << max_x)) == 0) {
            as_[j] &= !((1ull << max_x) - 1);
            as_[j] |= (1ull << max_x);
          }
        }
        k -= cost;
      }
    }

    ans[i] = this_ans;
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n, q;
  cin >> n >> q;
  vu as(n);
  fore(i, 0, n) {
    cin >> as[i];
  }
  vu ks(q);
  fore(i, 0, q) {
    cin >> ks[i];
  }

  vu ans = solve(as, ks);
  fore(i, 0, q) {
    cout << ans[i] << '\n';
  }

  return EXIT_SUCCESS;
}
