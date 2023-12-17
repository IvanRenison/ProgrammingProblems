// https://codeforces.com/contest/1902/problem/E

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
typedef unsigned long long ull;
typedef pair<ull, ull> uu;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()

struct Trie {
  map<char, Trie> children;

  // amount of words that end in this node
  uint countEnds;
  // amount of words that pass through this node
  uint countPass;

  Trie() : countEnds(0), countPass(0) {}

  // Inserts key into trie
  void insert(const string& key) {
    Trie* node = &*this;
    for (char c : key) {
      node->countPass++;
      if (node->children.count(c) == 0) {
        node->children[c] = Trie();
      }
      node = &node->children[c];
    }
    node->countEnds++;
  }

  // Returns true if key presents in trie, else false
  uu search(const string& key) {
    Trie* node = &*this;
    for (char c : key) {
      if (node->children.count(c) == 0) {
        return {0, 0};
      }
      node = &node->children[c];
    }
    return {node->countEnds, node->countPass};
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

    for (const string& s : ss) {
      ull m = s.size();
      Trie* node = &ss_ord;
      fore(i, 0, m) {
        char c = s[m - 1 - i];
        if (node->children.count(c) == 0) {
          break;
        }
        node = &node->children[c];
        ans -= node->countEnds + node->countPass;
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
      ull m = s.size();
      Trie* node = &ss_rev;
      fore(i, 0, m) {
        char c = s[i];
        if (node->children.count(c) == 0) {
          break;
        }
        node = &node->children[c];
        ans -= node->countEnds + node->countPass;
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
