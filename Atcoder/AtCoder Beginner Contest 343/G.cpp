// https://atcoder.jp/contests/abc343/tasks/abc343_g

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define sz(x) (x).size()


/* bool isSubStr(const string& s, const string& t) {
  ull n = s.size(), m = t.size();
  if (n > m) {
    return false;
  }
  fore(i, 0, m - n + 1) {
    if (s == t.substr(i, n)) {
      return true;
    }
  }

  return false;
}

bool isValidAns(const string& s, const vector<string>& goods) {
  for (const string& g : goods) {
    if (!isSubStr(g, s)) {
      return false;
    }
  }

  return true;
}

ull force(const vector<string>& goods) {

  for (ull n = 1, x = 5;; n++, x *= 5) {
    fore(i, 0, x) {
      string s;
      ull j = i;
      fore(k, 0, n) {
        s += 'a' + j % 5;
        j /= 5;
      }
      if (isValidAns(s, goods)) {
        return s.size();
      }
    }
  }
} */

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
static const H C = (ull)1e11+3; // (order ~ 3e9; random also ok)

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
  bool operator==(const HashInterval& o) const {
    ull n = ha.size() - 1, m = o.ha.size() - 1;
    if (n != m) {
      return false;
    }
    return hashInterval(0, n) == o.hashInterval(0, m);
  }
};

bool isSubStr(const HashInterval& H0, const HashInterval& H1) {
  // Check if H0 is substring of H1
  ull n = H1.ha.size() - 1, m = H0.ha.size() - 1;

  if (m > n) {
    return false;
  }

  H h0 = H0.hashInterval(0, m);

  fore(i, 0, n - m + 1) {
    if (H1.hashInterval(i, i + m) == h0) {
      return true;
    }
  }

  return false;
}

ull cntCmn(const HashInterval& H0, const HashInterval& H1) {
  // Size of biggest suffix of H0 that is prefix of H1
  ull n = H0.ha.size() - 1, m = H1.ha.size() - 1;

  ull k = min(n, m);

  for (ull i = k - 1; i > 0; i--) {
    H h0 = H0.hashInterval(n - i, n);
    H h1 = H1.hashInterval(0, i);

    if (h0 == h1) {
      return i;
    }
  }

  return 0;
}



ull solveSimp(const vector<HashInterval>& Hs) {
  // solve if no string is substring of other

  ull N = Hs.size();

  vector<vu> gains(N, vu(N));

  fore(i, 0, N) {
    fore(j, 0, N) {
      if (i != j) {
        gains[i][j] = cntCmn(Hs[i], Hs[j]);
      }
    }
  }

  // Traveling salesman problem

  vector<vu> dp(N, vu(1 << N));
  // dp[i][x] = max gains passing by all nodes in x and end in i

/*   fore(i, 0, N) {
    dp[i][0] = 0;
  } */

  fore(x, 1, 1 << N) {
    fore(i, 0, N) {
      if (!(x & (1 << i))) {

        fore(j, 0, N) {
          if (x & (1 << j)) {
            dp[i][x] = max(dp[i][x], dp[j][x ^ (1 << j)] + gains[j][i]);
          }
        }
      }
    }
  }

  ull total_gain = 0;
  fore(i, 0, N) {
    total_gain = max(total_gain, dp[i][((1 << N) - 1) ^ (1 << i)]);
  }

  ull total_length = 0;
  fore(i, 0, N) {
    total_length += Hs[i].ha.size() - 1;
  }

  return total_length - total_gain;
}


ull solve(const vector<string>& Ss) {
  ull N = Ss.size();

  vector<HashInterval> Hs;
  for (const string& S : Ss) {
    Hs.push_back(HashInterval(S));
  }

  vb valid(N, true);

  fore(i, 0, N) {
    fore(j, i + 1, N) {
      if (Hs[i] == Hs[j]) {
        valid[j] = false;
      }
    }
  }

  fore(i, 0, N) if (valid[i]) {
    fore(j, 0, N) if (valid[j]) {
      if (i != j && isSubStr(Hs[i], Hs[j])) {
        valid[i] = false;
        break;
      }
    }
  }

  vector<HashInterval> goods;
  fore(i, 0, N) {
    if (valid[i]) {
      goods.push_back(Hs[i]);
    }
  }

  ull ans = solveSimp(goods);

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull N;
  cin >> N;
  vector<string> Ss(N);
  for (string& S : Ss) {
    cin >> S;
  }

  auto ans = solve(Ss);
  cout << ans << '\n';

/*   ull N = rand() % 4 + 1;
  fore(_, 0, 10000) {
    vector<string> goods(N);
    fore(i, 0, N) {
      fore(_, 0, 1 + rand() % 3) {
        goods[i] += 'a' + rand() % 5;
      }
    }

    ull ans2 = force(goods);
    ull ans = solve(goods);

    if (ans != ans2) {
      cerr << "INVALID ANS\n";
      cerr << N << '\n';
      for (string& s : goods) {
        cerr << s << '\n';
      }
      cerr << "ans: " << ans << '\n';
      cerr << "ans2: " << ans2 << '\n';

      return EXIT_FAILURE;
    }
  } */

  return EXIT_SUCCESS;
}
