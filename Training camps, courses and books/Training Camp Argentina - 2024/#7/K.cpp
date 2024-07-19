// https://codeforces.com/group/5GNF7zti59/contest/534927/problem/K
#include<bits/stdc++.h>
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i =a,gmat=b;i<gmat;++i)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;

bool puedoGanar(ll s, ll e) {
  if (e % 2 == 1) {
    return s % 2 == 0;
  } else {
    if (s > e / 2) {
      return s % 2 == 1;
    } else if (s > e / 4) {
      return true;
    } else {
      return puedoGanar(s, e / 4);
    }
  }
}

bool puedoGanarForce(ll s, ll e) {
  if (s + 1 > e && 2 * s > e) {
    return false;
  }
  if (s + 1 <= e && !puedoGanarForce(s + 1, e)) {
    return true;
  }
  if (s * 2<= e && !puedoGanarForce(s * 2, e)) {
    return true;
  }

  return false;
}

bool puedoPerder(ll s, ll e) {
  if (s > e / 2) {
    return true;
  } else {
    return puedoGanar(s, e / 2);
  }
}

bool puedoPerderForce(ll s, ll e) {
   if (s + 1 > e || 2 * s > e) {
    return true;
  }
  if (s + 1 <= e && !puedoPerderForce(s + 1, e)) {
    return true;
  }
  if (s * 2 <= e && !puedoPerderForce(s * 2, e)) {
    return true;
  }

  return false;
}

pair<bool, bool> solve(const vii& se) {
  ll n = se.size();

  vector dp(n, vector<bool>(2, false));
  // dp[i][true] = puedo ganar si empiezo en la i
  // dp[i][false] = puedo perder si empiezo en la i
  vector dp2(n, vector<bool>(2, false));
  // dp[i][true] = puedo ganar si voy segundo en la i
  // dp[i][false] = puedo perder si voy segundo en la i

  dp[n - 1][false] = puedoPerder(se[n - 1].first, se[n - 1].second);
  dp[n - 1][true] = puedoGanar(se[n - 1].first, se[n - 1].second);
  dp2[n - 1][false] = !dp[n - 1][false];
  dp2[n - 1][true] = !dp[n - 1][true];

  for (ll i = n - 1; i--; ) {
    auto [s, e] = se[i];
    bool gan = puedoGanar(s, e);
    bool per = puedoPerder(s, e);
    if (gan && per) {
      dp[i][true] = dp[i][false] = true;
    } else if (gan) {
      dp[i][true] = !dp[i + 1][true];
      dp[i][false] = !dp[i + 1][false];
    } else if (per) {
      dp[i][true] = dp[i + 1][true];
      dp[i][false] = dp[i + 1][false];
    } else {
      dp[i][true] = dp[i][false] = false;
    }
  }

  return {dp[0][true], dp[0][false]};
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll t;
  cin >> t;
  vii se(t);
  for (auto& [s, e] : se) {
    cin >> s >> e;
  }

  auto [w, l] = solve(se);
  cout << w << ' ' << l << '\n';

/*   fore(e, 1, 100) fore(s, 1, e + 1) {
    bool w = puedoPerder(s, e);
    bool wf = puedoPerderForce(s, e);
    //cout << s << ' ' << e << ' ' << w << ' ' << wf << '\n';
    if (w != wf) {
      cout << s << ' ' << e << ' ' << w << ' ' << wf << '\n';
      //return 1;
    }
  } */

}