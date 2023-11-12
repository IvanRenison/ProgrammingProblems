// https://codeforces.com/contest/1662/problem/I
#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((ull)x.size())
#define fore(i,a,b) for(ull i=a,gmat=b;i<gmat;++i)
#define pb push_back
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define mste(a,v) memset((a),(v),sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;

ull solve(vi ps, vi xs) {
  ull n = ps.size(), m = xs.size();

  vi ps_sums(n+1);
  fore(i, 0, n) {
    ps_sums[i+1] = ps_sums[i] + ps[i];
  }

  sort(ALL(xs));

  ull ans = 0;

  if (xs[0] > 0) {
    ans = ps_sums[min((ull)((xs[0]-1)/100+1), n)];
    //cerr << "first ans " << ans << endl;
  }

  fore(i, 0, m-1) {
    ull x0 = xs[i], x1 = xs[i+1];

    if (x0 >= (n-1)*100) {
      break;
    }

    fore(j, (x0)/100 + 1, min((x1-1)/100 + 1,n)) {
      ull s = j*100 + j*100 - x0; // Put the store just before s
      ull e = (s + x1 - 1)/2;

      ull is = j;
      ull ie = e / 100;
      ull this_ans = ps_sums[min(ie + 1, n)] - ps_sums[is];
      ans = max(ans, this_ans);
      //cerr << "i: " << i << " j: " << j << " this_ans: " << this_ans << endl;
      if (ie >= (x1-1)/100) {
        break;
      }
    }
  }

  if (xs[m-1] < (n-1)*100) {
    ull this_ans = ps_sums[n] - ps_sums[(xs[m-1])/100+1];
    ans = max(ans, this_ans);
    //cerr << "last this_ans: " << this_ans << endl;
  }

  return ans;
}

int main(){FIN;


  ull n, m;
  cin >> n >> m;

  vi ps(n), xs(m);
  for(ll& p : ps) {
    cin >> p;
  }
  for(ll& x : xs) {
    cin >> x;
  }

  cout << solve(ps, xs) << '\n';

	return 0;
}