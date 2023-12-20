// https://codeforces.com/gym/104736/problem/C
#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
typedef unsigned short ushort;
typedef vector<uint> vu;
typedef pair<uint, uint> uu;

#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; i++)

const uint inf = 1 << 30;

struct Tree {
  typedef uu T;
  static constexpr T unit = {inf, 0};
  T f(T a, T b) {
    return {min(a.first, b.first), max(a.second, b.second)};
  }
  vector<T> s; int n;
  Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
  void update(int pos, T val) {
    for (s[pos += n] = val; pos /= 2;)
      s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
  }
  T query(int b, int e) {
    T ra = unit, rb = unit;
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if (b % 2) ra = f(ra, s[b++]);
      if (e % 2) rb = f(s[--e], rb);
    }
    return f(ra, rb);
  }
};

uint solveBigg(uint K, const vu& Cs) {
  uint N = Cs.size();

  vu counts(K);
  for (uint C : Cs) {
    counts[C]++;
  }

  uint min_count = *min_element(counts.begin(), counts.end());

  uint ans = 0;

  for (uint k = min_count * K; k > 0; k -= K) {
    Tree tree(K);
    fore(i, 0, k) {
      uint c = tree.query(Cs[i], Cs[i] + 1).second;
      tree.update(Cs[i], {c + 1, c + 1});
    }

    {
      uu t = tree.query(0, K);
      if (t.first == t.second) {
        ans = k;
        goto next;
      }
    }

    fore(j, k, N) {
      uint i = j - k;

      uint n = Cs[j];
      uint o = Cs[i];

      if (o != n) {
        uint cn = tree.query(n, n + 1).second;
        tree.update(n, {cn + 1, cn + 1});
        uint co = tree.query(o, o + 1).second;
        assert(co > 0);
        tree.update(o, {co - 1, co - 1});

        {
          uu t = tree.query(0, K);
          if (t.first == t.second) {
            ans = k;
            goto next;
          }
        }
      }

    }

  }
  next:;

  return ans;
}

// Arithmetic mod 2^64-1. 2x slower than mod 2^64 and more
// code, but works on evil test data (e.g. Thue-Morse, where
// ABBA... and BAAB... of length 2^10 hash the same mod 2^64).
// "typedef ull H;" instead if you think test data is random,
// or work mod 10^9+7 if the Birthday paradox is not a problem.
typedef uint64_t ull;
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
static const H C = (ull)1e11+3; // (order ~ 3e9; random also ok)

struct HashInterval {
  vector<H> ha, pw;
  HashInterval(vector<ushort>& str) : ha(str.size()+1), pw(ha) {
    pw[0] = 1;
    fore(i,0,str.size())
      ha[i+1] = ha[i] * C + str[i],
      pw[i+1] = pw[i] * C;
  }
  H hashInterval(int a, int b) { // hash [a, b)
    return ha[b] - ha[a] * pw[b - a];
  }
};

vector<H> getHashes(vector<ushort>& str, int length) {
  if (str.size() < length) return {};
  H h = 0, pw = 1;
  fore(i,0,length)
    h = h * C + str[i], pw = pw * C;
  vector<H> ret = {h};
  fore(i,length,str.size()) {
    ret.push_back(h = h * C + str[i] - pw * str[i-length]);
  }
  return ret;
}

H hashString(vector<ushort>& s){H h{}; for(ushort c:s) h=h*C+c;return h;}

bool no0(const vector<ushort>& a) {
  fore(i, 0, a.size()) {
    if (a[i] == 0) {
      return false;
    }
  }
  return true;
}

uint solveSmall(uint K, const vu& Cs) {
  uint N = Cs.size();

  vector<ushort> this_count(K);
  map<H, vu> counts;
  counts[hashString(this_count)].push_back(0);

  fore(i, 0, N) {
    this_count[Cs[i]]++;
    if (no0(this_count)) {
      for (ushort& c : this_count) {
        c--;
      }
    }
    counts[hashString(this_count)].push_back(i + 1);
  }

  uint ans = 0;

  for (auto& [_, v] : counts) {
    ans = max(ans, v.back() - v[0]);
  }

  return ans;
}

uint solve(uint K, const vu& Cs) {
  uint N = Cs.size();

  if (K*K > N * 10) {
    return solveBigg(K, Cs);
  } else {
    return solveSmall(K, Cs);
  }
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  uint N, K;
  cin >> N >> K;
  vu Cs(N);
  for (uint& C : Cs) {
    cin >> C;
    C--;
  }

  auto ans = solve(K, Cs);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
