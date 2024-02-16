// https://codeforces.com/gym/104875
#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(x) x.begin(),x.end()
#define SZ(x) ll(x.size())
#define fore(i,a,b) for(ll i=a, gmat=b;i<gmat;++i)
#define mset(a,v) memset((a),(v),sizeof(a))
#define pb push_back
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;

ii check(ll n, vii edges) {
  vector<vi> adj(n);
  for (auto [u, v] : edges) {
    adj[u].push_back(v), adj[v].push_back(u);
  }

  vi dists(n, -1);
  dists[0] = 0;

  vi s = {0};

  for (ll d = 0; !s.empty(); d++) {

    vi s_;

    for (ll u : s) {
      for (ll v : adj[u]) {
        if (dists[v] == -1) {
          dists[v] = d + 1;
          s_.push_back(v);
        }
      }
    }

    s = s_;
  }

  ll sum = 0;
  for (ll d : dists) {
    sum += d;
  }

  ll g = gcd(sum, n);
  sum /= g, n /= g;

  return {sum, n};
}

pair<ll, vii> solve(ll a, ll b) {
  if (b - 1 > a) {
    return {0, {}};
  }
  if (a == b) {
    return {3, {{0, 1}, {1, 2}}};
  }
  if (b - 1 != a) {
    ll r = 1000000/b;
    b *= r;
    a *= r;
  }

  ll sueltos = b - 1, pila = 0, extra = -1;
  ll sum = b - 1;
  while (sum != a && sueltos > 0) {
    if (a - sum > pila) {
      sum += pila;
      sueltos--;
      pila++;
    } else {
      extra = a - sum;
      sueltos--;
      sum = a;
      break;
    }
  }
  if (sum != a) {
    return {0, {}};
  }
  vii ans;
  fore(i, 0, pila) {
    ans.push_back({i, i + 1});
  }
  fore(i, 0, sueltos) {
    ans.push_back({0, i + 1 + pila});
  }
  if (extra != -1) {
    ans.push_back({extra, b - 1});
  }
  assert(pila + sueltos + (extra != -1) == b - 1);
  return {b, ans};
}

int main(){FIN;

  ll a, b;
  char c;
  cin >> a >> c >> b;

  auto [n, ans] = solve(a, b);
  if (ans.size() == 0) {
    cout << "impossible\n";
  } else {
    //auto [a_, b_] = check(n, ans);
    //assert(a == a_);
    //assert(b == b_);
    cout << n << ' ' << ans.size() << '\n';
    for (auto [u, v] : ans) {
      cout << u+1 << ' ' << v+1 << '\n';
    }
  }
/*
  fore(a, 1, 200) {
    fore(b, 1, 200) {
      ll g = gcd(a, b);
      if (g == 1) {
        auto [n, ans] = solve(a, b);
        if (ans.size() == 0) {
          //cout << "impossible\n";
        } else {
          auto [a_, b_] = check(n, ans);
          if (a != a_ || b != b_) {
            cerr << "ERROR: \n";
            cerr << a << '/' << b << '\n';
            // cout << n << ' ' << ans.size() << '\n';
            // for (auto [u, v] : ans) {
            //   cout << u+1 << ' ' << v+1 << '\n';
            // }
            return EXIT_FAILURE;
          }
        }
      }
    }
  } */

  return 0;
}