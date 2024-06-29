// https://codeforces.com/group/gmV7IkT2pN/contest/530194/problem/D

#include <bits/stdc++.h>
using namespace std;

typedef unsigned int uint;
typedef vector<uint> vu;
#define ALL(x) begin(x), end(x)

struct Tree {
  typedef uint T; typedef uint L; // T: data type, L: lazy type
  // neutrals
  constexpr static T tneut = 0; constexpr static L lneut = 0;
  T f(T a, T b) { return max(a, b); } // operation
  // new st according to lazy
  T apply(T v, L l) { return v + l; }
  // cumulative effect of lazy
  L comb(L a, L b) { return a + b; }
	uint n;
	vector<T> s;
	vector<L> d;

	Tree(uint n = 0) : n(n), s(2*n, tneut), d(n, lneut) {}
	Tree(vector<T>& vals) : n(vals.size()), s(2*n), d(n, lneut) {
		copy(ALL(vals), begin(s) + n);
		for (uint i = n - 1; i > 0; i--) s[i] = f(s[2*i], s[2*i+1]);
	}

	void apply_(uint p, L value) {
		s[p] = apply(s[p], value);
		if (p < n) d[p] = comb(d[p], value);
	}

	void build(uint p) {
		while (p > 1)
			p /= 2, s[p] = apply(f(s[2*p], s[2*p+1]), d[p]);
	}

	void push(uint p) {
		for (uint s = 63 - __builtin_clzll(n); s > 0; s--) {
			uint i = p >> s;
			apply_(2*i, d[i]);
			apply_(2*i+1, d[i]);
			d[i] = lneut;
		}
	}

	void upd(uint l, uint r, L value) {
		l += n, r += n;
		push(l);
		push(r - 1);
		uint l0 = l, r0 = r;
		for (; l < r; l /= 2, r /= 2) {
			if (l&1) apply_(l++, value);
			if (r&1) apply_(--r, value);
		}
		build(l0);
		build(r0 - 1);
	}

	T query(uint l, uint r) {
		l += n, r += n;
		push(l);
		push(r - 1);
		T ans = tneut;
		for (; l < r; l /= 2, r /= 2) {
			if (l&1) ans = f(ans, s[l++]);
			if (r&1) ans = f(s[--r], ans);
		}
		return ans;
	}
};

// Value of a after k updates
uint calcVal(uint a, uint k) {
  for (; k > 0 && a > 9; k--) {
    uint b = 0;
    for (; a > 0; a /= 10) {
      b += a % 10;
    }
    a = b;
  }
  return a;
}

void Case() {
  uint n, q;
  cin >> n >> q;
  vu as(n);
  for (uint& a : as) {
    cin >> a;
  }

  Tree t(n);

  while (q--) {
    uint op;
    cin >> op;
    if (op == 1) {
      uint l, r;
      cin >> l >> r;
      l--;
      t.upd(l, r, 1);
    } else {
      uint x;
      cin >> x;
      x--;
      uint k = t.query(x, x + 1);
      uint ans = calcVal(as[x], k);
      cout << ans << '\n';
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  uint t;
  cin >> t;

  while (t--) {
    Case();
  }
}
