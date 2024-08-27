// https://codeforces.com/gym/104172/problem/C
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define mset(a,v) memset((a),(v),sizeof(a))
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<bool> vb;

void next(vb& x) {
  ll n = x.size();
  ll i = 0;
  while (i < n && x[i]) {
    i++;
  }
  assert(i < n);

  x[i] = true;
  fore(j, 0, i) {
    x[j] = false;
  }
}

vb neg(const vb& x) {
  vb ans(x.size());
  fore(i, 0, x.size()) {
    ans[i] = !x[i];
  }
  return ans;
}

ll count(const vb& x) {
  ll n = x.size();
  ll ans = 0;
  fore(i, 0, n) {
    ans += x[i];
  }
  return ans;
}

vector<vb> transpose(const vector<vb>& x) {
  ll n = x.size(), m = x[0].size();
  vector<vb> ans(m, vb(n));
  fore(i, 0, n) fore(j, 0, m) {
    ans[j][i] = x[i][j];
  }
  return ans;
}

vector<vb> solve_square(ll n) {
  assert(n % 2 == 0);
  vector<vb> ans(n, vb(n, false));

  fore(i, 0, n / 2) {
    fore(j, 0, i) {
      ans[i][j] = true;
    }
  }
  fore(i, n / 2, n) {
    fore(j, 0, i + 1) {
      ans[i][j] = true;
    }
  }

  ans[n / 2][n / 2] = false;
  ans[n / 2 - 1][n / 2] = true;

  return ans;
}

bool nice(const vb& x) { // nice(x) iff x = 0…01…1 or x = 1…10…0
  ll n = x.size();

  bool f = x[0];
  ll i = 1;
  while (i < n && x[i] == f) {
    i++;
  }

  if (i == n) {
    return true;
  }

  fore(j, i + 1, n) {
    if (x[j] == f) {
      return false;
    }
  }

  return true;
}

vector<vb> solve_even_lt_even(ll n, ll m) {
  assert(n < m && n % 2 == 0 && m % 2 == 0);

  vector<vb> ans(m, vb(n, false));
  fore(i, 0, n + 1) {
    fore(j, 0, i) {
      ans[i][j] = true;
    }
  }

  fore(j, n / 2, n) {
    ans[n + 1][j] = true;
  }

  ll i;
  for (i = n + 2; i < min(m, 2 * n); i += 2) {
    assert(i + 1 < m);
    ll k = (i - n) / 2;
    fore(j, k, n) {
      ans[i][j] = true;
    }
    fore(j, n - k, n) {
      ans[i + 1][j] = true;
    }
  }

  vb x(n, false);
  for (; i < m; ) {
    while (nice(x)) {
      next(x);
    }
    ans[i] = x;
    i++;
    ans[i] = neg(x);
    i++;
    next(x);
  }

  ans = transpose(ans);

  return ans;
}

vector<vb> solve_odd_lt_even(ll n, ll m) {
  assert(n < m && n % 2 == 1 && m % 2 == 0);

  vector<vb> ans(m, vb(n, false));
  fore(i, 0, n + 1) {
    fore(j, 0, i) {
      ans[i][j] = true;
    }
  }

  ll i;
  for (i = n + 1; i < min(m, 2 * n); i += 2) {
    assert(i + 1 < m);
    ll k = i - n;
    fore(j, k, n) {
      ans[i][j] = true;
    }
    fore(j, n - k, n) {
      ans[i + 1][j] = true;
    }
  }

  vb x(n, false);
  for (; i < m; ) {
    while (nice(x)) {
      next(x);
    }
    ans[i] = x;
    i++;
    ans[i] = neg(x);
    i++;
    next(x);
  }

  ans = transpose(ans);

  return ans;
}

vector<vb> solve_even_lt_odd(ll n, ll m) {
  assert(n < m && n % 2 == 0 && m % 2 == 1);

  vector<vb> ans(m, vb(n, false));
  fore(i, 0, n + 1) {
    fore(j, 0, i) {
      ans[i][j] = true;
    }
  }

  ll i;
  for (i = n + 1; i < min(m, 2 * n - 2); i += 2) {
    assert(i + 1 < m);
    ll k = (i - n + 1) / 2;
    fore(j, k, n) {
      ans[i][j] = true;
    }
    fore(j, n - k, n) {
      ans[i + 1][j] = true;
    }
  }

  vb x(n, false);
  for (; i < m; ) {
    while (nice(x)) {
      next(x);
    }
    ans[i] = x;
    i++;
    ans[i] = neg(x);
    i++;
    next(x);
  }

  ans = transpose(ans);

  return ans;
}

vector<vb> solve_le(ll n, ll m) {
  assert(n <= m);

  if (n < 30 && (1ll << n) < m) {
    return {};
  }

  if (n & m & 1) {
    return {};
  }

  if (n == m) {
    return solve_square(n);
  }

  if (n % 2 == 0 && m % 2 == 0) {
    return solve_even_lt_even(n, m);
  }
  if (n % 2 == 1 && m % 2 == 0) {
    return solve_odd_lt_even(n, m);
  }
  if (n % 2 == 0 && m % 2 == 1) {
    return solve_even_lt_odd(n, m);
  }

  assert(false);
}

vector<vb> solve(ll n, ll m) {
  if (n * m % 2 == 1) {
    return {};
  }

  bool sawped = false;
  if (m < n) {
    swap(n, m);
    sawped = true;
  }

  vector<vb> ans = solve_le(n, m);

  if (ans.empty()) {
    return {};
  }

  if (sawped) {
    ans = transpose(ans);
  }

  return ans;
}

bool check(vector<vb> ans) {
  ll n = ans.size(), m = ans[0].size();

  set<vb> s;
  fore(i, 0, n) {
    if (s.count(ans[i])) {
      return false;
    }
    s.insert(ans[i]);
  }
  ans = transpose(ans);
  s = {};
  fore(i, 0, m) {
    if (s.count(ans[i])) {
      return false;
    }
    s.insert(ans[i]);
  }

  return true;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

#ifndef TEST
  ll T;
  cin >> T;

  while (T--) {
    ll n, m;
    cin >> n >> m;

    auto ans = solve(n, m);
    if (!ans.empty()) {
      cout << "YES\n";
      for (vb& row : ans) {
        for (bool x : row) {
          cout << (ll)x;
        }
        cout << '\n';
      }
    } else {
      cout << "NO\n";
    }
  }
#else
  fore(n, 1, 100) fore(m, 1, 100) {
    auto ans = solve(n, m);
    if (!ans.empty()) {
      if (!check(ans)) {
        cerr << n << ' ' << m;
        return 1;
      }
    }
  }
#endif

}
