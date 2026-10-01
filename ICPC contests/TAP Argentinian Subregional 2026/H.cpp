// https://codeforces.com/gym/106682/problem/H
#include <bits/stdc++.h>
#include <cassert>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ull> vu;
typedef vector<ll> vi;
typedef pair<ull, ull> uu;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(v) v.begin(), v.end()

const ull LIM = 1e8 * 14 + 10;

bitset<LIM> isPrime;
vu eratosthenes() {
	const ull S = (ull)round(sqrt(LIM)), R = LIM / 2;
	vu pr = {2}, sieve(S+1); pr.reserve(ull(LIM/log(LIM)*1.1));
	vector<uu> cp;
	for (ull i = 3; i <= S; i += 2) if (!sieve[i]) {
		cp.push_back({i, i * i / 2});
		for (ull j = i * i; j <= S; j += 2 * i) sieve[j] = 1;
	}
	for (ull L = 1; L <= R; L += S) {
		array<bool, S> block{};
		for (auto &[p, idx] : cp)
			for (ull i=idx; i < S+L; idx = (i+=p)) block[i-L] = 1;
		fore(i,0,min(S, R - L))
			if (!block[i]) pr.push_back((L + i) * 2 + 1);
	}
	for (ull i : pr) isPrime[i] = 1;
	return pr;
}

bool cpri(const vu& v, const vu& c) {
  ull n = v.size();
  vu sums(n);
  fore(i, 0, n) {
    sums[c[i]] += v[i];
  }

  for (ull s : sums) {
    if (isPrime[s]) {
      return true;
    }
  }

  return false;
}

bool ar(const vu& v) {
  ull n = v.size();

  ull sum = accumulate(ALL(v), 0ull);
  if (!isPrime[sum]) {
    return false;
  }

  vector<vu> coloreos = {{0}};

  fore(i, 1, n) {
    vector<vu> new_coloreos;
    for (vu& c : coloreos) {
      ull max_c = *max_element(ALL(c));
      fore(j, 0, max_c + 2) {
        c.push_back(j);
        new_coloreos.push_back(c);
        c.pop_back();
      }
    }
    coloreos = new_coloreos;
  }

  for (vu& c : coloreos) {
    if (!cpri(v, c)) {
      return false;
    }
  }

  return true;
}

bool fast_ar(ull x, ull n) {
  fore(i, 0, n) {
    if (!isPrime[x + 1 + i * x]) {
      return false;
    }
  }
  return true;
}

optional<vu> force(ull n) {
  vector<vu> vs;

  fore(x, 2, 1e8 - 1) {
    if (isPrime[x + 1]) {
      vs.push_back({x + 1});
      fore(i, 1, n) {
        vs.back().push_back(x);
      }
    }
  }

/*   fore(x, 1, 100000) {
    vs.push_back({x});
  }
  fore(i, 1, n) {
    vector<vu> new_vs;
    for (vu& v : vs) {
      v.push_back(v.back());
      new_vs.push_back(v);
      v.back()++;
      new_vs.push_back(v);
    }

    vs = new_vs;
  } */

  /*
    vector<vu> is;
  fore(x, 0, 20) {
    vs.push_back({primes[x]});
    is.push_back({x});
  }
  fore(i, 1, n) {
    vector<vu> new_vs;
    vector<vu> new_is;
    fore(j, 0, vs.size()) {
      vu& v = vs[j];
      vu& ti = is[j];
      ti.push_back(ti.back());
      v.push_back(primes[ti.back()]);
      new_vs.push_back(v);
      new_is.push_back(ti);
      ti.back()++;
      v.back() = primes[ti.back()];
      new_vs.push_back(v);
      new_is.push_back(ti);
    }

    vs = new_vs;
    is = new_is;
  }
  */

  vu ans;
  for (vu& v : vs) {
    if (ar(v))  {
      return v;
    }
    //if (ar(v)) {
    //  for (ull a : ans) {
    //    cerr << a << ' ';
    //  }
    //  cerr << endl;
    //  ans = v;
    //}
  }

  if (ans.size()) {
    return ans;
  }

  return {};
}

vu full_force() {
  fore(x, 2, 1e8) if (isPrime[x]) {
    for (ull d = 2; x + d * 12 < 1e8; d++) {
      bool valid = true;
      fore(i, 0, 12) {
        if (!isPrime[x + d * i]) {
          valid = false;
          break;
        }
      }
      if (valid) {
        return {x, d, d, d, d, d, d, d, d, d, d, d, d};
      }
    }
  }

  return {};
}

optional<vu> solve(ull n) {
  vu ans = {4943, 60060, 60060, 60060, 60060, 60060, 60060, 60060, 60060, 60060, 60060, 60060, 60060};
  while (ans.size() > n) {
    ans.pop_back();
  }
  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  //eratosthenes();

  //fore(p, 2, 100) if (prime[p]) {
  //  fore(q, 2, p + 1) if (prime[q]) {
  //    fore(r, 2, q + 1) if (prime[r]) {
  //      if (prime[p + q + r] && prime[p + q + r + 2]) {
  //        cout << p << ' ' << q << ' ' << r << ' ' << p + q + r << endl;
  //      }
  //    }
  //  }
  //}
  //exit(0);

  //vu as = full_force();
  //for (ull a : as) {
  //  cerr << a << ' ';
  //}
  //cerr << endl;
  //exit(0);

  //fore(i, 1, 13) {
  //  auto ans = force(i);
  //  if (ans) {
  //    for (ull x : *ans) {
  //      cout << x << ' ';
  //    }
  //  } else {
  //    cout << '*';
  //  }
  //  cout << endl;
  //}
  //exit(0);

  ull n;
  cin >> n;
  auto ans = solve(n);
  if (ans) {
    for (ull x : *ans) {
      cout << x << ' ';
    }
  } else {
    cout << '*';
  }
  cout << endl;

}
