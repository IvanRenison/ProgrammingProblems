#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(), x.end()
#define RALL(x) x.end(), x.begin()
#define fore(i,a,b) for(int i=a,gmat=b;i<gmat;++i)
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define SZ(x) ((int)x.size())
#define mset(a,v) memset((a), (v), sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
const ll MOD = 1e9+7;

ll add(ll x, ll y){
  return (x+y)%MOD;
}

struct Tree {
  typedef ull T;
  static constexpr T unit = 0;
  vector<T> s; int n;
  T f(T a, T b) {return add(a,b);}
  Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
  void update(int pos, T val) {
    for (s[pos += n] = val; pos /= 2;)
      s[pos] = f(s[pos*2], s[pos*2+1]);
  }
  T query(int b, int e) {
    T ra = unit, rb = unit;
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if (b % 2) ra = f(ra, s[b++]);
      if (e % 2) rb = f(s[--e], rb);
    }
    return f(ra, rb);
  }
};

int main(){FIN;
  ll k, lo, n;cin>>k>>lo;
  vector<vector<ll>> mat(k);
  fore(i,0,k){
    mat[i].resize(k);
    fore(j,0,k){
      cin>>mat[i][j];
    }
  }
  cin>>n;
  vector<ll> ps(n-1);
  fore(i,0,n-1)cin>>ps[i];
  vector<Tree> sts(n);
  fore(i,0,n){
    sts[i] = Tree(k);
  }
  fore(i,0,k){
    sts[n-1].update(i,1);
  }

  for(int i = n-2; i>=0; --i){
    fore(j,0,k){
      ll l = lower_bound(ALL(mat[j]),ps[i]-lo)-mat[j].begin();
      // if(mat[j][l]>ps[i]+lo){
      //   sts[i].update(j,0);
      //   continue;
      // }
      ll r = upper_bound(ALL(mat[j]),ps[i]+lo)-mat[j].begin();
      // cout << j << " " << l << " " << r << " " << ps[i] << "\n";
      sts[i].update(j,sts[i+1].query(l,r));
    }
  }
  // fore(j,0,n){
  //   fore(i,0,k) cout << sts[j].query(i,i+1) << " ";
  // cout << "\n";
  // }
  cout << sts[0].query(0,k) << "\n";
  return 0;
}