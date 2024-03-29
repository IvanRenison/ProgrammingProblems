// https://codeforces.com/gym/105053/problem/K
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

const ll inf = 1ll << 60;

bool is_vowel(char c){
    string S = "AEIOUY";
    fore(i,0,6){
        if(c==S[i])return true;
    }
    return false;
}

ll solve(const vi& vals) {
  ll N = vals.size();

  vector<vi> dp(N + 1, vi(3, inf));

  dp[0][0] = dp[0][1] = dp[0][2] = 0;

  fore(i, 0, N) {
    ll x = vals[i];
    dp[i + 1][2] = dp[i][1] + 1;
    dp[i + 1][1] = dp[i][0] + 1;
    fore(j, 0, 3) {
      if (x & (1 << j)) {
        fore(k, 0, 3) {
          dp[i + 1][k] = min(dp[i + 1][k], dp[i][2 - j] + j + 1);
        }
        break;
      }
    }
  }

  ll ans = min(dp[N][2], min(dp[N][1], dp[N][0]));

  return ans;
}


int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll N;
  cin >> N;
  vi vals(N);
  for (ll& x : vals) {
    string s;
    cin >> s;
    fore(i, 0, min(3ll, (ll)s.size())) {
      if (is_vowel(s[i])) {
        x |= 1 << i;
      }
    }
  }

  ll ans = solve(vals);

  if (ans < inf) {
    cout << ans << '\n';
  } else {
    cout << "*\n";
  }

}