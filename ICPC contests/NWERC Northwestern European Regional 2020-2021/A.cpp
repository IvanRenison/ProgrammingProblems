// https://codeforces.com/gym/103049/problem/A
#include <bits/stdc++.h>
#define fore(i,a,b) for(int i=a,gmat=b;i<gmat;++i)
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((int)x.size())
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;

vi dp(100*100 + 5, -1);
ll force(const vi& as, ll k) {
  if (dp[k-1] != -1) {
    return dp[k-1];
  }
  ll n = as.size();
  if (k <= n) {
    dp [k-1] = as[k-1];
    return as[k-1];
  }

  ll ans = 1ll << 60;

  fore(i, 0, n) {
    ll this_ans = as[i] + force(as, k - i - 1);
    ans = min(ans, this_ans);
  }

  dp[k-1] = ans;
  return ans;
}


vi solve(const vi& as, const vi& ks) {
  ll n = as.size(), q = ks.size();

  ll best_i = 0;
  fore(i, 1, n) {
    if (as[i]*(best_i+1) < as[best_i]*(i+1)) {
      best_i = i;
    }
  }

  ll best_in_n = n/(best_i+1);

  vi ans(q);
  fore(j, 0, q) {
    ll k = ks[j];
    if (k <= n) {
      ans[j] = force(as, k);
    } else {
      ll k_copy = k % (best_i+1) + best_in_n * (best_i+1);
      ans[j] = (k / (best_i+1) - best_in_n) * as[best_i];

      if (k_copy < n) {
        k_copy += (best_i+1);
        ans[j] -= as[best_i];
      }

      ll maybe_ans = force(as, k_copy);
      ll less_acum = 0;
      while (k_copy + (best_i+1) <= min(k, n*n)) {
        k_copy += (best_i+1);
        less_acum += as[best_i];
        ll this_ans = force(as, k_copy);
        maybe_ans = min(maybe_ans, this_ans - less_acum);
      }
      ans[j] += maybe_ans;
    }
  }

  return ans;
}

int main(){FIN;

  ll n, q;
  cin >> n >> q;
  vi as(n), ks(q);
  for(ll& a : as) {
    cin >> a;
  }
  for(ll& k : ks) {
    cin >> k;
  }

  vi ans = solve(as, ks);
  for(ll a : ans) {
    cout << a << '\n';
  }

	return 0;
}