// https://codeforces.com/gym/104270/problem/F
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((ll)x.size())
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;

bool check(const vector<vi>& ans) {
  if (ans.empty()) {
    return true;
  }
  ll k = ans.size(), n = ans[0].size();

  fore(i, 0, k) {
    fore(j, 0, k) if (i != j) {
      fore(a, 0, n) {
        ll b = ans[i][a];
        fore(c, 0, n) if (c != a && c != b) {
          ll d = ans[i][c];
          if (ans[j][a] == c && ans[j][b] != d) {
            return false;
          }
        }
      }
    }
  }

  return true;
}

vector<vi> force(ll n, ll k) {
  if (n % 2 == 1) {
    return {};
  }

  vector<vi> ans(k, vi(n, -1));

  set<ii> used;

  fore(i, 0, k) {
    fore(j, 0, n) {
      if (ans[i][j] == -1) {
        fore(j1, 0, n) {
          if (j != j1 && ans[i][j1] == -1 && !used.count({j, j1})) {
            ans[i][j] = j1;
            ans[i][j1] = j;
            used.insert({j, j1});
            used.insert({j1, j});
            break;
          }
        }
        if (ans[i][j] == -1) {
          return {};
        }
      }
    }
  }

  return ans;
}

vector<vi> solve(ll n, ll k) {
  if (n % 2 == 1) {
    return {};
  }

  ll p = __builtin_ctzll(n);
  ll q = n / p;

  vector<vi> ans_(1, vi(1));

  fore(i, 0, p) {

    assert(ans_.size() == (1ll << i));

    vector<vi> ans2 = ans_;

    for (vi& xs : ans2) {
      for (ll& x : xs) {
        x += 1ll << i;
      }
    }

    vector<vi> new_ans = ans_;

    fore(j, 0, 1ll << i) {
      new_ans[j].insert(new_ans[j].end(), ALL(ans2[j]));
    }

    fore(j, 0, 1ll << i) {
      new_ans.push_back(ans2[j]);
      new_ans.back().insert(new_ans.back().end(), ALL(ans_[j]));
    }

    ans_ = new_ans;
  }

  if (k >= ans_.size()) {
    return {};
  }

  vector<vi> ans(k, vi(n, -1));

  fore(i, 0, k) {
    fore(j, 0, n) {
      ans[i][j] = ans_[i + 1][j % (1ll << p)] + (j / (1ll << p)) * (1ll << p);
    }
  }

  return ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll T;
  cin >> T;

  while (T--) {
    ll n, k;
    cin >> n >> k;

    vector<vi> ans = solve(n, k);

    if (ans.empty()) {
      cout << "Impossible\n";
    } else {
      fore(i, 0, k) {
        fore(j, 0, n) {
          cout << ans[i][j] + 1;
          if (j + 1 != n) {
            cout << ' ';
          }
        }
        cout << '\n';
      }
    }

  }

//   fore(n, 1, 100) {
// /*     vector<vi> ansn;
//     ll nk = -1; */
//     fore(k, 1, n) {
//       vector<vi> ans = solve(n, k);
//       vector<vi> ans2 = force(n, k);
//       assert(check(ans2));
//       assert(ans == ans2);
// /*       if (!ans2.empty()) {
//         ansn = ans2;
//         nk = k;
//       } */
//     }
// /*     if (nk != -1) {
//       cout << n << ' ' << nk << '\n';
//       for (vi& xs : ansn) {
//         for (ll x : xs) {
//           cout << x << ' ';
//         }
//         cout << '\n';
//       }
//       cout << "-----------------------------" << endl;
//     } */
//   }

}
/*
 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
 1  0  3  2  5  4  7  6  9  8 11 10 13 12 15 14
 2  3  0  1  6  7  4  5 10 11  8  9 14 15 12 13
 3  2  1  0  7  6  5  4 11 10  9  8 15 14 13 12
 4  5  6  7  0  1  2  3 12 13 14 15  8  9 10 11
 5  4  7  6  1  0  3  2 13 12 15 14  9  8 11 10
 6  7  4  5  2  3  0  1 14 15 12 13 10 11  8  9
 7  6  5  4  3  2  1  0 15 14 13 12 11 10  9  8
 8  9 10 11 12 13 14 15  0  1  2  3  4  5  6  7
 9  8 11 10 13 12 15 14  1  0  3  2  5  4  7  6
10 11  8  9 14 15 12 13  2  3  0  1  6  7  4  5
11 10  9  8 15 14 13 12  3  2  1  0  7  6  5  4
12 13 14 15  8  9 10 11  4  5  6  7  0  1  2  3
13 12 15 14  9  8 11 10  5  4  7  6  1  0  3  2
14 15 12 13 10 11  8  9  6  7  4  5  2  3  0  1
15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
*/