// https://codeforces.com/gym/102861/problem/C

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define SZ(x) (x).size()

uu force(const vector<string>& A, const vector<string>& B) {
  ull N = A.size(), M = B.size();

  set<string> all;

  for (string s : A) {
    for (string t : B) {
      all.insert(s + t);
    }
  }

  vector<set<string>> allPerA(N), allPerB(M);
  fore(i, 0, N) {
    string s = A[i];
    fore(j, 0, M) {
      string t = B[j];
      allPerA[i].insert(s + t);
      allPerB[j].insert(s + t);
    }
  }

  ull ansA = 0, ansB = 0;

  fore(i, 0, N) {
    set<string> allNow;
    fore(i1, 0, N) if (i1 != i) {
      string s = A[i1];
      for (string t : B) {
        allNow.insert(s + t);
      }
    }

    bool peculiar = true;
    for (string s : allPerA[i]) {
      if (allNow.count(s)) {
        peculiar = false;
        break;
      }
    }

    ansA += peculiar;
  }

  fore(j, 0, M) {
    set<string> allNow;
    fore(j1, 0, M) if (j1 != j) {
      string t = B[j1];
      for (string s : A) {
        allNow.insert(s + t);
      }
    }

    bool peculiar = true;
    for (string t : allPerB[j]) {
      if (allNow.count(t)) {
        peculiar = false;
        break;
      }
    }

    ansB += peculiar;
  }

  return {ansA, ansB};
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
static const H C = (ull)1e11+3; // (order ~ 3e9; random also ok)

struct HashInterval {
  vector<H> ha, pw;
  HashInterval(const string& str) : ha(SZ(str)+1), pw(ha) {
    pw[0] = 1;
    fore(i,0,SZ(str))
      ha[i+1] = ha[i] * C + str[i],
      pw[i+1] = pw[i] * C;
  }
  H hashInterval(ull a, ull b) { // hash [a, b)
    return ha[b] - ha[a] * pw[b - a];
  }
};

uu solve(const vector<string>& A, const vector<string>& B) {
  ull N = A.size(), M = B.size();

  vector<HashInterval> HIA, HIB;
  HIA.reserve(N), HIB.reserve(M);
  fore(i, 0, N) {
    HIA.push_back(HashInterval(A[i]));
  }
  fore(i, 0, M) {
    HIB.push_back(HashInterval(B[i]));
  }

  map<H, vu> hashesA, hashesB;
  fore(i, 0, N) {
    H h = HIA[i].hashInterval(0, A[i].size());
    hashesA[h].push_back(i);
  }
  fore(i, 0, M) {
    H h = HIB[i].hashInterval(0, B[i].size());
    hashesB[h].push_back(i);
  }

  map<H, vuu> prexA, posxB;
  fore(i, 0, N) {
    ull l = A[i].size();
    fore(p, 1, l) {
      H h0 = HIA[i].hashInterval(0, p);
      H h1 = HIA[i].hashInterval(p, l);
      for (ull j : hashesA[h0]) {
        prexA[h1].push_back({i, j});
      }
    }
  }
  fore(i, 0, M) {
    ull l = B[i].size();
    fore(p, 1, l) {
      H h0 = HIB[i].hashInterval(0, p);
      H h1 = HIB[i].hashInterval(p, l);
      for (ull j : hashesB[h1]) {
        posxB[h0].push_back({i, j});
      }
    }
  }

  vb usedA(N, true), usedB(M, true);

  for (auto& [h, v] : prexA) {
    if (posxB.count(h)) {
      for (auto [i, j] : v) {
        usedA[i] = usedA[j] = false;
      }
      for (auto [i, j] : posxB[h]) {
        usedB[i] = usedB[j] = false;
      }
    }
  }

  for (auto& [h, v] : hashesA) {
    if (v.size() > 1) {
      for (ull i : v) {
        usedA[i] = false;
      }
    }
  }
  for (auto& [h, v] : hashesB) {
    if (v.size() > 1) {
      for (ull i : v) {
        usedB[i] = false;
      }
    }
  }

  ull ansA = accumulate(usedA.begin(), usedA.end(), 0ull);
  ull ansB = accumulate(usedB.begin(), usedB.end(), 0ull);

  return {ansA, ansB};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

#ifndef TEST
  ull N, M;
  cin >> N >> M;
  vector<string> A(N), B(M);
  for (string& s : A) {
    cin >> s;
  }
  for (string& s : B) {
    cin >> s;
  }

  auto [a, b] = solve(A, B);
  cout << a << ' ' << b << '\n';
#else
  fore(_, 0, 10000) {
    ull N = rand() % 4 + 1, M = rand() % 4 + 1;
    vector<string> A(N, ""), B(M, "");
    for (string& s : A) {
      ull l = rand() % 3 + 1;
      fore(_, 0, l) {
        s += 'a' + rand() % 5;
      }
    }
    for (string& s : B) {
      ull l = rand() % 3 + 1;
      fore(_, 0, l) {
        s += 'a' + rand() % 5;
      }
    }

    uu ans = solve(A, B);
    uu ansf = force(A, B);
    if (ans != ansf) {
      cerr << "FAIL\n";
      cerr << N << ' ' << M << '\n';
      for (string s : A) {
        cerr << s << ' ';
      }
      cerr << '\n';
      for (string s : B) {
        cerr << s << ' ';
      }
      cerr << '\n';
      cerr << "ans:  " << ans.first << ' ' << ans.second << '\n';
      cerr << "ansf: " << ansf.first << ' ' << ansf.second << '\n';
      return EXIT_FAILURE;
    }
  }
#endif
}
