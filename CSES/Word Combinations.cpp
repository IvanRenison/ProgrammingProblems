// https://cses.fi/problemset/task/1731

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef pair<ull, ull> uu;
typedef long long ll;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

// Based on ModularArithmetic of kactl

ll euclid(ll a, ll b, ll& x, ll& y) {
  if (!b)
    return x = 1, y = 0, a;
  ll d = euclid(b, a % b, y, x);
  return y -= a / b * x, d;
}

constexpr ull mod = (1e9 + 7);
struct Mod {
  ull x;
  Mod(ull xx) : x(xx) {}
  Mod() : x(0) {}
  Mod operator+(Mod b) {
    return Mod((x + b.x) % mod);
  }
  Mod operator-(Mod b) {
    return Mod((x + mod - b.x + mod) % mod);
  }
  Mod operator*(Mod b) {
    return Mod((x * b.x) % mod);
  }
  Mod operator+=(Mod b) {
    return *this = *this + b;
  }
  Mod operator-=(Mod b) {
    return *this = *this - b;
  }
  Mod operator*=(Mod b) {
    return *this = *this * b;
  }
  Mod operator++() {
    return *this = *this + Mod(1);
  }
  Mod operator--() {
    return *this = *this - Mod(1);
  }
  bool operator==(Mod b) {
    return x == b.x;
  }
  bool operator!=(Mod b) {
    return x != b.x;
  }
  bool operator<(Mod b) {
    return x < b.x;
  }
  bool operator>(Mod b) {
    return x > b.x;
  }
  bool operator<=(Mod b) {
    return x <= b.x;
  }
  bool operator>=(Mod b) {
    return x >= b.x;
  }

  Mod invert(Mod a) {
    ll x, y, g = euclid(a.x, mod, x, y);
    assert(g == 1);
    return Mod((x + mod) % mod);
  }
  Mod operator^(ull e) {
    if (!e)
      return Mod(1);
    Mod r = *this ^ (e / 2);
    r = r * r;
    return e & 1 ? *this * r : r;
  }
  Mod operator/(Mod b) {
    return *this * invert(b);
  }
  Mod operator/=(Mod b) {
    return *this = *this / b;
  }

  friend ostream& operator<<(ostream& os, Mod m) {
    os << m.x;
    return os;
  }
  friend istream& operator>>(istream& is, Mod& m) {
    ull x;
    is >> x;
    m = Mod(x);
    return is;
  }

  operator ull() const {
    return x;
  }
  operator ll() const {
    return x;
  }
};

struct Trie {
  struct Node {
    // amount of words that end in this node
    uint countEnds;
    // amount of words that pass through this node
    uint countPass;
    map<char, uint> children; // Use vector for better performance if alphabet is small
  };

  vector<Node> nodes;

  Trie() : nodes(1) {}

  // Inserts key into trie
  void insert(const string& key) {
    uint i = 0;
    for (char c : key) {
      nodes[i].countPass++;
      if (nodes[i].children.count(c) == 0) {
        nodes[i].children[c] = nodes.size();
        nodes.push_back(Node());
      }
      i = nodes[i].children[c];
    }
    nodes[i].countEnds++;
  }

  // Returns (countEnds, countPass) of key
  uu search(const string& key) {
    uint i = 0;
    for (char c : key) {
      if (nodes[i].children.count(c) == 0) {
        return {0, 0};
      }
      i = nodes[i].children[c];
    }
    return {nodes[i].countEnds, nodes[i].countPass};
  }
};


Mod solve(const string& s, const vector<string>& words) {
  ull n = s.size();

  Trie trie;
  for (const string& word : words) {
    trie.insert(word);
  }

  vector<Mod> dp(n + 1, 0);
  dp[0] = 1;

  fore(i, 0, n + 1) {
    uint p = 0;
    fore(k, i + 1, n + 1) {
      char c = s[k - 1];
      if (trie.nodes[p].children.count(c) == 0) {
        break;
      }
      p = trie.nodes[p].children[c];
      dp[k] += dp[i] * Mod(trie.nodes[p].countEnds);
    }
  }

  return dp[n];
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  string s;
  cin >> s;
  ull k;
  cin >> k;
  vector<string> words(k);
  for (string& word : words) {
    cin >> word;
  }

  auto ans = solve(s, words);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
