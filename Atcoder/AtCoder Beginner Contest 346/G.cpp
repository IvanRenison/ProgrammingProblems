// https://atcoder.jp/contests/abc346/tasks/abc346_g

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
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef tuple<ull, ull, ull> uuu;
typedef vector<uuu> vuuu;
typedef tuple<ull, ull, ull, ull> uuuu;
typedef vector<uuuu> vuuuu;
typedef tuple<ull, ull, ull, ull, ull> uuuuu;
typedef vector<uuuuu> vuuuuu;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;
typedef tuple<ll, ll, ll, ll> iiii;
typedef vector<iiii> viiii;
typedef tuple<ll, ll, ll, ll, ll> iiiii;
typedef vector<iiiii> viiiii;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;

struct STree {
  typedef pair<ll, ull> T; typedef ll L; // T: data type, L: lazy type
  constexpr static T tneut = {inf, 0}; constexpr static L lneut = 0;
  // neutrals
  T f(T a, T b) {
    if (a.first == b.first) {
      return {a.first, a.second + b.second};
    } else {
      return min(a, b);
    }
  } // operation
  T apply(T v, L l) {
    return {v.first + l, v.second};
  }
  // new st according to lazy
  L comb(L a, L b) { return a + b; }
  // cumulative effect of lazy

	ll n;
	vector<T> s;
	vector<L> d;

	STree(ll n = 0) : n(n), s(2*n, tneut), d(n, lneut) {}
	STree(vector<T> vals) : n(SZ(vals)), s(2*n), d(n, lneut) {
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

	void update(ll l, ll r, L value) {
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

ull solve(const vu& As) {
  ull N = As.size();

  vuu lrs(N);

  {
    vu from(N, 0);

    fore(i, 0, N) {
      lrs[i].first = from[As[i]];
      from[As[i]] = i + 1;
    }

    vu from_rev(N, N - 1);
    fore(i, 0, N) {
      ull j = N - i - 1;
      lrs[j].second = from_rev[As[j]];
      from_rev[As[j]] = j - 1;
    }
  }

  vector<vu> l_poss(N);
  fore(i, 0, N) {
    l_poss[lrs[i].first].push_back(i);
  }

  STree st(vector<STree::T>(N, {0, 1}));

  ull ans = 0;

  fore(i, 0, N) {
    for (ull j : l_poss[i]) {
      st.update(j, lrs[j].second + 1, 1);
    }
    auto [m, c] =  st.query(0, N);
    ans += N - c * (m == 0);
    st.update(i, lrs[i].second + 1, -1);
  }

  return ans;
}

ull force(const vu& As) {
  ull N = As.size();

  ull ans = 0;

  fore(i, 0, N) {
    fore(j, i + 1, N + 1) {
      map<ull, ull> counts;
      fore(k, i, j) {
        counts[As[k]]++;
      }
      for (auto [_, c] : counts) {
        if (c == 1) {
          ans++;
          break;
        }
      }
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull N;
  cin >> N;
  vu As(N);
  for (ull& A : As) {
    cin >> A;
    A--;
  }

  auto ans = solve(As);
  cout << ans << '\n';

/*   fore(_, 0, 100) {
    ull N = rand() % 5 + 2;
    vu As(N);
    for (ull& A : As) {
      A = rand() % N;
    }

    ull ans = solve(As);
    ull ans2 = force(As);

    if (ans != ans2) {
      cerr << "ERROR in test " << _ << '\n';
      cerr << N << '\n';
      for (ull A : As) {
        cerr << A + 1 << ' ';
      }
      cerr << '\n';
      cerr << "ans: " << ans << "\nans2: " << ans2 << endl;
      return EXIT_FAILURE;
    }
  } */

  return EXIT_SUCCESS;
}
