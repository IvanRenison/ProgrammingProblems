// https://codeforces.com/group/5GNF7zti59/contest/534709/problem/D
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((ll)x.size())
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;


map<ll, ll> dp;
ll calc(ll x) {
  if (x == 0 || x == 1) {
    return 0;
  }
  if (dp.count(x)) {
    return dp[x];
  }

  ll M = 0;
  ll j = __bit_width(x);
  fore(i, 1, j) {
    ll y = (x & ((1 << i) - 1)) | (x >> i);
    M |= (1 << calc(y));
  }
  ll ans;
  for (ll k = 0; ; k++) {
    if (!(M & (1 << k))) {
      ans = k;
      break;
    }
  }

  return dp[x] = ans;
}


vii factor(ll a) {
  vii ans;
  for (ll i = 2; i * i <= a; i++) {
    if (a % i == 0) {
      ans.push_back({i, 0});
      while (a % i == 0) {
        ans.back().second++;
        a /= i;
      }
    }
  }
  if (a > 1) {
    ans.push_back({a, 1});
  }
  return ans;
}

ll forceP(vi as) {
  sort(ALL(as));


  ll M = as.back();
  if (M == 0) {
    return 0;
  }

  set<ll> s;
  fore(i, 1, M + 1) {
    vi as_ = as;
    for (ll& a : as_) {
      if (a >= i) {
        a -= i;
      }
    }
    s.insert(forceP(as_));
  }

  for (ll x = 0; ; x++) {
    if (!s.count(x)) {
      return x;
    }
  }
}

ll solveP(vi& as) {
  ll n = as.size();
  sort(ALL(as));


  ll count = 0;
  fore (i, 1, n) {
    count += as[i] != as[i-1];
  }

  return count;
}

bool solve(const vi& as) {

  map<ll, vi> primes;
  for (ll a : as) {
    vii fact = factor(a);
    for (auto [p, e] : fact) {
      primes[p].push_back(e);
    }
  }

  ll ans = 0;
  for (auto& [p, es] : primes) {
    ll x = 0;
    for (ll e : es) {
      x |= (1 << e);
    }
    ll this_ans = calc(x);
    ans ^= this_ans;
  }

  return ans == 0;
}

void smaple() {
  ll m = 15;

  vi dp(1 << m);
  dp[1] = 0;

  fore(x, 2, 1 << m) {
    ll j = __bit_width(x);
    set<ll> s;
    fore(i, 1, j) {
      ll y = (x & ((1 << i) - 1)) | (x >> i);
      s.insert(dp[y]);
    }
    for (ll k = 0; ; k++) {
      if (!s.count(k)) {
        dp[x] = k;
        break;
      }
    }
  }

 // vector<set<ll>> per_ceros(22);

/*   fore(x, 1, 1 << m) {
    //per_ceros[21 - __builtin_popcountll(x)].insert(dp[x]);

    ll j = __bit_width(x);
    fore(i, 0, j) {
      cout << ((x & (1 << i)) ? '1' : '0');
    }
    fore(i, j, m) {
      cout << ' ';
    }
    cout << " " << dp[x] << '\n';
  } */
/*   fore(i, 0, 22) {
    cout << i << ": ";
    for (ll a : per_ceros[i]) {
      cout << a << ' ';

    }
    cout << '\n';
  } */

  vector<vi> vals(m + 1);
  fore(x, 0, 1 << m) {
    vals[dp[x]].push_back(x);
  }

  fore(i, 0, m + 1) {
    cout << i << ":\n";
    for (ll x : vals[i]) {
      ll j = __bit_width(x);
      cout << ' ';
      fore(i, 0, j) {
        cout << ((x & (1 << i)) ? '1' : '0');
      }
      cout << '\n';
    }
  }

}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

/*   smaple();
  return 0; */

  ll n;
  cin >> n;
  vi as(n);
  for (ll& a : as) {
    cin >> a;
  }

  bool ans = solve(as);
  if (ans) {
    cout << "Arpa\n";
  } else {
    cout << "Mojtaba\n";
  }

/*   fore(i, 1, 25) {
    vi as = {i};
    ll x = forceP(as);
    //if (x == 0) {
      cout << i << ": " << x << endl;;
    //}
  }
  fore(i, 1, 25) fore(j, i + 1, 25) {
    vi as = {i, j};
    ll x = forceP(as);
    //if (x == 0) {
      cout << i << ' ' << j << ": " << x << endl;
    //}
  }
  fore(i, 1, 25) fore(j, i + 1, 25) fore(k, j + i, 25) {
    vi as = {i, j, k};
    ll x = forceP(as);
    //if (x == 0) {
      cout << i << ' ' << j << ' ' << k << ": " << x << endl;
    //}
  }
  fore(i, 1, 25) fore(j, i + 1, 25) fore(k, j + i, 25) fore(m, k + 1, 25) {
    vi as = {i, j, k, m};
    ll x = forceP(as);
    //if (x == 0) {
      cout << i << ' ' << j << ' ' << k << ' ' << m << ": " << x << endl;
    //}
  } */

/*   vi as;
  fore(i, 1, 20) {
    as.push_back(i);
    cout << i << ' ' << forceP(as) << endl;
  } */

}