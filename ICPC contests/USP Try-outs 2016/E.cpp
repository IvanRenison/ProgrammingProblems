// https://codeforces.com/gym/101064/problem/E

#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")

using namespace std;

typedef unsigned int uint;
typedef vector<uint> vu;
typedef pair<uint, uint> uu;
typedef vector<uu> vuu;
typedef tuple<uint, uint, uint> uuu;
typedef tuple<uint, uint, uint, uint> uuuu;
typedef tuple<uint, uint, char> uuc;
typedef vector<uuc> vuuc;
typedef tuple<uint, uint, uint, uint, uint> uuuuc;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<bool> vb;

#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()

const uint inf = 1u << 30;

bool isSubStr(const string& s, const string& t) {
  uint n = s.size(), m = t.size();
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

struct AhoCorasick {
  struct vertex {
    vi next, go;
    int p, link;
    char pch;
    vector<int> leaf;
    vertex(int p = -1, char pch = -1) : next(10, -1), go(10, -1), p(p), link(-1), pch(pch) {}
  };
  vector<vertex> t;
  AhoCorasick() {
    t.push_back(vertex());
  }
  void add_string(const string& s, int id) {
    int v = 0;
    for (char c : s) {
      if (t[v].next[c - 'a'] == -1) {
        t[v].next[c - 'a'] = t.size();
        t.push_back(vertex(v, c));
      }
      v = t[v].next[c - 'a'];
    }
    t[v].leaf.push_back(id);
  }
  int get_link(int v) {
    if (t[v].link < 0) {
      if (!v || !t[v].p)
        t[v].link = 0;
      else
        t[v].link = go(get_link(t[v].p), t[v].pch);
    }
    return t[v].link;
  }
  int go(int v, char c) {
    if (t[v].go[c - 'a'] == -1) {
      if (t[v].next[c - 'a'] != -1)
        t[v].go[c - 'a'] = t[v].next[c - 'a'];
      else
        t[v].go[c - 'a'] = v == 0 ? 0 : go(get_link(v), c);
    }
    return t[v].go[c - 'a'];
  }

  vu bits;
  void bits_init() {
    bits = vu(t.size(), -1);
  }
  uint bits_get(uint v) {
    if (bits[v] != -1) {
      return bits[v];
    } else {
      uint ans = 0;
      if (v != 0) {
        ans = bits_get(get_link(v));
        for (uint i : t[v].leaf) {
          ans |= 1u << i;
        }
      }
      bits[v] = ans;
      return ans;
    }
  }
};

string solve(const vector<string>& goods, const vector<string>& bads) {
  uint N = goods.size(), M = bads.size();

  AhoCorasick ac;

  fore(i, 0, N) {
    ac.add_string(goods[i], i);
  }
  fore(i, 0, M) {
    ac.add_string(bads[i], i + N);
  }

  uint ac_size = ac.t.size();
  ac.bits_init();

  queue<uuuuc> q;
  vector<vuuc> prev(ac_size, vuuc(1u << N, {inf, inf, '\0'}));

  q.push({0, 0, inf, inf, '#'});

  uint found_i = inf;

  while (!q.empty()) {
    auto [i, x, i_prev, x_prev, c] = q.front();
    q.pop();

    if (get<2>(prev[i][x]) != '\0') {
      continue;
    }

    prev[i][x] = {i_prev, x_prev, c};

    if (x == (1u << N) - 1) {
      found_i = i;
      break;
    }

    for (char c = 'a'; c <= 'j'; c++) {
      uint j = ac.go(i, c);
      uint y = x | ac.bits_get(j);
      if (y < (1u << N) && get<2>(prev[j][y]) == '\0') {
        q.push({j, y, i, x, c});
      }
    }
  }

  if (found_i == inf) {
    return "";
  }

  string ans;

  uint found_x = (1u << N) - 1;

  while (found_i != inf) {
    auto [i, x, c] = prev[found_i][found_x];
    if (i != inf) {
      ans += c;
    }
    found_i = i;
    found_x = x;
  }

  reverse(all(ans));

  return ans;
}

/* bool isValidAns(
    const string& s, const vector<string>& goods, const vector<string>& bads
) {
  for (const string& b : bads) {
    if (isSubStr(b, s)) {
      return false;
    }
  }

  for (const string& g : goods) {
    if (!isSubStr(g, s)) {
      return false;
    }
  }

  return true;
}

string force(vector<string> goods, vector<string> bads) {
  for (string& b : bads) {
    for (string& g : goods) {
      if (isSubStr(b, g)) {
        return "";
      }
    }
  }

  for (uint n = 1, x = 10;; n++, x *= 10) {
    fore(i, 0, x) {
      string s;
      uint j = i;
      fore(k, 0, n) {
        s += 'a' + j % 10;
        j /= 10;
      }
      if (isValidAns(s, goods, bads)) {
        return s;
      }
    }
  }
} */


int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  uint N, M;
  cin >> N >> M;
  vector<string> goods(N), bads(M);
  for (string& s : goods) {
    cin >> s;
  }
  for (string& s : bads) {
    cin >> s;
  }

  string ans = solve(goods, bads);
  if (ans.size() == 0) {
    cout << "-\n";
  } else {
    cout << ans << '\n';
  }

/*   uint N = 1 + rand() % 2, M = rand() % 3;
  fore(_, 0, 500) {
    vector<string> goods(N);
    fore(i, 0, N) {
      fore(_, 0, 1 + rand() % 2) {
        goods[i] += 'a' + rand() % 10;
      }
    }
    vector<string> bads(M);
    fore(i, 0, M) {
      fore(_, 0, 1 + rand() % 2) {
        bads[i] += 'a' + rand() % 10;
      }
    }

    string ans2 = force(goods, bads);
    string ans = solve(goods, bads);

    if (ans != ans2 && (!isValidAns(ans, goods, bads) || ans.size() != ans2.size())) {
      cerr << "INVALID ANS\n";
      cerr << N << ' ' << M << '\n';
      for (string& s : goods) {
        cerr << s << '\n';
      }
      for (string& s : bads) {
        cerr << s << '\n';
      }
      cerr << "ans: " << ans << '\n';
      cerr << "ans2: " << ans2 << '\n';

      return EXIT_FAILURE;
    }
  } */

  return EXIT_SUCCESS;
}
