// https://codeforces.com/group/hzSLIARNBN/contest/464702/problem/A

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef unsigned int uint;
typedef unsigned char uchar;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

static constexpr ull max_d = 1e18;

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

tuple<ull, vector<ull>, map<ull, ull>> compress(vector<ull> xs) {
  ull n = xs.size();

  map<ull, vector<ull>> xs_map;
  fore(i, 0, n) {
    xs_map[xs[i]].push_back(i);
  }

  vector<ull> compressed_xs(n);
  map<ull, ull> ans_map;

  ull i = 0;
  for (auto [x, ks] : xs_map) {
    for (ull k : ks) {
      compressed_xs[k] = i;
    }
    ans_map[x] = i;
    i++;
  }

  return {i - 1, compressed_xs, ans_map};
}

ull solve(const vector<tuple<ull, ull, ull>>& DVTs) {
  ull n = DVTs.size();

  vector<ull> important_D;
  fore(i, 0, n) {
    auto [D, V, T] = DVTs[i];
    important_D.push_back(D);
    if (D >= T) {
      important_D.push_back(D - T);
    }
  }

  auto [k, xs, m] = compress(important_D);

  Tree t(k + 1);

  ull ans = 0;

  fore(i, 0, n) {
    auto [D, V, T] = DVTs[i];

    ull DT_x = m[D > T ? D - T : 0];
    ull D_x = m[D];

    ull best = t.query(DT_x, D_x+1);
    ull actual = t.query(D_x, D_x + 1);

    ull now = best + V;
    if (now > actual) {
      t.update(D_x, now);
      ans = max(ans, now);
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n;
  cin >> n;
  vector<tuple<ull, ull, ull>> DVTs(n);
  for (auto& [d, v, t] : DVTs) {
    cin >> d >> v >> t;
  }

  auto ans = solve(DVTs);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
