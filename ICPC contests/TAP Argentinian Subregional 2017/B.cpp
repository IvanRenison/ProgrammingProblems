// https://codeforces.com/group/YjFmW2O15Q/contest/101811
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define SZ(x) ((ll)x.size())
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef tuple<ll,ll,ll> iii;
typedef vector<iii> viii;

const ll mod = 1e9 + 7;

ll solve(vi& Ps, vi& Cs) {
  ll N = Ps.size();

  sort(ALL(Ps));
  sort(ALL(Cs));

  vi count(N);
  fore(i, 0, N) {
    ll C = Cs[i];

    auto it = lower_bound(ALL(Ps), C);
    ll k = Ps.end() - it;

    count[i] = k;
  }

  ll ans = 1;
  for (ll i = N; i--;) {
    ll j = N - 1 - i;
    if (count[i] <= j) {
      return 0;
    } else {
      ans *= count[i] - j;
      ans %= mod;
    }
  }

  return ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll N;
  cin >> N;
  vi Ps(N), Cs(N);
  for (ll& P : Ps) {
    cin >> P;
  }
  for (ll& C : Cs) {
    cin >> C;
  }

  cout << solve(Cs, Ps) << '\n';

}