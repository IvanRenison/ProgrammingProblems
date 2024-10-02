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
typedef vector<bool> vb;

vector<vb> readGrid() {
  ll h, w;
  cin >> h >> w;
  vector<vb> g(h, vb(w));
  fore(i, 0, h) fore(j, 0, w) {
    char c;
    cin >> c;
    g[i][j] = c == '*';
  }
  return g;
}

bool at(vector<vb>& g, ll i, ll j) {
  ll h = g.size(), w = g[0].size();
  if (i < 0 || i >= h || j < 0 || j >= w) return false;
  return g[i][j];
}

bool empty(vector<vb>& g) {
  ll h = g.size(), w = g[0].size();

  fore(i, 0, h) fore(j, 0, w) {
    if (g[i][j]) {
      return false;
    }
  }
  return true;
}

ii first(vector<vb>& g) {
  ll h = g.size(), w = g[0].size();

  fore(i, 0, h) fore(j, 0, w) {
    if (g[i][j]) {
      return {i, j};
    }
  }
  assert(false);
}

ii diff(vector<vb>& g0, vector<vb>& g1) {
  auto [i00, j00] = first(g0);
  auto [i01, j01] = first(g1);
  ll di = i01 - i00, dj = j01 - j00;
  return {di, dj};
}

bool eq(vector<vb>& g0, vector<vb>& g1) {
  bool g0_empty = empty(g0), g1_empty = empty(g1);
  if (g0_empty && g1_empty) return true;
  if (g0_empty || g1_empty) return false;

  ll h0 = g0.size(), w0 = g0[0].size();
  ll h1 = g1.size(), w1 = g1[0].size();
  auto [di, dj] = diff(g0, g1);

  fore(i, 0, h0) fore(j, 0, w0) {
    if (g0[i][j] != at(g1, i + di, j + dj)) {
      return false;
    }
  }
  fore(i, 0, h1) fore(j, 0, w1) {
    if (g1[i][j] != at(g0, i - di, j - dj)) {
      return false;
    }
  }

  return true;
}

tuple<vector<vb>, ll, ll, ll, ll> Xor(vector<vb>& g0, vector<vb>& g1) {
  ll h0 = g0.size(), w0 = g0[0].size();
  ll h1 = g1.size(), w1 = g1[0].size();
  auto [di, dj] = diff(g0, g1);

  vector<vb> ans(di > 0 ? max(h1, di + h0) : max(h0, -di + h1), vb(dj > 0 ? max(w1, dj + w0) : max(w0, -dj + w1)));

  ll di0 = max(0ll, di), dj0 = max(0ll, dj);
  ll di1 = max(0ll, -di), dj1 = max(0ll, -dj);

  fore(i, 0, h0) fore(j, 0, w0) {
    ans[i + di0][j + dj0] = g0[i][j];
  }
  fore(i, 0, h1) fore(j, 0, w1) {
    ans[i + di1][j + dj1] = ans[i + di1][j + dj1] ^ g1[i][j];
  }

  return {ans, di0, dj0, di1, dj1};
}

optional<ii> solve(vector<vb>& g0, vector<vb>& g1, vector<vb>& g2) {

  {
    auto [g01, di0, dj0, di1, dj1] = Xor(g0, g1);
    if (eq(g01, g2)) {
      auto [di, dj] = diff(g1, g0);
      return {{di, dj}};
    }
  }

  {
    auto [g02, di0, dj0, di2, dj2] = Xor(g0, g2);
    if (eq(g02, g1)) {
      auto [di_, dj_] = diff(g1, g02);
      return {{di_ - di0, dj_ - dj0}};
    }
  }

  {
    auto [g12, di1, dj1, di2, dj2] = Xor(g1, g2);
    if (eq(g12, g0)) {
      auto [di_, dj_] = diff(g0, g12);
      return {{di1 - di_, dj1 - dj_}};
    }
  }

  return {};
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);
#ifdef ONLINE_JUDGE
  freopen("kids.in", "r", stdin);
  freopen("kids.out", "w", stdout);
#endif
#ifndef TEST
  vector<vb> g0 = readGrid(), g1 = readGrid(), g2 = readGrid();
  auto ans = solve(g0, g1, g2);
  if (ans) {
    cout << "YES\n" << ans->second << ' ' << ans->first << '\n';
  } else {
    cout << "NO\n";
  }
#else
  auto randomGrid = [](ll h, ll w) -> vector<vb> {
    vector<vb> g(h, vb(w));
    fore(i, 0, h) fore(j, 0, w) {
      g[i][j] = rand() % 2;
    }
    g[rand() % h][rand() % w] = '*';
    return g;
  };
  auto printGrid = [](vector<vb>& g) {
    ll h = g.size(), w = g[0].size();
    cout << h << ' ' << w << '\n';
    fore(i, 0, h) {
      fore(j, 0, w) {
        cout << (g[i][j] ? '*' : '.');
      }
      cout << '\n';
    }
  };

  fore(_, 0, 10000) {
    vector<vb>
      g0 = randomGrid(rand() % 5 + 1, rand() % 5 + 1),
      g1 = randomGrid(rand() % 5 + 1, rand() % 5 + 1),
      g2 = randomGrid(rand() % 5 + 1, rand() % 5 + 1);
    printGrid(g0), printGrid(g1), printGrid(g2);
    cout << endl;
    solve(g0, g1, g2);
  }
#endif
}
