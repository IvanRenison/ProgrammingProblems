// https://codeforces.com/gym/100553

#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef long long ll;
typedef vector<ll> vi;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;

struct Graph;
struct List;
using Number = ull;
struct Range;
using Variable = char;
struct Numvar;

bool isGraphChar(char c) {
  return c == 'c' || c == 'l' || c == 't';
}
bool isNumberChar(char c) {
  return c >= '1' && c <= '9';
}
bool isRangeChar(char c) {
  return c == 'r';
}
bool isVariableChar(char c) {
  return c >= 'A' && c <= 'Z';
}
bool isNumvarChar(char c) {
  return isNumberChar(c) || isVariableChar(c);
}
bool isListChar(char c) {
  return isGraphChar(c) || isNumberChar(c) || isRangeChar(c) || isVariableChar(c);
}

struct Graph {
  enum TY {C, LOOP, T};

  TY ty;

  List* l;
};

struct List {
  enum TY {NONE, NUMBER, RANGE, VARIABLE};
  TY ty;

  vector<Graph*> gs;

  Number* n;
  Range* r;
  Variable* v;

  Graph* g;
};

struct Range {
  Variable* v;
  Numvar* nv0, * nv1;
};

struct Numvar {
  enum TY {NUMBER, VARIABLE};
  TY ty;

  Number* n;
  Variable* v;
};


List* parse_list(ull&, const string&);
Graph* parse_graph(ull&, const string&);
Number* parse_number(ull&, const string&);
Range* parse_range(ull&, const string&);
Variable* parse_variable(ull&, const string&);
Numvar* parse_numvar(ull&, const string&);

Graph* parse_graph(ull& i, const string& s) {
  ull n = s.size();
  assert(i < n);

  char c = s[i];
  assert(isGraphChar(c));
  i++;
  if (c == 'c') {
    if (i == n || s[i] != '(') {
      return new Graph{Graph::C, nullptr};
    } else {
      i++;
      List* l = parse_list(i, s);
      i++;
      return new Graph{Graph::C, l};
    }
  } else if (c == 'l') {
    i += 4;
    List* l = parse_list(i, s);
    i++;
    return new Graph{Graph::LOOP, l};
  } else {
    i++;
    List* l = parse_list(i, s);
    i++;
    return new Graph{Graph::T, l};
  }
}

List* parse_list(ull& i, const string& s) {
  ull n = s.size();
  assert(i < n);

  char c = s[i];
  if (isGraphChar(c)) {
    vector<Graph*> gs;
    while (true) {
      Graph* g = parse_graph(i, s);
      gs.push_back(g);
      if (i == n || s[i] != ',') {
        return new List{List::NONE, gs, nullptr, nullptr, nullptr, nullptr};
      }
      i++;
    }
  } else if (isNumberChar(c)) {
    Number* num = parse_number(i, s);
    if (i == n || s[i] != ',') {
      return new List{List::NUMBER, {}, num, nullptr, nullptr, nullptr};
    } else {
      i++;
      assert(isGraphChar(s[i]));
      Graph* g = parse_graph(i, s);
      return new List{List::NUMBER, {}, num, nullptr, nullptr, g};
    }
  } else if (isRangeChar(c)) {
    Range* r = parse_range(i, s);
    if (i == n || s[i] != ',') {
      return new List{List::RANGE, {}, nullptr, r, nullptr, nullptr};
    } else {
      i++;
      assert(isGraphChar(s[i]));
      Graph* g = parse_graph(i, s);
      return new List{List::RANGE, {}, nullptr, r, nullptr, g};
    }
  } else {
    assert(isVariableChar(c));
    Variable* v = parse_variable(i, s);
    if (i == n || s[i] != ',') {
      return new List{List::VARIABLE, {}, nullptr, nullptr, v, nullptr};
    } else {
      i++;
      assert(isGraphChar(s[i]));
      Graph* g = parse_graph(i, s);
      return new List{List::VARIABLE, {}, nullptr, nullptr, v, g};
    }
  }
}

Number* parse_number(ull& i, const string& s) {
  ull n = s.size();
  assert(i < n);

  char c = s[i];
  assert(isNumberChar(c));
  ull j = 1;
  while (i + j < n && '0' <= s[i + j] && s[i + j] <= '9') {
    j++;
  }
  Number* num = new Number{stoull(s.substr(i, j))};
  i += j;
  return num;
}

Range* parse_range(ull& i, const string& s) {
  ull n = s.size();
  assert(i < n);

  char c = s[i];
  assert(isRangeChar(c));
  i += 6;
  Variable* v = parse_variable(i, s);
  assert(s[i] == ',');
  i++;
  Numvar* nv0 = parse_numvar(i, s);
  assert(s[i] == ',');
  i++;
  Numvar* nv1 = parse_numvar(i, s);
  assert(s[i] == ')');
  i++;
  return new Range{v, nv0, nv1};
}

Variable* parse_variable(ull& i, const string& s) {
  ull n = s.size();
  assert(i < n);

  char c = s[i];
  assert(isVariableChar(c));
  i++;
  return new Variable{c};
}

