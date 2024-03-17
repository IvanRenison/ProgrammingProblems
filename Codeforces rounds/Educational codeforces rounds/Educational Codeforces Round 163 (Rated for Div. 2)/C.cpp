// https://codeforces.com/contest/1948/problem/C

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
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;
typedef tuple<ll, ll, ll, ll> iiii;
typedef vector<iiii> viiii;
typedef tuple<ll, ll, ll, ll, ll> iiiii;
typedef vector<iiiii> viiiii;
typedef long double ld;
typedef vector<ld> vd;
typedef pair<ld, ld> dd;
typedef vector<dd> vdd;
typedef tuple<ld, ld, ld> ddd;
typedef vector<ddd> vddd;
typedef tuple<ld, ld, ld, ld> dddd;
typedef vector<dddd> vdddd;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;
const ld eps = 1e-7;


bool solve1(const vector<string>& ss) {
  ull n = ss[0].size();

  vector<vb> vis(2, vb(n, false));
  queue<uu> q;

  q.push({0,0});
  vis[0][0] = true;

  while (!q.empty()) {
    auto [i, j] = q.front();
    q.pop();

    if (i == 1 && j == n - 1) {
      return true;
    }

    vuu neight;

    if (i > 0) {
      ull i_ = i - 1, j_ = j;
      if (ss[i_][j_] == '<') {
        j_--;
      } else {
        j_++;
      }
      neight.push_back({i_, j_});
    }
    if (i < 1) {
      ull i_ = i + 1, j_ = j;
      if (ss[i_][j_] == '<') {
        j_--;
      } else {
        j_++;
      }
      neight.push_back({i_, j_});
    }
    if (j > 0) {
      ull i_ = i, j_ = j - 1;
      if (ss[i_][j_] == '<') {
        j_--;
      } else {
        j_++;
      }
      neight.push_back({i_, j_});
    }
    if (j < n - 1) {
      ull i_ = i, j_ = j + 1;
      if (ss[i_][j_] == '<') {
        j_--;
      } else {
        j_++;
      }
      neight.push_back({i_, j_});
    }

    for (auto [i, j] : neight) {
      if (!vis[i][j]) {
        vis[i][j] = true;
        q.push({i, j});
      }
    }
  }

  return false;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;
    vector<string> ss(2);
    for (string& s : ss) {
      cin >> s;
    }

    bool ans = solve1(ss);
    if (ans) {
      cout << "Yes\n";
    } else {
      cout << "No\n";
    }
  }

  return EXIT_SUCCESS;
}
