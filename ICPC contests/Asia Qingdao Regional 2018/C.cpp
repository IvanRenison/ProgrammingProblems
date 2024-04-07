// https://codeforces.com/gym/104270/problem/C
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((ll)x.size())
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;

ll force(const vi& s, const vi& t) {
  ll n = s.size();

  ll ans = 0;

  fore(i0, 0, n) {
    fore(j0, i0 + 1, n + 1) {
      fore(i1, 0, n) {
        fore(j1, i1 + 1, n + 1) {
          vi s_copy = s;

          fore(k, i0, j0) {
            s_copy[k] ^= 1;
          }

          fore(k, i1, j1) {
            s_copy[k] ^= 1;
          }

          if (s_copy == t) {
            ans++;
          }
        }
      }
    }
  }

  return ans;
}

ll solve(const vi& s, const vi& t) {
  ll n = s.size();

  vi x(n);

  fore(i, 0, n) {
    x[i] = s[i] ^ t[i];
  }

  vii ones;
  ll in_ones = -1;
  fore(i, 0, n) {
    if (in_ones == -1) {
      if (x[i] == 1) {
        in_ones = i;
      }
    } else {
      if (x[i] == 0) {
        ones.push_back({in_ones, i});
        in_ones = -1;
      }
    }
  }

  if (in_ones != -1) {
    ones.push_back({in_ones, n});
  }

  if (ones.size() > 2) {
    return 0;
  }

  if (ones.size() == 2) {
    return 6;
  }

  if (ones.size() == 0) {
    return n * (n + 1) / 2;
  }

  //auto [i, j] = ones[0];

  return 2 * (n - 1);

}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll T;
  cin >> T;
  while (T--) {
    ll n;
    cin >> n;
    vi s(n), t(n);
    for (ll& a : s) {
      char c;
      cin >> c;
      a = c == '1';
    }
    for (ll& a : t) {
      char c;
      cin >> c;
      a = c == '1';
    }

    ll ans = solve(s, t);

    cout << ans << '\n';
  }

/*   fore(_, 0, 10000) {
    ll n = rand() % 10 + 1;
    vi s(n), t(n);
    for (ll& a : s) {
      a = rand() % 2;
    }
    for (ll& a : t) {
      a = rand() % 2;
    }

    ll ans = solve(s, t);
    ll ans2 = force(s, t);

    if (ans != ans2) {
      cerr << n << '\n';

      for (ll a : s) {
        cerr << a;
      }
      cerr << '\n';
      for (ll a : t) {
        cerr << a;
      }
      cerr << '\n';

      cerr << "ans: " << ans << "\nans2: " << ans2 << endl;

      return EXIT_FAILURE;
    }
  } */


}