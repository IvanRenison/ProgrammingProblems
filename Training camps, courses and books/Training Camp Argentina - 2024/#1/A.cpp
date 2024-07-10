// https://codeforces.com/group/5GNF7zti59/contest/534272/problem/A

#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

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
typedef vector<ii> vii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;

/** Author: Johan Sannemo, pajenegod
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Description: Range Minimum Queries on an array. Returns
 * min(V[a], V[a + 1], ... V[b - 1]) in constant time.
 * Usage:
 *  RMQ rmq(values);
 *  rmq.query(inclusive, exclusive);
 * Time: O(|V| \log |V| + Q)$
 * Status: stress-tested
 */
template<class T>
struct RMinQ {
  vector<vector<T>> jmp;
  RMinQ(const vector<T>& V) : jmp(1, V) {
    for (ll pw = 1, k = 1; pw * 2 <= SZ(V); pw *= 2, ++k) {
      jmp.emplace_back(SZ(V) - pw * 2 + 1);
      fore(j,0,SZ(jmp[k]))
        jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
    }
  }
  T query(ll a, ll b) {
    assert(a < b); // or return inf if a == b
    ll dep = 63 - __builtin_clzll(b - a);
    return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
  }
};

template<class T>
struct RMaxQ {
  vector<vector<T>> jmp;
  RMaxQ(const vector<T>& V) : jmp(1, V) {
    for (ll pw = 1, k = 1; pw * 2 <= SZ(V); pw *= 2, ++k) {
      jmp.emplace_back(SZ(V) - pw * 2 + 1);
      fore(j,0,SZ(jmp[k]))
        jmp[k][j] = max(jmp[k - 1][j], jmp[k - 1][j + pw]);
    }
  }
  T query(ll a, ll b) {
    assert(a < b); // or return inf if a == b
    ll dep = 63 - __builtin_clzll(b - a);
    return max(jmp[dep][a], jmp[dep][b - (1 << dep)]);
  }
};

// #{(l, i, r) : l < i < r < n : max[l, i) < min[i, r)}
ll calc(const vi& as) {
  ll n = as.size();

  RMinQ mins(as);
  RMaxQ maxs(as);

  ll ans = 0;

  fore(i, 1, n) {
    ll l = i - 1, r = i + 1;
    if (as[l] >= as[i]) continue;

    while (r < n && maxs.query(l, i) < mins.query(i, r + 1)) {
      r++;
    }

    ans += r - i;

    while (l > 0) {
      l--;

      while (r > i && !(maxs.query(l, i) < mins.query(i, r))) {
        r--;
      }

      ans += r - i;
    }
  }

  return ans;
}

ll forceCalc(const vi& as) {
  ll n = as.size();

  RMinQ mins(as);
  RMaxQ maxs(as);

  ll ans = 0;

  fore(l, 0, n) {
    fore(i, l + 1, n) {
      fore(r, i + 1, n + 1) {
        if (maxs.query(l, i) < mins.query(i, r)) {
          ans++;
        }
      }
    }
  }

  return ans;
}

int main(){
  ios::sync_with_stdio(0), cin.tie(0);

  ll t;
  cin >> t;
  while (t--) {
    ll n;
    cin >> n;

    vi as(n);
    for (ll& a : as) {
      cin >> a;
    }

    ll c = calc(as);

    ll ans = n * (n * n - 1) / 6 - c;

    cout << ans << '\n';
  }

}

