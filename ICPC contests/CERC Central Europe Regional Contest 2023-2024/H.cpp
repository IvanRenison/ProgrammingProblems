// https://codeforces.com/gym/104871/problem/H

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef tuple<ull, ull, ull> uuu;
typedef vector<uuu> vuuu;
typedef tuple<ull, ull, ull, ull> uuuu;
typedef vector<uuuu> vuuuu;
typedef tuple<ull, ull, ull, ull, ull> uuuuu;
typedef vector<uuuuu> vuuuuu;
typedef vector<bool> vb;
typedef vector<string> vs;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()
#define sz(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;

pair<vs, vb> ENCODE(const vector<pair<string, vs>>& tree) {

  map<string, vs> tree_map;
  for (auto& [w, children] : tree) {
    tree_map[w] = children;
  }

  vs list;
  vb bits;

  function<void(const string, bool)> dfs = [&](const string w, bool last) {
    list.push_back(w);
    if (tree_map.count(w) == 0) {
      bits.push_back(0);
      bits.push_back(0);
    } else {
      if (last) {
        bits.push_back(1);
        bits.push_back(1);
      } else {
        bits.push_back(0);
        bits.push_back(1);
      }
      fore(i, 0, tree_map[w].size()) {
        string c = tree_map[w][i];
        dfs(c, i == tree_map[w].size() - 1);
      }
      if (!last) {
        bits.push_back(1);
        bits.push_back(0);
      }
    }
  };

  dfs(tree[0].first, true);

  assert(bits.size() <= 2048);
  assert(bits.size() % 2 == 0);

  return {list, bits};
}

vector<pair<string, vs>> DECODE(const vs& list, const vb& bits) {

  vector<pair<string, vs>> tree = {{list[0], {}}};

  vu s;
  ull i = 1, j = 1, k = 0;
  while (i < list.size() && j < bits.size() / 2) {
    ull b = 2 * bits[2 * j] + bits[2 * j + 1];
    if (b == 0b10) {
      assert(!s.empty());
      k = s.back();
      s.pop_back();
    } else {
      string w = list[i];
      tree[k].second.push_back(w);
      if (b == 0b11) {
        tree.push_back({w, {}});
        k = tree.size() - 1;
      } else if (b == 0b01) {
        tree.push_back({w, {}});
        s.push_back(k);
        k = tree.size() - 1;
      } else {
        assert(b == 0b00);
      }
      i++;
    }
    j++;
  }

  return tree;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  string s;
  cin >> s;
  if (s[0] == 'E') {
    vector<pair<string, vs>> tree;
    while (true) {
      if (cin.eof()) {
        break;
      }
      string w;
      cin >> w;
      if (w.empty()) {
        break;
      }
      if (w.back() == ':') {
        w.pop_back();
        tree.push_back({w, {}});
      } else {
        tree.back().second.push_back(w);
      }
    }
    auto [list, bits] = ENCODE(tree);
    for (string& w : list) {
      cout << w << '\n';
    }
    for (bool b : bits) {
      cout << b;
    }
    cout << '\n';
  } else {
    vs list;
    vb bits;
    while (true) {
      if (cin.eof()) {
        break;
      }
      string w;
      cin >> w;
      if (w.empty()) {
        break;
      }
      if (w[0] == '0' || w[0] == '1') {
        for (char c : w) {
          bits.push_back(c == '1');
        }
        break;
      } else {
        list.push_back(w);
      }
    }
    auto tree = DECODE(list, bits);
    for (auto& [w, children] : tree) {
      cout << w << ':';
      for (string& c : children) {
        cout << ' ' << c;
      }
      cout << '\n';
    }
  }

  return EXIT_SUCCESS;
}
