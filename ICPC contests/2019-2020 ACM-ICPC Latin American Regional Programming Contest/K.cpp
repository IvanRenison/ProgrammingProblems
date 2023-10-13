#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define fore(i,a,b) for(int i=a,gmat=b;i<gmat;i++)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(),x.end()
#define mset(a,v) memset((a),(v),sizeof(a))
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;

struct poly {
  vi c;
  poly(vi c) : c(c) {}
  poly(ll k) : c(k) {}
  poly operator*(ll x) {
    poly res(c.size());
    fore(i,0,c.size()) {
      res.c[i]=c[i]*x;
    }
    return res;
  }
  poly operator*(poly o) {
    ll m = c.size(), n = o.c.size();
    poly res(m+n-1);
    fore(i, 0, m) fore(j, 0, n) res.c[i+j]=res.c[i+j]+c[i]*o.c[j];
    return res;
  }
};

poly cons(const vi& roots, ull i, ull j) {
  if (i == j) {
    vi v(1,1);
    return poly(v);
  }
  if (i + 1 == j) {
    return poly({-roots[i], 1});
  } else {
    ull m = (i+j)/2;
    poly ans1 = cons(roots, i, m), ans2 = cons(roots, m, j);
    return ans1 * ans2;
  }
}

vi solve(vector<bool> Hs) {
  ull N = Hs.size();

  vi roots;
  fore(i, 1, N) {
    if (Hs[i] != Hs[i-1]) {
      roots.push_back(2*i+1);
    }
  }

  poly ans = cons(roots, 0, roots.size());
  if (!Hs[N-1]) {
    ans = ans*(-1);
  }

  return ans.c;
}

int main(){FIN;
  string s;
  cin >> s;
  ull N = s.size();
  vector<bool> Hs(N);
  fore(i, 0, N) {
    Hs[i] = s[i] == 'H';
  }

  vi ans = solve(Hs);

  cout << ans.size() - 1 << '\n';
  fore(i, 0, ans.size()) {
    cout << ans[ans.size() - 1 - i] << ' ';
  }
  cout << '\n';

  return 0;
}