// https://codeforces.com/contest/1902/problem/E

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
typedef unsigned long long ull;
typedef pair<uint, uint> uu;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()

struct Trie {
  struct Node {
    // amount of words that end in this node
    uint countEnds;
    // amount of words that pass through this node
    uint countPass;
    map<char, uint> children;
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

ull solve(const vector<string>& ss) {
  ull n = ss.size();

  ull ans = 0;
  {
    Trie ss_ord;
    fore(i, 0, n) {
      string s = ss[i];
      ans += s.size();
      ss_ord.insert(s);
    }

    ans = ans * 2 * n;

    for (string s : ss) {
      uint i = 0;
      fore (j, 0, s.size()) {
        char c = s[s.size() - 1 - j];
        if (ss_ord.nodes[i].children.count(c) == 0) {
          break;
        }
        i = ss_ord.nodes[i].children[c];
        ans -= ss_ord.nodes[i].countEnds + ss_ord.nodes[i].countPass;
      }
    }
  }

  {
    Trie ss_rev;
    fore(i, 0, n) {
      string s = ss[i];
      reverse(all(s));
      ss_rev.insert(s);
    }

    for (const string& s : ss) {
      uint i = 0;
      for (char c : s) {
        if (ss_rev.nodes[i].children.count(c) == 0) {
          break;
        }
        i = ss_rev.nodes[i].children[c];
        ans -= ss_rev.nodes[i].countEnds + ss_rev.nodes[i].countPass;
      }
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n;
  cin >> n;
  vector<string> ss(n);
  for (string& s : ss) {
    cin >> s;
  }

  auto ans = solve(ss);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
