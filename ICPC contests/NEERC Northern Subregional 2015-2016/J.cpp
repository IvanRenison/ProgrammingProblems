// https://codeforces.com/gym/100801
#include <bits/stdc++.h>
#define fore(i, a, b) for (int i = a, gmat = b; i < gmat; ++i)
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
typedef unsigned long long ull;
typedef long long ll;

struct Tree {
	typedef ull T;
	static constexpr T unit = ULLONG_MAX;
	T f(T a, T b) { return min(a, b); } // (any associative fn)
	vector<T> s; int n;
	Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
	void update(int pos, T val) {
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};

/* Find the minimum index for witch f is true or upper if none if true */
ull binary_search(function<bool(ull)> f, ull lower, ull upper) {
  if (f(lower)) {
    return lower;
  }
  if (!f(upper - 1)) {
    return upper;
  }
  while (lower + 1 < upper) {
    ull m = (lower + upper) / 2;
    if (f(m)) {
      upper = m;
    } else {
      lower = m;
    }
  }

  return upper;
}

ull solveWith(ull r, const vector<ull>& ds) {
  ull n = ds.size() + 2;

  Tree dp(n);
  dp.update(0, 0);
  fore(i, 1, min(r + 1, n - 1)) {
    dp.update(i, ds[i - 1]);
  }
  fore(i, r + 1, n - 1) {
    ull q = dp.query(i - r, i);
    dp.update(i, q + ds[i - 1]);
  }
  ull q = dp.query(n - 1 - r, n - 1);
  return q;
}

ull solve(ull t, vector<ull>& ps, vector<ull>& ds) {
  ull n = ps.size() + 1;
  t -= (n - 1);

  ull min_amount = binary_search([&](ull r) {
    return solveWith(r, ds) <= t;
  }, 1, n);


  ull ans = ps[min_amount - 1];
  fore(i, min_amount, n - 1) {
    ans = min(ans, ps[i]);
  }

  return ans;
}

int main() {
  FIN;
#ifdef ONLINE_JUDGE
  freopen("journey.in", "r", stdin);
  freopen("journey.out", "w", stdout);
#endif

  ull n, t;
  cin >> n >> t;
  vector<ull> ps(n - 1), ds(n - 2);
  for (ull& p : ps) {
    cin >> p;
  }
  for (ull& d : ds) {
    cin >> d;
  }

  auto ans = solve(t, ps, ds);
  cout << ans << '\n';

  return 0;
}
