// https://codeforces.com/contest/1798/problem/C

#include <bits/stdc++.h>

using namespace std;

typedef __int128 ll;
#define fore(i, a, b) for (ll i = a; i < b; i++)

vector<pair<ll, ll>> parse1(void) {
  ll n;
  long long n_;
  cin >> n_;
  n = (ll)n_;

  vector<pair<ll, ll>> abs(n);

  fore(i, 0, n) {
    long long a, b;
    cin >> a >> b;
    abs[i] = {(ll)a, (ll)b};
  }

  return abs;
}

ll solve1(vector<pair<ll, ll>> abs) {
  ll n = abs.size();

  ll ans = 1;

  ll diva = abs[0].first;
  ll mulb = abs[0].second;
  ll divt = abs[0].first * abs[0].second;

  fore(i, 1, n) {
    ll a = abs[i].first;
    ll b = abs[i].second;
    ll t = a*b;

    diva = __gcd(diva, a);
    divt = __gcd(divt, t);
    mulb = mulb * b / __gcd(mulb, abs[i].second);

    if (divt % mulb != 0 || diva % (divt/mulb) != 0) {
      ans++;
      diva = a;
      divt = t;
      mulb = b;
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  long long t;

  cin >> t;

  fore(i, 0, t) {
    cout << (long long)solve1(parse1()) << endl;
  }

  return EXIT_SUCCESS;
}
