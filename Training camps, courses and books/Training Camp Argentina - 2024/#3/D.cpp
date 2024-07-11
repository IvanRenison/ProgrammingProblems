// https://codeforces.com/group/5GNF7zti59/contest/535420/problem/D
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

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll n, k; cin >> n >> k;

  if (k > n) {
    cout << "NO\n";
    return 0;
  }

  multiset<ll> p;
  fore(b, 0, 32) {
    if (n & (1 << b)) {
      p.insert(b);
    }
  }

  if (SZ(p) > k) {
    cout << "NO\n";
    return 0;
  }

  while(SZ(p) < k) {
    ll pi = *p.rbegin();
    assert(pi > 0);
    p.erase(p.find(pi));
    fore(_, 0, 2) p.insert(pi-1);
  }

  cout << "YES\n";
  for(auto b : p) {
    cout << (1 << b) << " ";
  }
  cout << "\n";
}