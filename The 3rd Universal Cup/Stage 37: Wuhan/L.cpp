// https://contest.ucup.ac/contest/2025/problem/10747
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
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;


ll solve(vi as) {
  ll n = as.size();

  sort(ALL(as));

  map<ll, ii> apps;
  fore(i, 0, n) {
    ll a = as[i];

    if (!apps.count(a)) {
      apps[a] = {i, i};
    } else {
      apps[a].second = i;
    }
  }

  ll ans = 1;

  fore(i, 0, n) {
    fore(k, i + 1, n) {
      ll di = as[i], dk = as[k];

      if (((di + dk) & 1) == 0) {
        ll dm = (di + dk) >> 1;
        if (!apps.count(dm)) {
          continue;
        }
        ll m = i + ((k - i)) / 2;
        if (dm == as[m]) {
          ans = max(ans, k - i + 1);
        } else if (as[m] < dm) { // dm está a la derecha
          ll this_ans = 2 * (k + 1 - apps[dm].first) - 1;
          ans = max(ans, this_ans);
        } else { // dm a la izquierda
          ll this_ans = 2 * (apps[dm].second + 1 - i);
          ans = max(ans, this_ans);
        }
      }
    }
  }

  return ans;
}

ll force(vi as) {
  ll n = as.size();

  ll ans = 0;

  fore(x, 1, 1 << n) {
    vi ds;
    fore(i, 0, n) if (x & (1 << i)) {
      ds.push_back(as[i]);
    }

    sort(ALL(ds));

    ll k = ds.size();
    ll d0 = ds[0], dk = ds.back();
    ll m = (k - 1) / 2;

    if (!((d0 + dk) & 1) && ds[m] == (d0 + dk) / 2) {
      ans = max(ans, k);
    }
  }

  return ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);
#ifndef TEST
  ll T;
  cin >> T;
  while (T--) {
    ll n;
    cin >> n;
    vi as(n);
    for (ll& a : as) {
      cin >> a;
    }

    ll ans = solve(as);
    cout << ans << '\n';
  }
#else
  fore(_, 0, 10000) {
    ll n = rand() % 5 + 1;
    vi as(n);
    for (ll& a : as) {
      a = rand() % 10 + 1;
    }

    ll ans = solve(as);
    ll ansf = force(as);

    if (ans != ansf) {
      cout << n << '\n';
      for (ll a : as) {
        cout << a << ' ';
      }
      cout << '\n';
      cout << "ans: " << ans << "\nansf: " << ansf << '\n';
      return 1;
    }
  }
#endif
}