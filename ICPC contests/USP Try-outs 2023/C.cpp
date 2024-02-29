// https://codeforces.com/gym/104505/problem/C

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()
#define sz(x) (x).size()

const ull inf = 1ull << 60;

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
  H operator+(H o) const { return x + o.x + (x + o.x < x); }
  H operator-(H o) const { return *this + ~o.x; }
  H operator*(H o) const { auto m = (__uint128_t)x * o.x;
    return H((ull)m) + (ull)(m >> 64); }
  ull get() const { return x + !~x; }
  bool operator==(H o) const { return get() == o.get(); }
  bool operator<(H o) const { return get() < o.get(); }
};
static const H C = (ll)1e11+3; // (order ~ 3e9; random also ok)

struct HashInterval {
  vector<H> ha, pw;
  HashInterval(const string& str) : ha(sz(str)+1), pw(ha) {
    pw[0] = 1;
    fore(i,0,sz(str))
      ha[i+1] = ha[i] * C + str[i],
      pw[i+1] = pw[i] * C;
  }
  H hashInterval(int a, int b) const { // hash [a, b)
    return ha[b] - ha[a] * pw[b - a];
  }
};

struct HashIntervalRev {
  HashInterval hi;
  ull n;
  HashIntervalRev(const string& str) : hi(""), n(str.size()) {
    string str_rev = str;
    reverse(all(str_rev));
    hi = HashInterval(str_rev);
  }
  H hashInterval(int a, int b) const { // reverse hash of [a, b)
    return hi.hashInterval(n - b, n - a);
  }
};


ull oddQuasiPalindromes(const HashInterval& h, const HashIntervalRev& h_rev, ull i) {
  ull n = h.ha.size() - 1;

  ull l = 1, r = min(i + 1, n - i) + 1;

  // l  → lower, r → upper
  while (l + 1 < r) {
    ull m = (l + r) / 2;
    if (h.hashInterval(i - m + 1, i + 1) != h_rev.hashInterval(i, i + m)) {
      r = m;
    } else {
      l = m;
    }
  }

  ull pal = l;

  if (pal == min(i + 1, n - i)) {
    return pal;
  } else if (pal + 1 == min(i + 1, n - i)) {
    return pal + 1;
  }

  l = pal + 1, r = min(i + 1, n - i) + 1;

  // l  → lower, r → upper
  while (l + 1 < r) {
    ull m = (l + r) / 2;
    if (h.hashInterval(i - m + 1, i - pal) != h_rev.hashInterval(i + pal + 1, i + m)) {
      r = m;
    } else {
      l = m;
    }
  }

  ull ans = l;

  return ans;
}

/* ull oddQuasiPalindromesForce(const string& s, ull i) {
  ull n = s.size();

  ull r = min(i + 1, n - i) + 1;

  ull diffs = 0;
  fore(j, 0, r) {
    if (s[i - j] != s[i + j]) {
      if (diffs == 0) {
        diffs++;
      } else {
        return j;
      }
    }
  }

  return r - 1;
} */

ull evenQuasiPalindromes(const HashInterval& h, const HashIntervalRev& h_rev, ull i) {
  ull n = h.ha.size() - 1;

  ull l = 0, r = min(i + 1, n - i - 1) + 1;

  // l  → lower, r → upper
  while (l + 1 < r) {
    ull m = (l + r) / 2;
    if (h.hashInterval(i + 1 - m, i + 1) != h_rev.hashInterval(i + 1, i + 1 + m)) {
      r = m;
    } else {
      l = m;
    }
  }

  if (l == min(i + 1, n - i - 1)) {
    return l;
  } else if (l + 1 == min(i + 1, n - i - 1)) {
    return l + 1;
  }

  ull pal = l;

  l = pal + 1, r = min(i + 1, n - i - 1) + 1;

  // l  → lower, r → upper
  while (l + 1 < r) {
    ull m = (l + r) / 2;
    if (h.hashInterval(i + 1 - m, i - pal) != h_rev.hashInterval(i + pal + 2, i + 1 + m)) {
      r = m;
    } else {
      l = m;
    }
  }

  ull ans = l;

  return ans;
}

/* ull evenQuasiPalindromesForce(const string& s, ull i) {
  ull n = s.size();

  ull r = min(i + 1, n - i - 1) + 1;

  ull diffs = 0;
  fore(j, 0, r) {
    if (s[i - j] != s[i + 1 + j]) {
      if (diffs == 0) {
        diffs++;
      } else {
        return j;
      }
    }
  }

  return r - 1;
} */

ull solve(const string& s) {
  ull n = s.size();

  string s_rev = s;
  reverse(all(s_rev));

  HashInterval h(s);
  HashIntervalRev h_rev(s);

  ull ans = 0;

  fore(i, 0, n) {
    ull this_ans = oddQuasiPalindromes(h, h_rev, i);
    //ull force_ans = oddQuasiPalindromesForce(s, i);
    //assert(this_ans == force_ans);
    ans += this_ans;
  }

  fore(i, 0, n - 1) {
    ull this_ans = evenQuasiPalindromes(h, h_rev, i);
    //ull force_ans = evenQuasiPalindromesForce(s, i);
    //assert(this_ans == force_ans);
    ans += this_ans;
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull n;
  string s;
  cin >> n >> s;

  auto ans = solve(s);
  cout << ans << '\n';

/*   fore(n, 1, 20) {
    fore(_, 0, 1000) {
      string s;
      fore(i, 0, n) {
        s.push_back('a' + rand() % 10);
      }

      solve(s);
    }
  } */

  return EXIT_SUCCESS;
}
