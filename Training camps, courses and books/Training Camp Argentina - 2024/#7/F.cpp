// https://codeforces.com/group/5GNF7zti59/contest/534927/problem/F

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

const ull Nlim = 1e5;

ull random(ull x) {
  static random_device rd;
  static mt19937_64 gen(rd());
  static uniform_int_distribution<ull> dis(0, -1);

  static vu mem(Nlim + 1);
  static vb set(Nlim + 1, false);

  if (set[x]) {
    return mem[x];
  } else {
    set[x] = true;
    return mem[x] = dis(gen);
  }
}

struct H {
  ull x;
  H() : x(0) {}

  void insert(ull y) {
    x += random(y);
  }
  void erase(ull y) {
    x -= random(y);
  }
  bool operator==(H o) const {
    return x == o.x;
  }
  bool empty() {
    return x == 0;
  }
  H operator+(H o) const {
    H res;
    res.x = x + o.x;
    return res;
  }
  H operator-(H o) const {
    H res;
    res.x = x - o.x;
    return res;
  }

};

/* struct H {
  map<ull, ull> x;
  H() {}

  void insert(ull y) {
    x[y]++;
    if (x[y] == 0) {
      x.erase(y);
    }
  }
  void erase(ull y) {
    x[y]--;
    if (x[y] == 0) {
      x.erase(y);
    }
  }
  bool operator==(H o) const {
    return x == o.x;
  }
  bool empty() {
    return x.empty();
  }
  H operator+(H o) const {
    H res = *this;
    for (auto& [k, v] : o.x) {
      res.x[k] += v;
      if (res.x[k] == 0) {
        res.x.erase(k);
      }
    }
    return res;
  }
  H operator-(H o) const {
    H res = *this;
    for (auto& [k, v] : o.x) {
      res.x[k] -= v;
      if (res.x[k] == 0) {
        res.x.erase(k);
      }
    }
    return res;
  }

}; */


ull solve(ull K, const vector<vu>& Ss) {
  ull N = Ss.size(), M = Ss[0].size();

  vector<vector<H>> hashes(M, vector<H>(26));
  fore(j, 0, M) {
    fore(i, 0, N) {
      hashes[j][Ss[i][j]].insert(i);
    }
  }

  H total_hash;
  fore(i, 0, N) {
    fore(_, 0, K) {
      total_hash.insert(i);
    }
  }

  fore(i, 0, N) {
    H this_hash = total_hash;
    fore(_, 0, K) {
      this_hash.erase(i);
    }

    fore(j, 0, M) {
      fore(c, 0, 26) if (c != Ss[i][j]) {
        this_hash = this_hash - hashes[j][c];
      }
    }

    if (this_hash.empty()) {
      return i;
    }
  }

  assert(false);
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ull N, M, K;
  cin >> N >> M >> K;
  vector<vu> Ss(N, vu(M));
  for (vu& s : Ss) {
    string str;
    cin >> str;
    fore(i, 0, M) {
      s[i] = str[i] - 'A';
    }
  }

  ull ans = solve(K, Ss);
  cout << ans + 1 << '\n';

}
