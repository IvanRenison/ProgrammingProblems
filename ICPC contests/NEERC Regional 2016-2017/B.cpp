// https://codeforces.com/gym/101190

#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

#include <bits/stdc++.h>
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;


/** Author: Emil Lenngren, Simon Lindholm
 * Date: 2011-11-29
 * License: CC0
 * Source: folklore
 * Description: Calculates a valid assignment to boolean variables a, b, c,... to a 2-SAT problem,
 * so that an expression of the type $(a||b)\&\&(!a||c)\&\&(d||!b)\&\&...$
 * becomes true, or reports that it is unsatisfiable.
 * Negated variables are represented by bit-inversions (\texttt{\tilde{}x}).
 * Usage:
 *  TwoSat ts(number of boolean variables);
 *  ts.either(0, \tilde3); // Var 0 is true or var 3 is false
 *  ts.setValue(2); // Var 2 is true
 *  ts.atMostOne({0,\tilde1,2}); // <= 1 of vars 0, \tilde1 and 2 are true
 *  ts.solve(); // Returns true iff it is solvable
 *  ts.values[0..N-1] holds the assigned values to the vars
 * Time: O(N+E), where N is the number of boolean variables, and E is the number of clauses.
 * Status: stress-tested
 */
struct TwoSat {
  ll N;
  vector<vi> gr;
  vi values; // 0 = false, 1 = true

  TwoSat(ll n = 0) : N(n), gr(2*n) {}

  ll addVar() { // (optional)
    gr.push_back({}), gr.push_back({});
    return N++;
  }

  void either(ll f, ll j) {
    if (f == j) return;
    //cerr << f << ' ' << j << '\n';
    f = max(2*f, -1-2*f);
    j = max(2*j, -1-2*j);
    gr[f].push_back(j^1), gr[j].push_back(f^1);
  }
  void setValue(ll x) { either(x, x); }

  void atMostOne(const vi& li) { // (optional)
    if (SZ(li) <= 1) return;
    ll cur = ~li[0];
    fore(i,2,SZ(li)) {
      ll next = addVar();
      either(cur, ~li[i]);
      either(cur, next);
      either(~li[i], next);
      cur = ~next;
    }
    either(cur, ~li[1]);
  }

  vi val, comp, z; ll time = 0;
  ll dfs(ll i) {
    ll low = val[i] = ++time, x; z.push_back(i);
    for(ll e : gr[i]) if (!comp[e])
      low = min(low, val[e] ?: dfs(e));
    if (low == val[i]) do {
      x = z.back(); z.pop_back();
      comp[x] = low;
      if (values[x>>1] == -1)
        values[x>>1] = x&1;
    } while (x != i);
    return val[i] = low;
  }

  bool solve() {
    values.assign(N, -1);
    val.assign(2*N, 0); comp = val;
    fore(i,0,2*N) if (!comp[i]) dfs(i);
    fore(i,0,N) if (comp[2*i] == comp[2*i+1]) return 0;
    return 1;
  }
};

struct Trie {
  struct Node {
    ll depth = 0;
    vi ends;
    array<ll, 2> children = {-1, -1};
  };

  vector<Node> nodes;

  Trie() : nodes(1) {}

  void insert(ll x, const string& key) {
    ll i = 0;
    for (char c : key) {
      if (nodes[i].children[c - '0'] == -1) {
        nodes[i].children[c - '0'] = nodes.size();
        nodes.push_back(Node());
        nodes.back().depth = nodes[i].depth + 1;
      }
      i = nodes[i].children[c - '0'];
    }
    nodes[i].ends.push_back(x);
  }
};

optional<vector<string>> solve(vector<string>& words) {
  ll n = words.size();

  vi poss(n);
  Trie tr;
  fore(i, 0, n) {
    ll& pos = poss[i];
    for (; pos < words[i].size(); pos++) {
      if (words[i][pos] == '?') {
        break;
      }
    }
    if (pos == words[i].size()) {
      tr.insert(i, words[i]);
      tr.insert(~i, words[i]);
    } else {
      words[i][pos] = '0';
      tr.insert(~i, words[i]);
      words[i][pos] = '1';
      tr.insert(i, words[i]);
    }
  }
  ll m = tr.nodes.size();

  TwoSat ts(n + m);
  fore(i, 0, m) {
    if (tr.nodes[i].ends.size() > tr.nodes[i].depth) {
      return {};
    }
    ts.atMostOne(tr.nodes[i].ends);
    fore(c, 0, 2) {
      if (tr.nodes[i].children[c] != -1) {
        ts.either(~(n + i), n + tr.nodes[i].children[c]);
      }
    }
    for (ll x : tr.nodes[i].ends) {
      ts.either(~(n + i), ~x);
      fore(c, 0, 2) {
        if (tr.nodes[i].children[c] != -1) {
          ts.either(~x, n + tr.nodes[i].children[c]);
        }
      }
    }
  }

  if (!ts.solve()) {
    return {};
  }
  fore(i, 0, n) {
    if (poss[i] < words[i].size()) {
      words[i][poss[i]] = '0' + ts.values[i];
    }
  }

  return words;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);
#ifdef ONLINE_JUDGE
  freopen("binary.in", "r", stdin);
  freopen("binary.out", "w", stdout);
#endif

#ifndef TEST
  ll n = 500000;
  cin >> n;
  vector<string> words(n);
  for (string& s : words) {
    cin >> s;
  }
  auto ans = solve(words);
  if (ans) {
    cout << "YES\n";
    for (string& s : *ans) {
      cout << s << '\n';
    }
  } else {
    cout << "NO\n";
  }
#else
  fore(_, 0, 1000000) {
    ll n = rand() % 10 + 1;
    vector<string> words(n);
    for (string& s : words) {
      ll m = rand() % 10 + 1;
      fore(_, 0, m) {
        s += '0' + rand() % 2;
      }
      if (rand() % 2) {
        s[rand() % m] = '?';
      }
    }
    solve(words);
  }
#endif
}
