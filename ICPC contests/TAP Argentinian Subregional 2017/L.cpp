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
typedef vector<ii> vii;
typedef tuple<ll,ll,ll> iii;
typedef vector<iii> viii;

typedef array<ll, 4> Arr;

const vector<Arr> ops = {
  {0, 4, 0, 0},
  {4, 0, 0, 0},
  {0, 0, 0, 4},
  {1, 0, 1, 2},
  {2, 0, 2, 0},
  {2, 2, 0, 0}
};

ll greedy(const vi& perm, Arr vals) {
  ll ans = 0;
  for (ll i : perm) {
    ll cant = 1ll << 60;
    fore(j, 0, 4) {
      if (ops[i][j] > 0) {
        ll this_cant = vals[j] / ops[i][j];
        cant = min(cant, this_cant);
      }
    }
    ans += cant;
    fore(j, 0, 4) {
      vals[j] -= cant * ops[i][j];
    }
  }
  return ans;
}

ll solve(Arr LOST) {
  vi perm(6);
  iota(ALL(perm), 0);

  ll ans = 0;
  do {
    ll this_ans = greedy(perm, LOST);
    ans = max(ans, this_ans);
  } while (next_permutation(ALL(perm)));

  return ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  Arr LOST;
  for (ll& a : LOST) {
    cin >> a;
  }

  cout << solve(LOST) << '\n';

}