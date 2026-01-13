// https://codeforces.com/gym/106193/problem/E
#include <bits/stdc++.h>
#define pb push_back
#define fst first
#define snd second
#define fore(i,a,b) for(ll i=a,renison=b;i<renison;i++)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(),x.end()
#define mset(a,v) memset((a),(v),sizeof(a))
#define FIN ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define imp(v) {for(auto i:v)cout<<i<<" ";cout<<"\n";}
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;

char query(ll x, ll y) {
  cout << "? " << x << ' ' << y << endl;
  char c;
  cin >> c;
  return c;
}

vii vecinos(ll x, ll y) {
  return {
    {x - 1, y - 1}, {x, y - 1}, {x + 1, y - 1},
    {x - 1, y}, {x, y}, {x + 1, y},
    {x - 1, y + 1}, {x, y + 1}, {x + 1, y + 1}
  };
}

pair<char, vii> solve(ll n) {
  set<ii> Bs, Ws, com;

  auto ins = [&](char q, ll x, ll y) {
    if (q == 'B') {
      Bs.insert({x, y});
    } else {
      Ws.insert({x, y});
    }
  };

  auto is_com = [&](ll x, ll y) -> bool {
    if (Bs.count({x, y}) || Ws.count({x, y})) {
      return false;
    }
    bool found_B = false, found_W = false;
    for (auto nxy : vecinos(x, y)) {
      if (Bs.count(nxy)) {
        found_B = true;
      }
      if (Ws.count(nxy)) {
        found_W = true;
      }
    }
    return found_B && found_W;
  };

  char q0 = query(0, 0);
  ins(q0, 0, 0);

  fore(i, 1, n) {
    char qi = query(0, i);
    ins(qi, 0, i);

    if (qi != q0) {
      com.insert({1, i-1});
      com.insert({1, i});
      com.insert({-1, i-1});
      com.insert({-1, i});
      break;
    }
  }

  while (Bs.size() < n && Ws.size() < n) {
    assert(!com.empty());
    assert(!Bs.empty());
    assert(!Ws.empty());

    auto [x, y] = *com.begin();
    com.erase(com.begin());

    char q = query(x, y);
    ins(q, x, y);
    for (auto [nx, ny] : vecinos(x, y)) {
      if (is_com(nx, ny)) {
        com.insert({nx, ny});
      }
    }

    if (com.empty()) {
      ii min_B = *Bs.begin();
      ii min_W = *Ws.begin();

      if (min_B < min_W) {
        Ws = {};
        auto [xm, ym] = min_B;

        ll i = 1;
        while (Bs.size() < n) {
          char qi = query(xm - i, ym);
          if (qi == 'B') {
            ins('B', xm - i, ym);
          } else {
            ins('W', xm - i, ym);
            for (auto [nx, ny] : vecinos(xm - i, ym)) {
              if (is_com(nx, ny)) {
                com.insert({nx, ny});
              }
            }
            break;
          }

          i++;
        }
      } else { // Copy & paste
        Bs = {};
        auto [xm, ym] = min_W;

        ll i = 1;
        while (Ws.size() < n) {
          char qi = query(xm - i, ym);
          if (qi == 'W') {
            ins('W', xm - i, ym);
          } else {
            ins('B', xm - i, ym);
            for (auto [nx, ny] : vecinos(xm - i, ym)) {
              if (is_com(nx, ny)) {
                com.insert({nx, ny});
              }
            }
            break;
          }

          i++;
        }
      }
    }
  }

  if (Bs.size() == n) {
    return {'B', vii(ALL(Bs))};
  } else {
    return {'W', vii(ALL(Ws))};
  }
}

int main(){
  FIN;

  ll t, n;
  cin >> t >> n;
  while (t--) {
    auto [v, vals] = solve(n);
    cout << "! " << v;
    for (auto [x, y] : vals) {
      cout << ' ' << x << ' ' << y;
    }
    cout << endl;
  }

  return 0;
}