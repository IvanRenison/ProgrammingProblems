// https://codeforces.com/contest/1250/problem/B
#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(x) x.begin(),x.end()
#define SZ(x) (ll(x.size()))
#define fore(i,a,b) for(ll i=a, gmat=b;i<gmat;++i)
#define pb push_back
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;

ll solve(ll k, const vi& ts) {
  ll n = ts.size();

  vi cnts(k);
  for (ll t : ts) {
    cnts[t]++;
  }

  sort(ALL(cnts));

  ll ans = cnts.back() * k; // k rides

  if (k % 2 == 0) { // k/2 rides
    ll this_ans = 0;
    fore(i, 0, k/2) {
      this_ans = max(this_ans, cnts[i] + cnts[k - 1 - i]);
    }
    this_ans *= (k/2);

    ans = min(ans, this_ans);
  }

  fore(r, k/2 + 1, k) {
    ll this_ans = cnts.back();

    ll two = k - r;
    fore(i, 0, two) {
      this_ans = max(this_ans, cnts[i] + cnts[2 * two - 1 - i]);
    }

    this_ans *= r;

    ans = min(this_ans, ans);
  }

  return ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);

  ll n, k;
  cin >> n >> k;

  vi ts(n);
  for (ll& t : ts) {
    cin >> t;
    t--;
  }

  cout << solve(k, ts) << '\n';

  return 0;
}