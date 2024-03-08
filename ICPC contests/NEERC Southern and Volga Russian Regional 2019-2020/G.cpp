// https://codeforces.com/contest/1250/problem/G
#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(x) x.begin(),x.end()
#define SZ(x) (ll(x.size()))
#define fore(i,a,b) for(ll i=a, gmat=b;i<gmat;++i)
#define pb push_back
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;

optional<vi> solve(ll k, const vi& as, const vi& bs) {
  ll n = as.size();

  vi presums_as(n + 1), presums_bs(n + 1);
  fore(i, 0, n) {
    presums_as[i + 1] = presums_as[i] + as[i];
    presums_bs[i + 1] = presums_bs[i] + bs[i];
  }

  ll A = 0, B = 0;

  ll i = -1;

  fore(j, 0, n) {
    ll a = as[j], b = bs[j];

    while (A + a >= k) {
      i++;
      if (i == j) {
        return {};
      }

      A = max(0ll, presums_as[i + 1] - presums_bs[i + 1]) + presums_as[j] - presums_as[i + 1];
      B = max(0ll, presums_bs[i + 1] - presums_as[i + 1]) + presums_bs[j] - presums_bs[i + 1];
    }

    A += a, B += b;

    if (B >= k) {
      break;
    }
  }

  if (B < k) {
    return {};
  }

  vi ans;

  if (i >= 0) {
    A = 0, B = 0;
    fore(j, 0, i + 1) {
      ll a = as[j], b = bs[j];

      if (A + a >= k) {
        ll m = min(A, B);
        A -= m, B -= m;
        ans.push_back(j - 1);
      }

      A += a, B += b;
    }

    ans.push_back(i);
  }

  return ans;
}

optional<vi> force(ll k, const vi& as, const vi& bs) {
  ll n = as.size();

  ll ans_v = 1ll << 60;
  ll ans_mask;

  fore(x, 0, 1 << n) {
    ll this_ans = __builtin_popcountll(x);
    if (this_ans < ans_v) {

      ll A = 0, B = 0;
      fore(i, 0, n) {
        A += as[i], B += bs[i];

        if (A >= k) {
          goto next;
        }
        if (B >= k) {
          break;
        }
        if (x & (1 << i)) {
          ll d = min(A, B);
          A -= d, B -= d;
        }
      }

      ans_v = this_ans;
      ans_mask = x;
    }
    next:;
  }

  if (ans_v == (1ll << 60)) {
    return {};
  }

  vi ans;
  fore(i, 0, n) {
    if (ans_mask & (1 << i)) {
      ans.push_back(i);
    }
  }

  return ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);

  ll t;
  cin >> t;
  while (t--) {
    ll n, k;
    cin >> n >> k;
    vi as(n), bs(n);
    for (ll& a : as) {
      cin >> a;
    }
    for (ll& b : bs) {
      cin >> b;
    }

    auto ans = solve(k, as, bs);
    if (ans.has_value()) {
      cout << ans->size() << '\n';
      for (ll a : *ans) {
        cout << a + 1 << ' ';
      }
      cout << '\n';
    } else {
      cout << "-1\n";
    }
  }

/*   fore(_, 0, 1000) {
    ll n = rand() % 15 + 2, k = rand() % 200 + 2;
    vi as(n), bs(n);
    for(ll& a : as) {
      a = rand() % (k - 2) + 1;
    }
    for(ll& b : bs) {
      b = rand() % (k - 2) + 1;
    }

    auto ans = solve(k, as, bs);
    auto ans2 = force(k, as, bs);

    if (ans != ans2) {
      cerr << "ERROR:\n";
      cerr << n << ' ' << k << '\n';
      for (ll a : as) {
        cerr << a << ' ';
      }
      cerr << '\n';
      for (ll b : bs) {
        cerr << b << ' ';
      }
      cerr << '\n';
      cerr << "ans:\n";
      if (!ans.has_value()) {
        cerr << "-1\n";
      } else {
        cerr << ans->size() << '\n';
        for (ll a : *ans) {
          cerr << a + 1 << ' ';
        }
        cerr << '\n';
      }
      cerr << "ans2:\n" ;
      if (!ans2.has_value()) {
        cerr << "-1\n";
      } else {
        cerr << ans2->size() << '\n';
        for (ll a : *ans2) {
          cerr << a + 1 << ' ';
        }
        cerr << '\n';
      }
    }
    cerr << endl;

    return 1;
  } */

  return 0;
}
