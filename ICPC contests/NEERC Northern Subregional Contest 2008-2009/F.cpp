// https://codeforces.com/gym/100623

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef long long ll;
typedef vector<ll> vi;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)


vi solve(const vi& as) {
  ull n = as.size();
  vi ans = as;

  fore(i, 0, n - 1) {
    if (i % 2 == 0) {
      ans[i] = -(ans[i + 1] - as[i + 1]);
    }
    if ((i | (i + 1)) < n) {
      ans[i | (i + 1)] += ans[i] ;
    }
  }

  return ans;
}


int main(void) {
#ifdef ONLINE_JUDGE
  freopen("fenwick.in", "r", stdin);
  freopen("fenwick.out", "w", stdout);
#endif
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n;
  cin >> n;
  vi as(n);
  for(ll& a : as) {
    cin >> a;
  }

  vi ans = solve(as);
  for (ll a : ans) {
    cout << a << ' ';
  }
  cout << '\n';

  return EXIT_SUCCESS;
}
