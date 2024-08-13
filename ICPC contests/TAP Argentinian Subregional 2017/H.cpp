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

ll solve(vi& Xs) {
  ll N = Xs.size();
  if (Xs == vi(N, 0)) {
    return 0;
  }

  vi Ys;
  fore(i, 0, N) {
    if (i == 0 || Xs[i] != Xs[i-1]) {
      Ys.push_back(Xs[i]);
    }
  }

  if (Ys.size() == 1) {
    return 1;
  }

  ll K = Ys.size();

  ll ans = (Ys[0] > Ys[1]) + (Ys[K-1] > Ys[K-2]);
  fore(i, 1, K-1) {
    ans += Ys[i-1] < Ys[i] && Ys[i] > Ys[i+1];
  }

  return ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll N;
  cin >> N;
  vi Xs(N);
  for (ll& X : Xs) {
    cin >> X;
  }

  cout << solve(Xs) << '\n';

}