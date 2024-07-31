// https://codeforces.com/contest/1997/problem/E

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef long long ll;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()

const ull inf = 1ull << 60;

struct TreeMin {
  typedef uu T;
  static constexpr T neut = {inf, inf};
  T f(T a, T b) { return min(a, b); } // (any associative fn)
  vector<T> s; ll n;
  TreeMin(ll n = 0, T def = neut) : s(2*n, def), n(n) {}
  void upd(ll pos, T val) {
    for (s[pos += n] = val; pos /= 2;)
      s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
  }
  T query(ll b, ll e) { // query [b, e)
    T ra = neut, rb = neut;
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if (b % 2) ra = f(ra, s[b++]);
      if (e % 2) rb = f(s[--e], rb);
    }
    return f(ra, rb);
  }
};

struct TreeSum {
  typedef ull T;
  static constexpr T neut = 0;
  static T f(T a, T b) { return a + b; } // (any associative fn)
  vector<T> s; ll n;
  TreeSum(ll n = 0, T def = neut) : s(2*n, def), n(n) {}
  void upd(ll pos, T val) {
    for (s[pos += n] = val; pos /= 2;)
      s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
  }
  T query(ll b, ll e) const { // query [b, e)
    T ra = neut, rb = neut;
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if (b % 2) ra = f(ra, s[b++]);
      if (e % 2) rb = f(s[--e], rb);
    }
    return f(ra, rb);
  }
};

// First j such then t.query(i, j) >= a
ull firstSumMore(const TreeSum& t, ull i, ull a) {

  ull l = i, r = t.n;
  while (l + 1 < r) {
    ull m = (l + r) / 2;
    if (t.query(i, m) >= a) {
      r = m;
    } else {
      l = m;
    }
  }

  return l + 1;
}

vb solve(const vu& as, const vuu& queries) {
  ull n = as.size(), q = queries.size();

  TreeSum sums(n);
  fore(i, 0, n) {
    sums.upd(i, 1);
  }

  TreeMin mins(n);
  fore(i, 0, n) {
    mins.upd(i, {as[i], i});
  }

  vector<vu> ups(n); // ups[x] = levels ups when k = x

  for (ull x = n; --x;) {
    ups[x].push_back(0);
    ull i = firstSumMore(sums, 0, x), l = 1;
    while (i < n) {
      ups[x].push_back(i);
      l++;
      while (true) {
        auto [a, j] = mins.query(i, n);
        if (a >= l) {
          break;
        }
        sums.upd(j, 0);
        mins.upd(j, {inf, inf});
      }
      i = firstSumMore(sums, i, x);
    }
  }

  vb ans;
  ans.reserve(q);
  for (auto [i, x] : queries) {
    if (x >= n) {
      ans.push_back(true);
    } else {
      ull j = upper_bound(ALL(ups[x]), i) - ups[x].begin();
      bool this_ans = j <= as[i];
      ans.push_back(this_ans);
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull n, q;
  cin >> n >> q;
  vu as(n);
  for (ull& a : as) {
    cin >> a;
  }
  vuu queries(q);
  for (auto& [i, x] : queries) {
    cin >> i >> x;
    i--;
  }

  vb ans = solve(as, queries);
  for (bool b : ans) {
    cout << (b ? "YES" : "NO") << '\n';
  }
}
