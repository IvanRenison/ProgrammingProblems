// https://codeforces.com/group/5GNF7zti59/contest/534927/problem/L
#include<bits/stdc++.h>
#define fst first
#define snd second
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i =a,gmat=b;i<gmat;++i)
#define pb push_back
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef long double ld;
typedef vector<ld> vd;

optional<vector<pair<vi, vi>>> solve(ll N, ll X) {
  if (X >= N) {
    return {};
  }
  vi prims(X*N);
  fore(i, 0, N) {
    fore(j, 0, X) {
      prims[i*X+j]=i;
    }
  }
  vi secs(X*N);
  fore(i, 0, N) {
    ll e = 0;
    fore(j, 0, X) {
      secs[i*X+j] = (i + j + 1) % N;
    }
  }
  vector<pair<vi, vi>> ans(N);
  fore(i, 0, N*X) {
    ans[prims[i]].first.push_back(i);
    ans[secs[i]].second.push_back(i);
  }
  return ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll N, X;
  cin >> N >> X;
  auto ans = solve(N, X);
  if (!ans) {
    cout << "-1\n";
  } else {
    for (auto& [Ps, Ss] : *ans) {
      for (ll P : Ps) {
        cout << P + 1 << ' ';
      }
      for (ll S : Ss) {
        cout << S + 1 << ' ';
      }
      cout << '\n';
    }
  }
}