Numvar* parse_numvar(ull& i, const string& s) {
  ull n = s.size();
  assert(i < n);

  char c = s[i];
  if (isNumberChar(c)) {
    Number* num = parse_number(i, s);
    return new Numvar{Numvar::NUMBER, num, nullptr};
  } else {
    assert(isVariableChar(c));
    Variable* v = parse_variable(i, s);
    return new Numvar{Numvar::VARIABLE, nullptr, v};
  }
}

void swap(vuu& edges, ull u, ull v) {
  for (auto& [i, j] : edges) {
    if (i == u) i = v;
    else if (i == v) i = u;
    if (j == u) j = v;
    else if (j == v) j = u;
  }
}

ull getNumvar(Numvar* nv, map<Variable, vu>& context) {
  if (nv->ty == Numvar::NUMBER) {
    return *nv->n;
  } else {
    return context[*nv->v].back();
  }
}

vector<pair<ull, vuu>> get_edges(List*, map<Variable, vu>&);

pair<ull, vuu> get_edges(Graph* g, map<Variable, vu>& context) { // Get n and edges
  if (g == nullptr) {
    return {2, {{0, 1}}};
  }
  if (g->ty == Graph::C) {
    if (g->l == nullptr) {
      return {2, {{0, 1}}};
    } else {
      vector<pair<ull, vuu>> edgess = get_edges(g->l, context);
      auto [n, edges] = edgess[0];
      fore(i, 1, edgess.size()) {
        auto& [n_, edges_] = edgess[i];
        for (auto [u, v] : edges_) {
          edges.push_back({u + n - 1, v + n - 1});
        }
        n += n_ - 1;
      }
      return {n, edges};
    }
  } else if (g->ty == Graph::LOOP) {
    assert(g->l != nullptr);
    vector<pair<ull, vuu>> edgess = get_edges(g->l, context);
    assert(edgess.size() > 1);
    auto [n, edges] = edgess[0];
    ull last = n - 1;
    fore(i, 1, edgess.size()) {
      auto& [n_, edges_] = edgess[i];
      for (auto [u, v] : edges_) {
        edges.push_back({u + n - 1, v + n - 1});
      }
      n += n_ - 1;
    }
    n--;
    swap(edges, last, n - 1);
    for (auto& [u, v] : edges) {
      if (u == n) u = 0;
      if (v == n) v = 0;
    }
    return {n, edges};
  } else {
    assert(g->ty == Graph::T);
    assert(g->l != nullptr);
    vector<pair<ull, vuu>> edgess = get_edges(g->l, context);
    auto [n, edges] = edgess[0];
    ull last = n - 1;
    fore(i, 1, edgess.size()) {
      auto& [n_, edges_] = edgess[i];
      for (auto [u, v] : edges_) {
        edges.push_back({(u > 0) * (u + n - 1), (v > 0) * (v + n - 1)});
      }
      n += n_ - 1;
    }
    swap(edges, last, n - 1);
    return {n, edges};
  }
}

vector<pair<ull, vuu>> get_edges(List* l, map<Variable, vu>& context) {
  if (l->ty == List::NONE) {
    vector<pair<ull, vuu>> ans;
    for (Graph* g : l->gs) {
      ans.push_back(get_edges(g, context));
    }
    return ans;
  } else if (l->ty == List::NUMBER) {
    auto [n, edges] = get_edges(l->g, context);
    vector<pair<ull, vuu>> ans;
    fore(_, 0, *l->n) {
      ans.push_back({n, edges});
    }
    return ans;
  } else if (l->ty == List::RANGE) {
    ull n0 = getNumvar(l->r->nv0, context);
    ull n1 = getNumvar(l->r->nv1, context);
    vector<pair<ull, vuu>> ans;
    if (n1 < n0) swap(n0, n1);
    fore(i, n0, n1 + 1) {
      context[*l->r->v].push_back(i);
      ans.push_back(get_edges(l->g, context));
      context[*l->r->v].pop_back();
    }
    return ans;
  } else {
    assert(l->ty == List::VARIABLE);
    auto [n, edges] = get_edges(l->g, context);
    vector<pair<ull, vuu>> ans;
    fore(_, 0, context[*l->v].back()) {
      ans.push_back({n, edges});
    }
    return ans;
  }
}

/** Author: Simon Lindholm
 * Date: 2019-12-31
 * License: CC0
 * Source: folklore
 * Description: Eulerian undirected/directed path/cycle algorithm.
 * Input should be a vector of (dest, global edge index), where
 * for undirected graphs, forward/backward edges have the same index.
 * Returns a list of nodes in the Eulerian path/cycle with src at both start and end, or
 * empty list if no cycle/path exists.
 * To get edge indices back, add .snd to s and ret.
 * Time: O(V + E)
 * Status: stress-tested
 */
