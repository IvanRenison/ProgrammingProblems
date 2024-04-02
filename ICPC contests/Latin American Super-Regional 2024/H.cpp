// https://codeforces.com/gym/105053/problem/H

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef long long ll;
typedef vector<ll> vi;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define rep(i, a, b) for (ll i = a; i < b; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) ((ll)(x).size())

/** Author: chilli
 * License: CC0
 * Description: z[x] computes the length of the longest common prefix of s[i:] and s,
 * except z[0] = 0. (abacaba -> 0010301)
 * Time: O(n)
 * Status: stress-tested
 */
vi Z(const string& S) {
	vi z(SZ(S));
	ll l = 0, r = 0;
	rep(i,1,SZ(S)) {
		z[i] = min(max(r - i, 0ll), z[i - l]);
		while (i + z[i] < SZ(S) && S[i + z[i]] == S[z[i]])
			z[i]++, l = i, r = i + z[i];
	}
	return z;
}

string bestRoot(const string& S) {
  ull n = S.size();

  vi z = Z(S);

  fore(i, 1, n) {
    if (n % i == 0) {
      bool isRoot = true;
      for (ull j = i; j < n; j += i) {
        if (z[j] < i) {
          isRoot = false;
          break;
        }
      }
      if (isRoot) {
        return S.substr(0, i);
      }
    }
  }

  return S;
}

/** Author: Simon Lindholm
 * Date: 2015-03-15
 * License: CC0
 * Source: own work
 * Description: Self-explanatory methods for string hashing.
 * Status: stress-tested
 */
// Arithmetic mod 2^64-1. 2x slower than mod 2^64 and more
// code, but works on evil test data (e.g. Thue-Morse, where
// ABBA... and BAAB... of length 2^10 hash the same mod 2^64).
// "typedef ull H;" instead if you think test data is random,
// or work mod 10^9+7 if the Birthday paradox is not a problem.
struct H {
  ull x; H(ull x=0) : x(x) {}
  H operator+(H o) { return x + o.x + (x + o.x < x); }
  H operator-(H o) { return *this + ~o.x; }
  H operator*(H o) { auto m = (__uint128_t)x * o.x;
    return H((ull)m) + (ull)(m >> 64); }
  ull get() const { return x + !~x; }
  bool operator==(H o) const { return get() == o.get(); }
  bool operator<(H o) const { return get() < o.get(); }
};
static const H C = (ll)1e11+3; // (order ~ 3e9; random also ok)

struct HashInterval {
  vector<H> ha, pw;
  HashInterval(const string& str) : ha(SZ(str)+1), pw(ha) {
    pw[0] = 1;
    rep(i,0,SZ(str))
      ha[i+1] = ha[i] * C + str[i],
      pw[i+1] = pw[i] * C;
  }
  H hashInterval(ll a, ll b) { // hash [a, b)
    return ha[b] - ha[a] * pw[b - a];
  }
};

H hashString(const string& s){H h{}; for(char c:s) h=h*C+c;return h;}


optional<ull> findRotation(const string& S, const string& T) {
  ull n = S.size();
  if (T.size() != n) {
    return {};
  }

  HashInterval SS(S + S);

  H h = hashString(T);

  fore(i, 0, n) {
    if (SS.hashInterval(i, i + n) == h) {
      return i;
    }
  }

  return {};
}



struct oper {
  bool I;
  ull R;
  oper(bool I = false, ull R = 0) : I(I), R(R) {}

  oper comb(ull N, oper o) {
    if (!o.I) {
      return {I, (R + o.R) % N};
    } else {
      return {!I, (N - R + o.R) % N};
    }
  }

  oper inv(ull N, oper o) {
    // ans.comb(o) == *this
    if (o.I) {
      return {!I, (N - R + o.R) % N};
    } else {
      assert(false);
    }
  }

  bool operator<(oper o) const {
    return I < o.I || (I == o.I && R < o.R);
  }
  bool operator==(oper o) const {
    return I == o.I && R == o.R;
  }
};

/*
-- derivation of inv(N, o)

ans.comb(o) == *this

Assuming o.I:
  {!ans.I, (N - ans.R + o.R) % N} = *this

    ans.I = !I

    (N - ans.R + o.R) % N = R
    N - ans.R = (R - o.R + N) % N
    ans.R = (N - R + o.R) % N

*/

optional<oper> nonTrivialFixed(const string& S) {

  string T = S;
  reverse(ALL(T));

  optional<ull> i = findRotation(S, T);

  if (!i.has_value()) {
    return {};
  } else {
    return oper(true, *i);
  }
}

ull solve(string& S, vector<oper>& ops) {
  S = bestRoot(S);

  ull N = S.size();
  for (auto& [_, R] : ops) {
    R %= N;
  }

  map<oper, ull> count = {{oper(), 1}};

  ull ans = 0;

  optional<oper> fixed = nonTrivialFixed(S);

  oper op_count;
  for (oper op : ops) {
    op_count = op_count.comb(N, op);
    ans += count[op_count];
    if (fixed.has_value()) {
      oper opf = op_count.inv(N, *fixed);
      assert(opf.comb(N, *fixed) == op_count);
      ans += count[opf];
    }
    count[op_count] += 1;
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string S;
  cin >> S;

  ull K;
  cin >> K;

  vector<oper> ops(K);
  fore(i, 0, K) {
    char c;
    cin >> c;
    if (c == 'I') {
      ops[i].I = true;
    } else {
      ull D;
      cin >> D;
      if (c == 'R') {
        ops[i].R = D;
      } else {
        ops[i].R = S.size() - D;
      }
    }
  }

  auto ans = solve(S, ops);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
