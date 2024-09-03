// https://codeforces.com/gym/105321/problem/A
#include <bits/stdc++.h>
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;

vector<vi> gans = {
  {0,1,2},
  {3,4,5},
  {6,7,8},
  {0,3,6},
  {1,4,7},
  {2,5,8},
  {0,4,8},
  {2,4,6}
};

bool gana(ll usado, ll quien, ll x) {
  for (vi ga : gans) {
    ll a = ga[0], b = ga[1], c = ga[2];

    if ((usado & (1 << a)) && (usado & (1 << b)) && (usado & (1 << c))) {
      bool ba = ((quien & (1 << a)) >> a);
      bool bb = ((quien & (1 << b)) >> b);
      bool bc = ((quien & (1 << c)) >> c);
      if (x == ba && ba == bb && bb == bc) {
 /*    fore(i, 0, 9) {
          cerr << (!!(usado & (1 << i)));
        }
        cerr << '\n';
        fore(i, 0, 9) {
          cerr << (!!(quien & (1 << i)));
        }
        cerr << '\n';
        cerr << x << '\n'; */
        return true;
      }
    }
  }

  return false;
}

char solve(const vii& ABs) {

  vector<vector<vi>> dp(1 << 9, vector(1 << 9, vi(2, -1)));
  // dp[usado][quien está][quen le toca]
  // 2 -> empate

  vector<set<ll>> back_adj(9);
  for (auto [A, B] : ABs) {
    back_adj[B].insert(A);
  }

  function<ll(ll, ll, bool)> f = [&](ll usado, ll quien, ll turno) -> ll {
    ll& ans = dp[usado][quien][turno];
    if (ans != -1) {
      return ans;
    }

    bool found_empate = false;
    bool found_move = false;


    fore(i, 0, 9) {
      if (!(usado & (1 << i))) {
        bool valid = true;
        for (ll j : back_adj[i]) {
          if (!(usado & (1 << j))) {
            valid = false;
            break;
          }
        }

        if (valid) {
          found_move = true;
          ll usado_ = usado | (1 << i);
          ll quien_ = quien | ((turno << i));
          if (gana(usado_, quien_, turno)) {
            return ans = 1;
          } else if (usado_ == (1 << 9) - 1) {
            found_empate = true;
          } else {
            ll rec = f(usado_, quien_, !turno);

            if (rec == 0) {
              return ans = 1;
            } else if (rec == 2) {
              found_empate = true;
            }
          }
        }
      }
    }

    if (found_empate || !found_move) {
      return ans = 2;
    }

    return ans = 0;
  };

  ll ans = f(0, 0, 0);

  if (ans == 1) {
    return 'X';
  } else if (ans == 0) {
    return 'O';
  } else {
    return 'E';
  }
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll N;
  cin >> N;
  vii ABs(N);
  for (auto& [A, B] : ABs) {
    cin >> A >> B;
    A--, B--;
  }

  cout << solve(ABs) << '\n';
}
