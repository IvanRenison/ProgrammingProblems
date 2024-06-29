// https://codeforces.com/group/gmV7IkT2pN/contest/520377/problem/G

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
typedef long long ll;
typedef vector<ll> vi;

#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; i++)

struct Tree {
  typedef ll T; typedef ll L; // T: data type, L: lazy type
  constexpr static T tneut = 1ll << 60; constexpr static L lneut = 0;
  // neutrals
  T f(T a, T b) { return min(a, b); } // operation
  T apply(T v, L l) { return v + l; }
  // new st according to lazy
  L comb(L a, L b) { return a + b; }
  // cumulative effect of lazy

	ll n;
	vector<T> s;
	vector<L> d;

	Tree(ll n = 0) : n(n), s(2*n, tneut), d(n, lneut) {}
	Tree(vector<T>& vals) : n(vals.size()), s(2*n), d(n, lneut) {
		copy(vals.begin(), vals.end(), begin(s) + n);
		for (ll i = n - 1; i > 0; i--) s[i] = f(s[2*i], s[2*i+1]);
	}

	void apply_(ll p, L value) {
		s[p] = apply(s[p], value);
		if (p < n) d[p] = comb(d[p], value);
	}

	void build(ll p) {
		while (p > 1)
			p /= 2, s[p] = apply(f(s[2*p], s[2*p+1]), d[p]);
	}

	void push(ll p) {
		for (ll s = 63 - __builtin_clzll(n); s > 0; s--) {
			ll i = p >> s;
			apply_(2*i, d[i]);
			apply_(2*i+1, d[i]);
			d[i] = lneut;
		}
	}

	void upd(ll l, ll r, L value) {
		l += n, r += n;
		push(l);
		push(r - 1);
		ll l0 = l, r0 = r;
		for (; l < r; l /= 2, r /= 2) {
			if (l&1) apply_(l++, value);
			if (r&1) apply_(--r, value);
		}
		build(l0);
		build(r0 - 1);
	}

	T query(ll l, ll r) {
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

uint solve(const vi& as) {
  uint n = as.size();

  uint ans = 0;

  vi sums_pos(n + 1);
  fore(i, 0, n) {
    if (as[i] >= 0) {
      sums_pos[i + 1] = sums_pos[i] + as[i];
      ans++;
    } else {
      sums_pos[i + 1] = sums_pos[i];
    }
  }

  vector<pair<ll, uint>> negs;
  fore(i, 0, n) {
    if (as[i] < 0) {
      negs.push_back({as[i], i});
    }
  }

  sort(negs.begin(), negs.end(), greater<>());

  Tree tree(sums_pos);

  for (auto [a, i] : negs) {
    ll m = tree.query(i + 1, n + 1);
    if (m + a >= 0) {
      ans++;
      tree.upd(i + 1, n + 1, a);
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  uint n;
  cin >> n;
  vi as(n);
  for (ll& a : as) {
    cin >> a;
  }

  uint ans = solve(as);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
