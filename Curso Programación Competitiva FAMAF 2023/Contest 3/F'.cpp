// https://codeforces.com/group/id8eYTCwzg/contest/442745/problem/F

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fore(i, a, b) for (ull i = a; i < b; i++)

#define MAXN 2000

int uf[MAXN + 1];
void uf_init() {
  memset(uf, -1, sizeof(uf));
}

int uf_find(int x) {
  return uf[x] < 0 ? x : uf[x] = uf_find(uf[x]);
}

bool uf_join(int x, int y) {
  x = uf_find(x);
  y = uf_find(y);
  if (x == y)
    return false;
  if (uf[x] > uf[y])
    swap(x, y);
  uf[x] += uf[y];
  uf[y] = x;
  return true;
}

pair<ll, vector<pair<ull, ull>>> kruskal(vector<pair<ll, pair<int, int>>> es
) { // assumes graph is connected
  sort(es.begin(), es.end());
  uf_init();
  ll r = 0;
  vector<pair<ull, ull>> mst;
  mst.reserve(es.size() - 1);
  fore(i, 0, es.size()) {
    int x = es[i].second.first, y = es[i].second.second;
    if (uf_join(x, y))
      r += es[i].first; // (x,y,c) belongs to mst
    mst.push_back({x, y});
  }
  return {r, mst}; // total cost
}

tuple<ull, vector<ull>, vector<pair<ull, ull>>>
solve(vector<pair<ll, ll>> xys, vector<ull> cs, vector<ull> ks) {
  ull n = xys.size();

  vector<pair<ll, pair<int, int>>> es;
  es.reserve((n + 1) * (n + 1));

  fore(i, 0, n) {
    es.push_back({cs[i], {0, i + 1}});
  }
  fore(i, 0, n) {
    fore(j, i + 1, n) {
      ull c = (abs(xys[i].first - xys[j].first) +
               abs(xys[i].second - xys[j].second)) *
              (ks[i] + ks[j]);
      es.push_back({c, {i + 1, j + 1}});
    }
  }

  auto [cost, mst] = kruskal(es);

  vector<ull> gens;
  vector<pair<ull, ull>> connections;

  for (auto [u, v] : mst) {
    if (u == 0) {
      gens.push_back(v);
    } else if (v == 0) {
      gens.push_back(u);
    } else {
      connections.push_back({u, v});
    }
  }

  return {cost, gens, connections};
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull n;
  cin >> n;

  vector<pair<ll, ll>> xys(n);
  fore(i, 0, n) {
    cin >> xys[i].first >> xys[i].second;
  }

  vector<ull> cs(n);
  fore(i, 0, n) {
    cin >> cs[i];
  }

  vector<ull> ks(n);
  fore(i, 0, n) {
    cin >> ks[i];
  }

  auto [c, vs, abs] = solve(xys, cs, ks);

  cout << c << '\n';
  cout << vs.size() << '\n';
  for (ull v : vs) {
    cout << v << ' ';
  }
  cout << '\n';

  cout << abs.size() << '\n';
  for (auto [a, b] : abs) {
    cout << a << ' ' << b << '\n';
  }

  return EXIT_SUCCESS;
}
