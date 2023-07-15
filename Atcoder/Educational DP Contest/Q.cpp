// https://atcoder.jp/contests/dp/tasks/dp_q

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

/**
 * Author: Lucian Bicsi
 * Date: 2017-10-31
 * License: CC0
 * Source: folklore
 * Description: Zero-indexed max-tree. Bounds are inclusive to the left and exclusive to the right. Can be changed by modifying T, f and unit.
 * Time: O(\log N)
 * Status: stress-tested
 */
struct Tree {
	typedef ull T;
	static constexpr T unit = 0;
	T f(T a, T b) { return max(a, b); } // (any associative fn)
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

ull solve(vector<ull> hs, vector<ull> as) {
  ull N = hs.size();

  Tree dp(N + 1); // dp[i] = max beauty with maximum height i

  fore(i, 0, N) {
    ull h = hs[i], a = as[i];
    ull best = dp.query(0, h);
    ull beauty = best + a;
    dp.update(h, beauty);
  }

  return dp.query(0, N + 1);
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N;
  cin >> N;
  vector<ull> hs(N), as(N);
  for (ull& h : hs) {
    cin >> h;
  }
  for (ull& a : as) {
    cin >> a;
  }

  cout << solve(hs, as) << '\n';

  return EXIT_SUCCESS;
}
