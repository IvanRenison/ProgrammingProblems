// https://codeforces.com/contest/1832/problem/D1

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define fore(i, a, b) for (ll i = a; i < b; i++)

/*
Ver que solo vale la pena una suma y el resto restan 1, (porque combine sumar y inmieditamente restar)

Pero uno puede ver a cual le van a sumar en otro orden

En particular primero sumar k, k-1, k - n(n-1) y después hacer las restas de 1
*/

/* as has to be sorted and will be modified */
ll solve1(vector<ll> as, ll k) {
  ll n = as.size();

  ll sum = 0;
  ll min_a = LLONG_MAX;
  ll amount_with_add = k <= n ? k : n - (k - n) % 2;
  fore(i, 0, amount_with_add) {
    as[i] += k;
    k--;
    min_a = min(min_a, as[i]);
    sum += as[i];
  }
  fore(i, amount_with_add, n) {
    min_a = min(min_a, as[i]);
    sum += as[i];
  }

  ll extras = sum - min_a * n;

  if (k <= 2 * extras) {
    return min_a;
  }

  k -= 2 * extras;
  sum -= extras;

  return min_a - (k / 2 + n - 1) / n;
}

vector<ll> solve(vector<ll> as, vector<ll> ks) {
  ll n = as.size();
  ll q = ks.size();

  sort(as.begin(), as.end());

  vector<ll> ans(q);

  fore(i, 0, q) {
    vector<ll> as_copy(n);
    fore(j, 0, n) {
      as_copy[j] = as[j];
    }

    ll k = ks[i];
    ll m = solve1(as_copy, k);

    ans[i] = m;
  }

  return ans;
}

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

  vector<ll> ans = solve(as, ks);

  fore(i, 0, q) {
    cout << ans[i] << ' ';
  }

  cout << '\n';

  return EXIT_SUCCESS;
}
