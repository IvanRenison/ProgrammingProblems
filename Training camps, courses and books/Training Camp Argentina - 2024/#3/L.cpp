// https://codeforces.com/group/5GNF7zti59/contest/535420/problem/L
#include <bits/stdc++.h>
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;

const ll alim = 3e5 + 1;

vi some_prime(alim);

void init() {
  iota(ALL(some_prime), 0);
  for (ll i = 4; i < alim; i += 2) {
    some_prime[i] = 2;
  }
  for (ll i = 3; i < alim; i += 2) {
    if (some_prime[i] == i) {
      for (ll j = i; j < alim; j += i) {
        some_prime[j] = i;
      }
    }
  }
}

vi compress(const vi& as) {
  set<ll> as_set;
  for (ll a : as) {
    vi ps;
    while (a > 1) {
      ll p = some_prime[a];
      ps.push_back(p);
      while (a % p == 0) {
        a /= p;
      }
    }
    for (ll p : ps) {
      a *= p;
    }
    as_set.insert(a);
  }

  vector<bool> valid(alim, true);

  vi ans;
  for (ll a : as_set) {
    if (valid[a]) {
      for (ll b = a + a; b < alim; b += a) {
        valid[b] = false;
      }
      ans.push_back(a);
    }
  }
  return ans;
}

ll comb(ll x, ll y) {
  if (y > x) {
    return 0;
  }

  y = min(y, x - y);
  ll z = x - y;

  ll ans = 1;
  fore(a, z + 1, x + 1) {
    ans *= a;
  }
  fore(a, 1, y + 1) {
    ans /= a;
  }

  return ans;
}

ll solve(vi& as) {
  {
    ll g = 0;
    for (ll a : as) {
      g = gcd(g, a);
    }
    if (g != 1) {
      return -1;
    }
  }

  as = compress(as);
  vector<bool> apps(alim, false);
  for (ll a : as) {
    apps[a] = true;
  }

  for(ll i = 1;; i++) {
    // dp[a] = Cantidad de formas de obtener gcd a con i elementos
    vi dp(alim);
    for (ll a = alim - 1; a > 0; a--) {
      ll count = 0;
      for (ll b = a; b < alim; b += a) {
        count += apps[b];
      }

      dp[a] = comb(count, i);
      for (ll b = 2 * a; b < alim; b += a) {
        dp[a] -= dp[b];
      }
    }

    if (dp[1] > 0) {
      return i;
    }
  }
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  init();

  ll n;
  cin >> n;
  vi as(n);
  for (ll& a : as) {
    cin >> a;
  }

  ll ans = solve(as);
  cout << ans << '\n';
}
