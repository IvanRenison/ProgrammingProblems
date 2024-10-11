// https://codeforces.com/gym/101630
#include <bits/stdc++.h>
#define ALL(x) x.begin(), x.end()
#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; ++i)
#define SZ(x) (ll(x.size()))
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;

const ll n_lim = 10001;
typedef bitset<n_lim / 2 + 1> B;

/* vi as(10000);
vi aos, aes;
ll LT_count = 0; */

bool LT(ll i, ll j) { // os[i] < es[j]

  static vector<B> mem(n_lim / 2);
  static vector<B> used(n_lim / 2);

  if (used[i][j]) {
    return mem[i][j];
  }
  used[i][j] = true;
  //LT_count++;
  //return mem[i][j] = aos[i] < aes[j];

  cout << "? " << i + 1 << ' ' << j + 1 << endl;
  char c;
  cin >> c;
  return mem[i][j] = c == '<';
}

pair<vi, vi> solve(ll n) {

  vii os_ranges(n / 2, {0, n}), es_ranges((n + 1) / 2, {0, n});

  for (ll i = 0, j = 0; j < (n + 1) / 2; i++, j++) {
    if (i < n / 2) {
      auto [l, e] = os_ranges[i];
      ll count = 0;
      fore(k, 0, (n + 1) / 2) {
        auto [lk, ek] = es_ranges[k];
        if (ek <= l) {
          count++;
        } else if (lk < e) {
          count += !LT(i, k);
        }
      }
      ll val = 2 * count - 1;
      os_ranges[i] = {val, val};
      fore(k, 0, (n + 1) / 2) {
        auto& [lk, ek] = es_ranges[k];

        if (lk <= val && val < ek) {
          bool lt = LT(i, k);
          if (lt) {
            lk = val + 1;
          } else {
            ek = val;
          }
        }
      }
    }
    {
      auto [l, e] = es_ranges[j];
      ll count = 0;
      fore(k, 0, n / 2) {
        auto [lk, ek] = os_ranges[k];
        if (ek <= l) {
          count++;
        } else if (lk < e) {
          count += LT(k, j);
        }
      }
      ll val = 2 * count;
      es_ranges[j] = {val, val + 1};
      fore(k, 0, n / 2) {
        auto& [lk, ek] = os_ranges[k];
        if (lk <= val && val < ek) {
          bool lt = LT(k, j);
          if (lt) {
            ek = val;
          } else {
            lk = val + 1;
          }
        }
      }
    }
  }

  vi os(n / 2, -1), es((n + 1) / 2, -1);
  fore(i, 0, n / 2) {
    os[i] = os_ranges[i].first;
  }
  fore(j, 0, (n + 1) / 2) {
    es[j] = es_ranges[j].first;
  }

  return {os, es};
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);

/*   iota(ALL(as), 0);
  random_shuffle(ALL(as));
  for (ll a : as) {
    if (a % 2 == 0) {
      aes.push_back(a);
    } else {
      aos.push_back(a);
    }
  } */

  ll n;
  cin >> n;
  auto [os, es] = solve(n);
  cout << '!';
  for (ll o : os) {
    cout << ' ' << o + 1;
  }
  for (ll e : es) {
    cout << ' ' << e + 1;
  }
  cout << endl;

  //cerr << LT_count << '\n';
}