vu eulerWalk(vector<vuu>& gr, ull nedges, ull src=0) {
  ull n = SZ(gr);
  vi D(n), its(n), eu(nedges), ret, s = {(ll)src};
  D[src]++; // to allow Euler paths, not just cycles
  while (!s.empty()) {
    ll x = s.back(), &it = its[x], end = SZ(gr[x]);
    if (it == end) { ret.push_back(x), s.pop_back(); continue; }
    auto [y, e] = gr[x][it++];
    if (!eu[e]) D[x]--, D[y]++, eu[e] = 1, s.push_back(y);
  }
  for (ll x : D) if (x < 0 || SZ(ret) != nedges+1) return {};
  return {ret.rbegin(), ret.rend()};
}

vector<vu> solve(ull n, vuu& edges) {
  ull m = edges.size();

  set<uu> edges_set;
  vector<vuu> adj(n);
  fore(e, 0, m) {
    auto [u, v] = edges[e];
    adj[u].push_back({v, e});
    adj[v].push_back({u, e});
    edges_set.insert(minmax(u, v));
  }

  vu odd_degs;
  fore(u, 0, n) {
    if (adj[u].size() % 2 == 1) {
      odd_degs.push_back(u);
    }
  }

  assert(odd_degs.size() % 2 == 0);
  set<uu> extra_edges;

  while (!odd_degs.empty()) {
    ull u = odd_degs.back();
    odd_degs.pop_back();

    vu s;
    ull v = odd_degs.back();
    while (edges_set.count(minmax(u, v))) {
      odd_degs.pop_back();
      s.push_back(v);
      if (odd_degs.empty()) {
        v = inf;
        s.pop_back();
        break;
      }
      v = odd_degs.back();
    }
    if (v != inf) {
      odd_degs.pop_back();
    }
    odd_degs.insert(odd_degs.end(), s.rbegin(), s.rend());

    if (v != inf) {
      extra_edges.insert(minmax(u, v));
    }
  }

  ull m2 = 0;
  for (auto [u, v] : extra_edges) {
    adj[u].push_back({v, m + m2});
    adj[v].push_back({u, m + m2});
    m2++;
  }

  ull src = 0;
  fore(u, 0, n) {
    if (adj[u].size() % 2 == 1) {
      src = u;
      break;
    }
  }

  vu path = eulerWalk(adj, m + m2, src);
  assert(path.size() == m + m2 + 1);

  if (path[0] == path.back() && !extra_edges.empty()) {
    vu s;
    while (true) {
      ull u = path.back();
      s.push_back(u);
      path.pop_back();
      if (extra_edges.count(minmax(u, path.back()))) {
        break;
      }
    }
    reverse(ALL(s));
    s.pop_back();
    s.insert(s.end(), ALL(path));
    path = s;
  }

  vector<vu> ans = {{}};

  fore(i, 0, path.size() - 1) {
    ull u = path[i], v = path[i + 1];
    ans.back().push_back(u);
    if (extra_edges.count(minmax(u, v))) {
      if (ans.back().size() == 1) {
        ans.back().pop_back();
      } else if (ans.back().size() > 1) {
        ans.push_back({});
      }
    }
  }
  { // last
    ull u = path[path.size() - 2], v = path.back();
    if (!extra_edges.count(minmax(u, v))) {
      ans.back().push_back(v);
    }
  }
  if (ans.back().empty()) {
    ans.pop_back();
  }

  return ans;
}

void check(vector<vu>& paths) {
  set<ull> ends;
  for (vu& path : paths) {
    ull u = path[0], v = path.back();
    assert(!ends.count(u));
    assert(!ends.count(v));
    ends.insert(u);
    ends.insert(v);
  }
}

void checkEdges(vuu edges, vector<vu> paths) {
  vuu edges2;
  for (vu& path : paths) {
    ull n = path.size();
    fore(i, 0, n - 1) {
      edges2.push_back({path[i], path[i + 1]});
    }
  }

  for (auto& [u, v] : edges) {
    if (u > v) swap(u, v);
  }
  for (auto& [u, v] : edges2) {
    if (u > v) swap(u, v);
  }


  sort(ALL(edges));
  sort(ALL(edges2));
  for (uu e : edges) {
    auto it = lower_bound(ALL(edges2), e);
    assert(it != edges2.end() && *it == e);
  }
  for (uu e : edges2) {
    auto it = lower_bound(ALL(edges), e);
    assert(it != edges.end() && *it == e);
  }
  assert(edges == edges2);
}

int main(void) {
  ios_base::sync_with_stdio(false), cin.tie(nullptr);
#ifdef ONLINE_JUDGE
  freopen("cactus.in", "r", stdin);
  freopen("cactus.out", "w", stdout);
#endif

  string s;
  getline(cin, s);
  ull i = 0;
  Graph* g = parse_graph(i, s);
  assert(i == s.size());
  map<Variable, vu> context;
  auto [n, edges] = get_edges(g, context);
  // for (auto [u, v] : edges) {
  //   cerr << u + 1 << ' ' << v + 1 << '\n';
  // }
  // cerr << endl;
  vector<vu> paths = solve(n, edges);
  // checkEdges(edges, paths);
  // check(paths);
  cout << n << ' ' << paths.size() << '\n';
  for (vu& path : paths) {
    cout << path.size();
    for (ull u : path) {
      cout << ' ' << u + 1;
    }
    cout << '\n';
  }
}
