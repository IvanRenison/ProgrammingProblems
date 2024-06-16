// https://codeforces.com/contest/1969/problem/E

#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) (x).begin(), (x).end()
#define SZ(x) (x).size()

const ull inf = 1ull << 60;

ull force(vu as) {
  ull n = as.size();

  ull ans = inf;

  fore(x, 0, 1 << n) {
    vu bs = as;
    ull b = n;
    fore(i, 0, n) if (x & (1 << i)) {
      bs[i] = b;
      b++;
    }
    bool valid = true;
    fore(i, 0, n) {
      fore(j, i + 1, n + 1) {
        map<ull, ull> counter;
        fore(k, i, j) {
          counter[bs[k]]++;
        }
        bool found1 = false;
        for (auto [_, c] : counter) {
          if (c == 1) {
            found1 = true;
            break;
          }
        }
        if (!found1) {
          valid = false;
          break;
        }
      }
    }

    if (valid) {
      ans = min(ans, (ull)__builtin_popcountll(x));
    }
  }

  return ans;
}

struct Tree {
  typedef ll T; typedef ll L; // T: data type, L: lazy type
  // neutrals
  constexpr static T tneut = inf; constexpr static L lneut = 0;
  T f(T a, T b) { return min(a, b); } // operation
  // new st according to lazy
  T apply(T v, L l) { return v + l; }
  // cumulative effect of lazy
  L comb(L a, L b) { return a + b; }

	ll n;
	vector<T> s;
	vector<L> d;

	Tree(ll n = 0) : n(n), s(2*n, tneut), d(n, lneut) {}
	Tree(vector<T> vals) : n(SZ(vals)), s(2*n), d(n, lneut) {
		copy(ALL(vals), begin(s) + n);
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

ull solve(const vu& as) {
  ull n = as.size();

  ull ans = 0;

  Tree st(vi(n, 0));
  vu last(n, inf), prev_last(n, inf);
  ull this_start = 0;

  fore(i, 0, n) {
    ull a = as[i];
    if (last[a] == inf) {
      st.upd(this_start, i + 1, 1);
      last[a] = i;
    } else {
      ll k = prev_last[a];
      if (k == inf) {
        k = this_start;
      } else {
        k++;
      }
      st.upd(k, last[a] + 1, -1);
      st.upd(last[a] + 1, i + 1, 1);
      ll q = st.query(this_start, i + 1);
      if (q <= 0) {
        ans++;
        this_start = i + 1;
        fore(j, this_start, i + 1) {
          last[as[j]] = prev_last[as[j]] = inf;
        }
      }

      prev_last[a] = last[a];
      last[a] = i;
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

#ifndef TEST
  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;
    vu as(n);
    for (ull& a : as) {
      cin >> a;
      a--;
    }

    ull ans = solve(as);
    cout << ans << '\n';
  }
#else
  fore(_, 0, 100000) {
    ull n = rand() % 8 + 1;
    vu as(n);
    fore(i, 0, n) {
      as[i] = rand() % n;
    }

    ull ans = solve(as);
    ull ansf = force(as);
    if (ansf != ans) {
      cerr << "Fail" << endl;
      cerr << n << endl;
      fore(i, 0, n) {
        cerr << as[i] << ' ';
      }
      cerr << endl;
      cerr << ansf << ' ' << ans << endl;
      return EXIT_FAILURE;
    }
  }
#endif

  return EXIT_SUCCESS;
}
