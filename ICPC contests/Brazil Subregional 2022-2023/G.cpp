// https://codeforces.com/gym/103960/problem/G

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef vector<ull> vu;
typedef vector<ll> vi;
#define fore(i, a, b) for (ull i = a; i < b; i++)

const double eps = 1e-9;

typedef ull Vertex;
typedef double Weight;
typedef tuple<Vertex, Vertex> Edge;

struct Graph {
  ull n;
  ull m;
  vector<Edge> edges;
  vector<vector<Vertex>> adj;
  vector<Weight> weights;

  Graph(ull n, vector<Edge> edges, vector<Weight> weights)
      : n(n), m(edges.size()), edges(edges), adj(n), weights(weights) {
    for (auto [u, v] : edges) {
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
  }
};

pair<vector<Weight>, vector<vu>> make_tree(const Graph& g) {
  vector<vu> children;
  vector<Weight> weights;

  fore(i, 0, g.n) {
    if (g.adj[i].size() == 3) {
      vector<bool> visited(g.n, false);
      vu new_ids(g.n);
      ull id = 0;
      children = {{}};
      weights.push_back(g.weights[i]);

      vu s = {i};
      visited[i] = true;
      new_ids[i] = id;
      id++;

      while (!s.empty()) {
        auto u = s.back();
        s.pop_back();

        for (auto v : g.adj[u]) {
          if (!visited[v] && g.adj[v].size() == 3) {
            s.push_back(v);
            visited[v] = true;
            new_ids[v] = id;
            id++;
            children.push_back({});
            children[new_ids[u]].push_back(new_ids[v]);
            weights.push_back(g.weights[v]);
          }
        }
      }

      break;
    }
  }

  return {weights, children};
}

typedef pair<ll, ll> Point;
typedef array<Point, 3> Trian;

double dist(Point p0, Point p1) {
  auto [x0, y0] = p0;
  auto [x1, y1] = p1;

  ll x = x0 - x1;
  ll y = y0 - y1;

  return sqrt((double)(x * x + y * y));
}

Weight area(Trian t) {
  double s0 = dist(t[0], t[1]), s1 = dist(t[1], t[2]), s2 = dist(t[0], t[2]);
  double p = (s0 + s1 + s2) / 2.0;
  return sqrt(p * (p - s0) * (p - s1) * (p - s2));
}

// min included area
// {including i, not including i}
pair<double, double> tree_solve(const vector<Weight>& ws, const vector<vu>& tree, ull i) {
  //assert(ws.size() == tree.size());
  //assert(i < ws.size());

  ull n_suns = tree[i].size();
  vector<pair<double, double>> suns_ans(n_suns);
  fore(j, 0, n_suns) {
    suns_ans[j] = tree_solve(ws, tree, tree[i][j]);
  }

  double ans_including = ws[i];
  fore(j, 0, n_suns) {
    ans_including += min(suns_ans[j].first, suns_ans[j].second);
  }

  double ans_not_including = 0.0;
  fore(j, 0, n_suns) {
    ans_not_including += suns_ans[j].first;
  }

  return {ans_including, ans_not_including};
}

double solve(vector<Trian> ts) {
  ull n = ts.size();

  vector<Edge> edges;
  vector<Weight> weights(n);

  map<pair<Point, Point>, ull> sides;

  fore(i, 0, n) {
    sort(ts[i].begin(), ts[i].end());

    weights[i] = area(ts[i]);

    vector<pair<Point, Point>> ss = {{ts[i][0], ts[i][1]}, {ts[i][1], ts[i][2]}, {ts[i][0], ts[i][2]}};

    for(auto side : ss) {
      if (sides.find(side) != sides.end()) {
        edges.push_back({sides[side], i});
      } else {
        sides[side] = i;
      }
    }
  }

  Graph g(n, edges, weights);

  double border_area = 0.0;
  fore(i, 0, n) {
    if (g.adj[i].size() != 3) {
      border_area += weights[i];
    }
  }

  auto [ws, tree] = make_tree(g);

  if (tree.size() == 0) {
    return border_area;
  }

  auto [ans_including, ans_not_including] = tree_solve(ws, tree, 0);

  return border_area + min(ans_including, ans_not_including);
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  cout << setprecision(1) << fixed;

  ull n;
  cin >> n;
  vector<Trian> ts(n);
  fore(i, 0, n) {
    for (auto& [x, y] : ts[i]) {
      cin >> x >> y;
    }
  }

  auto ans = solve(ts);
  //ans = 1.86;
  //cout << ans << '\n';
  ans += eps;
  cout << (int)ans << '.' << ((int)(ans*10.0 + 0.5)) % 10 << '\n';

  return EXIT_SUCCESS;
}
