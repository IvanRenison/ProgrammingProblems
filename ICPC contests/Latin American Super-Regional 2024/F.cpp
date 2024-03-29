// https://codeforces.com/gym/105053/problem/F
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define SZ(x) (ll(x.size()))
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;

const ll lim = 2e5 + 1;

bool old(const vii& GRs) {
  ll N = GRs.size();

  if (N == 1) {
    return false;
  }

  ll g = GRs[0].second;
  ll sum = GRs[0].first;
  ll has0 = sum == 0;
  fore(i, 1, N) {
    g = gcd(g, GRs[i].second);
    sum += GRs[i].first;
    has0 = has0 || GRs[i].first == 0;
  }

  bitset<lim> dp;
  dp[0] = true;

  for (auto [G, _] : GRs) {
    dp |= dp << G;
  }

  fore(i, has0 ? 0 : 1, has0 ? sum + 1 : sum) {
    if (dp[i]) {
      if (abs(i - (sum - i)) % g == 0) {
        return true;
      }
    }
  }

  return false;
}

ll exp_(ll x, ll n) {
  if(!n) {
    return 1;
  }
  ll ans = exp_(x, n/2);
  ans *= ans;
  if (n&1) {
    ans *= x;
  }
  return ans;
}

bool solve(const vii& GRs) {
  ll N = GRs.size();

  if (N == 1) {
    return false;
  }

  ll g = GRs[0].second;
  ll sum = GRs[0].first;
  ll has0 = sum == 0;
  map<ll, ll> vals = {{GRs[0].first, 1}};
  fore(i, 1, N) {
    g = gcd(g, GRs[i].second);
    sum += GRs[i].first;
    has0 = has0 || GRs[i].first == 0;
    vals[GRs[i].first]++;
  }

  bitset<lim> dp;
  dp[0] = true;

  for (auto [G, e] : vals) {
    ll x = G;
    for (ll i = 1; i < e && x < lim; i *= 2) {
      dp |= dp << x;
      x *= 2;
    }

    if (x < lim) {
      dp |= dp << exp_(G, e);
    }
  }

  fore(i, has0 ? 0 : 1, has0 ? sum + 1 : sum) {
    if (dp[i]) {
      if (abs(i - (sum - i)) % g == 0) {
        return true;
      }
    }
  }

  return false;
}

int main(){
    ios::sync_with_stdio(0),cin.tie(0);

  ll N;
  cin >> N;

  vii GRs(N);
  for (auto& [G, R] : GRs) {
    cin >> G >> R;
  }

  if (solve(GRs)) {
    cout << "Y\n";
  } else {
    cout << "N\n";
  }

/*   {
    ll N = 1e5;
    cout << N << '\n';
    fore(i, 0, N) {
      cout << 2 << ' ' << rand() % ((ll)1e9) << '\n';
    }
  } */

/*
  fore(_, 0, 1000) {
    ll N = rand() % 5 + 1;
    vii GRs(N);
    for (auto& [G, R] : GRs) {
      G = rand() % 10;
      R = 6 * (rand() % 3 + 1);
    }

    bool ans = solve(GRs);
    bool ans2 = old(GRs);
    if (ans != ans2) {
      cerr << N << '\n';
      for (auto [G, R] : GRs) {
        cerr << G << ' ' << R << '\n';
      }
      cerr << "ans: " << ans << " ans2: " << ans2 << endl;
      return 1;
    }
  } */

}

/*

4
6 6
5 18
5 12
2 6
ans: 0 ans2: 1

*/