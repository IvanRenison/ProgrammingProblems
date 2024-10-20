// https://www.facebook.com/codingcompetitions/hacker-cup/2024/round-2/problems/A2

/* #ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif */

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


const ull n = 6, m = 7;
const ull nn_pow_m = 823543; // (n+1)**m


pair<vector<vuu>, vector<vuu>> findWins(vector<string>& grid) {

  vector<vuu> conn, firr;

  fore(i, 0, n) { // Horizontales
    fore(j, 0, m - 3) {
      char c = grid[i][j];
      bool valid = true;
      fore(k, 0, 4) {
        if (grid[i][j + k] != c) {
          valid = false;
          break;
        }
      }
      if (valid) {
        if (c == 'F') {
          firr.push_back({{i, j}, {i, j + 1}, {i, j + 2}, {i, j + 3}});
        } else {
          conn.push_back({{i, j}, {i, j + 1}, {i, j + 2}, {i, j + 3}});
        }
      }
    }
  }

  fore(j, 0, m) { // Verticales
    fore(i, 0, n - 3) {
      char c = grid[i][j];
      bool valid = true;
      fore(k, 0, 4) {
        if (grid[i + k][j] != c) {
          valid = false;
          break;
        }
      }
      if (valid) {
        if (c == 'F') {
          firr.push_back({{i, j}, {i + 1, j}, {i + 2, j}, {i + 3, j}});
        } else {
          conn.push_back({{i, j}, {i + 1, j}, {i + 2, j}, {i + 3, j}});
        }
      }
    }
  }

  fore(i, 0, n - 3) { // Diagonales
    fore(j, 0, m - 3) {
      char c = grid[i][j];
      bool valid = true;
      fore(k, 0, 4) {
        if (grid[i + k][j + k] != c) {
          valid = false;
          break;
        }
      }
      if (valid) {
        if (c == 'F') {
          firr.push_back({{i, j}, {i + 1, j + 1}, {i + 2, j + 2}, {i + 3, j + 3}});
        } else {
          conn.push_back({{i, j}, {i + 1, j + 1}, {i + 2, j + 2}, {i + 3, j + 3}});
        }
      }
    }
  }

  fore(i, 0, n - 3) { // Diagonales
    fore(j, 3, m) {
      char c = grid[i][j];
      bool valid = true;
      fore(k, 0, 4) {
        if (grid[i + k][j - k] != c) {
          valid = false;
          break;
        }
      }
      if (valid) {
        if (c == 'F') {
          firr.push_back({{i, j}, {i + 1, j - 1}, {i + 2, j - 2}, {i + 3, j - 3}});
        } else {
          conn.push_back({{i, j}, {i + 1, j - 1}, {i + 2, j - 2}, {i + 3, j - 3}});
        }
      }
    }
  }

  return {conn, firr};
}


typedef array<ull, m> State;

bool has(vector<vuu>& p, State& s) {
  for (vuu& line : p) {
    bool valid = true;
    for (auto [i, j] : line) {
      if (i >= s[j]) {
        valid = false;
        break;
      }
    }
    if (valid) {
      return true;
    }
  }
  return false;
}

State toState(ull x) {
  State s;
  fore(i, 0, m) {
    s[i] = x % (n + 1);
    assert(s[i] <= n);
    x /= (n + 1);
  }
  return s;
}
ull toNum(const State& s) {
  ull x = 0, d = 1;
  fore(i, 0, m) {
    x += s[i] * d;
    d *= (n + 1);
  }
  return x;
}


bool valid(const vector<string>& grid, const State& s) {
  ull count_c = 0, count_f = 0;
  fore(j, 0, m) {
    fore(i, 0, s[j]) {
      if (grid[i][j] == 'C') {
        count_c++;
      } else {
        count_f++;
      }
    }
  }
  ull sum = accumulate(ALL(s), 0ull);

  assert(sum == count_c + count_f);
  return count_c == count_f || count_c == count_f + 1;
}

char add(char x, char p) {
  if (x == 'X' || x == '0') {
    return p;
  }
  if (x == '?' || p == '?') {
    return '?';
  }
  if (x == 'C' && p == 'F') {
    return '?';
  }
  if (x == 'F' && p == 'C') {
    return '?';
  }
  return x;
}

char solve(vector<string>& grid) {

  auto [conn, firr] = findWins(grid);

  vector<char> dp(nn_pow_m, '0');
  fore(x, 0, nn_pow_m) {
    //cerr << x << endl;
    State s = toState(x);

    if (valid(grid, s)) {
      bool has_conn = has(conn, s);
      bool has_firr = has(firr, s);

        if (has_conn && has_firr) {
        dp[x] = '0';
      } else if (has_conn) {
        dp[x] = 'C';
      } else if (has_firr) {
        dp[x] = 'F';
      } else {
        dp[x] = '0';
      }
    }
  }

  fore(x, 1, nn_pow_m) {
    State s = toState(x);

    if (valid(grid, s)) {
      fore(j, 0, m) {
        if (s[j] > 0) {
          s[j]--;
          dp[x] = add(dp[x], dp[toNum(s)]);
          s[j]++;
        }
      }
    }
  }

  assert(dp.back() != 'X');
  return dp.back();
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull t;
  cin >> t;

  fore(tc, 0, t) {
    cout << "Case #" << tc + 1 << ": ";

    vector<string> grid(n);
    fore(i, 0, n) {
      cin >> grid[i];
    }

    reverse(ALL(grid));

    auto ans = solve(grid);
    cout << ans << '\n';
  }

}
