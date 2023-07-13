// https://codeforces.com/contest/1832/problem/D2

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define fore(i, a, b) for (ll i = a; i < b; i++)

class Problem {
public:
  // Sorted vector of original elements
  vector<ll> as;
  ll n;

  // For k > n && (n - k) % 2 == 0
  vector<ll> big_pair_as;
  ll big_pair_sum;
  ll big_pair_min;

  // For k > n && (n - k) % 2 == 1
  vector<ll> big_odd_as;
  ll big_odd_sum;
  ll big_odd_min;

  // For k =< n
  vector<ll> small_anss;

  Problem(vector<ll> as) {
    n = as.size();
    sort(as.begin(), as.end());
    this->as = as;

    { // Initialization for k > n && (n - k) % 2 == 0
      big_pair_as = vector<ll>(n);
      fore(i, 0, n) {
        big_pair_as[i] = as[i];
      }
      big_pair_sum = 0;
      big_pair_min = LLONG_MAX;

      ll k = n;
      fore(i, 0, n) {
        big_pair_as[i] += k;
        k--;
        big_pair_min = min(big_pair_min, big_pair_as[i]);
        big_pair_sum += big_pair_as[i];
      }
    }

    { // Initialization for k > n && (n - k) % 2 == 1
      big_odd_as = vector<ll>(n);
      fore(i, 0, n) {
        big_odd_as[i] = as[i];
      }
      big_odd_sum = 0;
      big_odd_min = LLONG_MAX;

      ll k = n - 1;
      fore(i, 0, n - 1) {
        big_odd_as[i] += k;
        k--;
        big_odd_min = min(big_odd_min, big_odd_as[i]);
        big_odd_sum += big_odd_as[i];
      }
    }

    { // Initialization for k <= n
      small_anss = vector<ll>(n + 1);

      small_anss[0] = as[0];
      fore(k, 1, n) {
        small_anss[k] = min(small_anss[k - 1] + 1, as[k]);
      }
      small_anss[n] = small_anss[n - 1] + 1;
    }
  }

  ll query(ll k) const {
    if (k <= n) {
      return small_anss[k];
    } else if ((k - n) % 2 == 0) {
      ll sum = big_pair_sum + (k - n) * n;
      ll _min = big_pair_min + k - n;

      k -= n;

      ll extras = sum - n * _min;

      if (k <= extras * 2) {
        return _min;
      }

      k -= extras * 2;

      return _min - (k / 2 + n - 1) / n;
    } else {
      ll sum = big_odd_sum + (k - n + 1) * (n - 1) + as[n - 1];
      ll _min = big_odd_min == LLONG_MAX
                    ? as[n - 1]
                    : min(big_odd_min + k - n + 1, as[n - 1]);

      k -= (n - 1);

      ll extras = sum - n * _min;

      if (k <= extras * 2) {
        return _min;
      }

      k -= extras * 2;
      return _min - (k / 2 + n - 1) / n;
    }
  }
};

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ll n, q;
  cin >> n >> q;

  vector<ll> as(n);
  fore(i, 0, n) {
    cin >> as[i];
  }

  vector<ll> ks(q);
  fore(i, 0, q) {
    cin >> ks[i];
  }

  Problem p(as);

  fore(i, 0, q) {
    cout << p.query(ks[i]) << ' ';
  }

  cout << '\n';

  return EXIT_SUCCESS;
}
