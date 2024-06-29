// https://codeforces.com/group/gmV7IkT2pN/contest/531946/problem/J

#include <bits/stdc++.h>
using namespace std;
typedef unsigned int uint;
typedef vector<uint> vu;
typedef tuple<uint, uint, uint> uuu;
typedef vector<uuu> vuuu;
#define fore(i, a, b) for (uint i = a, gmat = b; i < gmat; i++)

const uint inf = 1 << 30;
void floydWarshall(vector<vu>& m) {
  uint n = m.size();
  fore(i,0,n) m[i][i] = min(m[i][i], 0u);
  fore(k,0,n) fore(i,0,n) fore(j,0,n)
    if (m[i][k] != inf && m[k][j] != inf) {
      auto newDist = m[i][k] + m[k][j];
      m[i][j] = min(m[i][j], newDist);
    }
}

optional<pair<uint, vu>> solve(const vu& s, const vu& t, vuuu& changes) {
  uint n = s.size();
  if (n != t.size()) {
    return {};
  }

  vector<vu> mat(26, vu(26, inf));
  fore(i, 0, 26) {
    mat[i][i] = 0;
  }
  for (auto [A, B, W] : changes) {
    mat[A][B] = min(mat[A][B], W);
  }

  floydWarshall(mat);

  vector<vector<vu>> needs(26, vector<vu>(26));
  fore(i, 0, n) {
    uint a = s[i], b = t[i];
    if (a != b) {
      if (a > b) swap(a, b);
      needs[a][b].push_back(i);
    }
  }

  uint ans;
  vu ans_s(n);
  fore(i, 0, n) {
    uint c0 = s[i], c1 = t[i];
    uint cost = inf;
    uint c2 = inf;
    fore(c_, 0, 26) {
      uint this_cost = mat[c0][c_] + mat[c1][c_];
      if (this_cost < cost) {
        cost = this_cost;
        c2 = c_;
      }
    }
    if (cost == inf) {
      return {};
    }
    ans_s[i] = c2;
    ans += cost;
  }

  return {{ans, ans_s}};
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  string s_, t_;
  uint n;
  cin >> s_ >> t_ >> n;

  vu s(s_.size()), t(t_.size());
  fore(i, 0, s_.size()) {
    s[i] = s_[i] - 'a';
  }
  fore(i, 0, t_.size()) {
    t[i] = t_[i] - 'a';
  }

  vuuu changes(n);
  for (auto& [A, B, W] : changes) {
    char c0, c1;
    cin >> c0 >> c1 >> W;
    A = c0 - 'a';
    B = c1 - 'a';
  }

  auto ans = solve(s, t, changes);
  if (ans) {
    auto [ans_val, ans_vu] = *ans;
    cout << ans_val << '\n';
    for (uint a : ans_vu) {
      cout << (char)('a' + a);
    }
    cout << '\n';
  } else {
    cout << "-1\n";
  }
}
