// https://codeforces.com/group/5GNF7zti59/contest/534272/problem/D
#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef double ld;

template <typename T>
using rpriority_queue = priority_queue<T, vector<T>, greater<T>>;

const ld eps = 1e-9;

bool can(ll m, ll k, const vi& as, const vi& bs) {
  ll n = as.size();

  rpriority_queue<pair<ld, ll>> pq;

  fore(i, 0, n) {
    ll a = as[i], b = bs[i];
    ld t = (ld)a / (ld)b;

    pq.push({t, i});

  }

  fore(i, 0, k) {
    auto [t, j] = pq.top();
    pq.pop();
    if (t + eps < (ld)i) {
      return false;
    }
    t += (ld)m / (ld) bs[j];
    pq.push({t, j});
  }

  return true;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll n, k;
  cin >> n >> k;
  vi as(n), bs(n);
  for (ll& a : as) {
    cin >> a;
  }
  for (ll& b : bs) {
    cin >> b;
  }

  ll l = -1, r = 1e13;
  while (l + 1 < r) {
    ll m = (l + r) / 2;
    if (can(m, k, as, bs)) {
      r = m;
    } else {
      l = m;
    }
  }

  if (r == 1e13) {
    cout << "-1\n";
  } else {
    cout << r << '\n';
  }

}