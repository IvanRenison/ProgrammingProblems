// https://codeforces.com/contest/1662/problem/O
#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((int)x.size())
#define fore(i,a,b) for(int i=a,gmat=b;i<gmat;++i)
#define pb push_back
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define mste(a,v) memset((a),(v),sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;
typedef vector<ii> vii;

bool solve(viii Cs, viii Ss) {

  // 0: up, 1: right, 2 down, 3 left
  vector<vector<vector<bool>>> disconnected(21, vector<vector<bool>>(360, vector<bool>(4, false)));

  fore(a, 0, 360) {
    disconnected[0][a][0] = true;
    disconnected[20][a][2] = true;
  }

  for(auto [r, a0, a1] : Cs) {
    if (a1 < a0) {
      a1 += 360;
    }
    fore(a, a0, a1) {
      disconnected[r-1][a % 360][2] = true;
      disconnected[r][a % 360][0] = true;
    }
  }

  for(auto [r0, r1, a] : Ss) {
    fore(r, r0, r1) {
      disconnected[r][a][3] = true;
      disconnected[r][(a + 359) % 360][1] = true;
    }
  }

  vii s = {{20, 0}};
  vector<vector<bool>> vis(21, vector<bool>(360, false));
  vis[20][0] = true;

  while(!s.empty()) {
    auto [r, a] = s.back();
    s.pop_back();

    vii adj;
    if (!disconnected[r][a][0]) {
      adj.push_back({r-1,a});
    }
    if (!disconnected[r][a][1]) {
      adj.push_back({r, (a+1)%360});
    }
    if (!disconnected[r][a][2]) {
      adj.push_back({r+1,a});
    }
    if (!disconnected[r][a][3]) {
      adj.push_back({r, (a+359)%360});
    }

    for (auto [r0, a0] : adj) {
      if (r0 == 0) {
        return true;
      }

      if (!vis[r0][a0]) {
        vis[r0][a0] = true;
        s.push_back({r0, a0});
      }
    }
  }

  return false;
}

int main(){FIN;

  ull t;
  cin >> t;
  while(t--) {
    ull n;
    cin >> n;

    viii Cs, Ss;

    while(n--) {
      char c;
      ll a, b, d;
      cin >> c >> a >> b >> d;
      if (c == 'C') {
        Cs.push_back({a,b,d});
      } else {
        Ss.push_back({a,b,d});
      }
    }

    if (solve(Cs, Ss)) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }

	return 0;
}
