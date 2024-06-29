// https://codeforces.com/group/gmV7IkT2pN/contest/530194/problem/F

#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) begin(x), end(x)

struct Tree {
  typedef ull T; typedef ull L; // T: data type, L: lazy type
  // neutrals
  constexpr static T tneut = 0; constexpr static L lneut = 0;
  T f(T a, T b) { return max(a, b); } // operation
  // new st according to lazy
  T apply(T v, L l) { return v + l; }
  // cumulative effect of lazy
  L comb(L a, L b) { return a + b; }
	ull n;
	vector<T> s;
	vector<L> d;

	Tree(ull n = 0) : n(n), s(2*n, tneut), d(n, lneut) {}
	Tree(vector<T>& vals) : n(vals.size()), s(2*n), d(n, lneut) {
		copy(ALL(vals), begin(s) + n);
		for (ull i = n - 1; i > 0; i--) s[i] = f(s[2*i], s[2*i+1]);
	}

	void apply_(ull p, L value) {
		s[p] = apply(s[p], value);
		if (p < n) d[p] = comb(d[p], value);
	}

	void build(ull p) {
		while (p > 1)
			p /= 2, s[p] = apply(f(s[2*p], s[2*p+1]), d[p]);
	}

	void push(ull p) {
		for (ull s = 63 - __builtin_clzll(n); s > 0; s--) {
			ull i = p >> s;
			apply_(2*i, d[i]);
			apply_(2*i+1, d[i]);
			d[i] = lneut;
		}
	}

	void upd(ull l, ull r, L value) {
		l += n, r += n;
		push(l);
		push(r - 1);
		ull l0 = l, r0 = r;
		for (; l < r; l /= 2, r /= 2) {
			if (l&1) apply_(l++, value);
			if (r&1) apply_(--r, value);
		}
		build(l0);
		build(r0 - 1);
	}

	T query(ull l, ull r) {
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
const ull aLim = 26;

ull solve(const vu& as) {
  ull n = as.size();

  vector<vu> pos(aLim);
  fore(i, 0, n) {
    pos[as[i]].push_back(i);
  }
  fore(j, 0, aLim) {
    reverse(ALL(pos[j]));
  }

  ull ans = 0;

  Tree st(n);
  fore(i, 0, n) {
    ull a = as[n - 1 - i];
    ull j = pos[a].back();
    pos[a].pop_back();

    ull this_ans = j + st.query(j, j + 1) - i;
    ans += this_ans;

    st.upd(0, j, 1);
  }

  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull n;
  string s;
  cin >> n >> s;
  vu as(n);
  fore(i, 0, n) {
    as[i] = s[i] - 'a';
  }

  ull ans = solve(as);
  cout << ans << '\n';
}
