// https://www.facebook.com/codingcompetitions/hacker-cup/2023/round-1/problems/B2

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef vector<ull> vu;
typedef vector<ll> vi;
typedef vector<double> vd;
typedef pair<ull, ull> uu;
typedef pair<ll, ll> ii;
typedef vector<uu> vuu;
typedef vector<ii> vii;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) (x).begin(), (x).end()

typedef unsigned long long ull;
ull modmul(ull a, ull b, ull M) {
	ll ret = a * b - M * ull(1.L / M * a * b);
	return ret + M * (ret < 0) - M * (ret >= (ll)M);
}
ull modpow(ull b, ull e, ull mod) {
	ull ans = 1;
	for (; e; b = modmul(b, b, mod), e /= 2)
		if (e & 1) ans = modmul(ans, b, mod);
	return ans;
}

bool isPrime(ull n) {
	if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
	ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
	    s = __builtin_ctzll(n-1), d = n >> s;
	for (ull a : A) {   // ^ count trailing zeroes
		ull p = modpow(a%n, d, n), i = s;
		while (p != 1 && p != n - 1 && a % n && i--)
			p = modmul(p, p, n);
		if (p != n-1 && i != s) return 0;
	}
	return 1;
}


ull pollard(ull n) {
	auto f = [n](ull x) { return modmul(x, x, n) + 1; };
	ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
	while (t++ % 40 || __gcd(prd, n) == 1) {
		if (x == y) x = ++i, y = f(x);
		if ((q = modmul(prd, max(x,y) - min(x,y), n))) prd = q;
		x = f(x), y = f(f(y));
	}
	return __gcd(prd, n);
}
vector<ull> factor(ull n) {
	if (n == 1) return {};
	if (isPrime(n)) return {n};
	ull x = pollard(n);
	auto l = factor(x), r = factor(n / x);
	l.insert(l.end(), all(r));
	return l;
}

template<typename T>
struct KDimArray {
  vu ds;
  vector<T> elems;
  KDimArray() {};
  KDimArray(const vu& ds, T l) : ds(ds) {
    ull p = 1;
    for(ull d : ds) {
      p *= d;
    }
    elems = vector<T>(p, l);
  }
  T operator[](const vu& id) const {
    ull idx = 0;
    fore(i, 0, ds.size()) {
      idx *= ds[i];
      idx += id[i];
    }
    return elems[idx];
  }
  T& operator[](const vu& id) {
    ull idx = 0;
    fore(i, 0, ds.size()) {
      idx *= ds[i];
      idx += id[i];
    }
    return elems[idx];
  }
  T last() const {
    return elems.back();
  }
};

void nextIndexs(vu& is, const vu& ds) {
  ull n = is.size();
  for(ull i = n-1; i < n; i--) {
    is[i]++;
    if (is[i] == ds[i]) {
      is[i] = 0;
    } else {
      break;
    }
  }
}

void nextIndexs_(vu& is, const vu& ds) {
  ull n = is.size();
  for(ull i = n-1; i < n; i--) {
    is[i]++;
    if (is[i] > ds[i]) {
      is[i] = 0;
    } else {
      break;
    }
  }
}

bool all0(const vu& is) {
  for(ull i : is) {
    if (i != 0) {
      return false;
    }
  }
  return true;
}


constexpr ull inf = 1ull << 60;

vu calc(vuu& fe) {
  ull n = fe.size();
  vu es(n);
  fore(i, 0, n) {
    es[i] = fe[i].second + 1;
  }

  KDimArray<vector<pair<ull, pair<vu, ull>>>> dp(es, vector<pair<ull, pair<vu, ull>>>(42, {inf,{{}, inf}}));

  vu is(n);

  dp[is][0] = {0, {{}, inf}};
  fore(i, 1, 42) {
    dp[is][i] = {i, {vu(n), 1}};
  }

  nextIndexs(is, es);

  for(; !all0(is); nextIndexs(is, es)) {
    fore(j, 1, 42) {
      ull best = inf, best_p = inf;
      vu best_js(n);
      for(vu js(n); js != is; nextIndexs_(js, is)) {
        ull p = 1;
        fore(i, 0, n) {
          fore(k, js[i], is[i]) {
            p *= fe[i].first;
          }
        }

        if (p <= j && dp[js][j - p].first != inf) {
          ull this_ans = 1 + dp[js][j - p].first;
          if (this_ans < best) {
            best = this_ans;
            best_js = js;
            best_p = p;
          }
        }
      }
      dp[is][j] = {best, {best_js, best_p}};
    }
  }

  auto [n_ans, y_p] = dp.last()[41];
  vu ans;
  ull rest = 41;
  while (!y_p.first.empty()) {
    ans.push_back(y_p.second);
    ull next_rest = rest - y_p.second;
    y_p = dp[y_p.first][rest - y_p.second].second;
    rest = next_rest;
  }
  assert(n_ans == ans.size());

  return ans;
}


optional<vu> solve1(ull P) {
  if (P == 1) {
    vu ans(41, 1);
    return ans;
  }
  auto factors = factor(P);
  sort(factors.rbegin(), factors.rend());

  ull sum = 0;
  for (auto factor : factors) {
    sum += factor;
  }


  if (sum == 41) {
    return factors;
  } if (sum < 41) {
    vuu fe;
    for (auto f : factors) {
      if (fe.size() > 0 && fe.back().first == f) {
        fe.back().second++;
      } else {
        fe.push_back({f, 1});
      }
    }
    vu ans = calc(fe);
    return ans;
  } else {
    return {};
  }
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull P;
    cin >> P;

    auto ans = solve1(P);
    if (!ans.has_value()) {
      cout << "Case #" << i + 1 << ": " << "-1" << '\n';
    } else {
      cout << "Case #" << i + 1 << ": " << (*ans).size() << ' ';
      for (auto factor : *ans) {
        cout << factor << ' ';
      }
      cout << '\n';
    }
  }

  return EXIT_SUCCESS;
}
