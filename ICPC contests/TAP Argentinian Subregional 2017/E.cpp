// https://codeforces.com/group/YjFmW2O15Q/contest/101811
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define SZ(x) ((ll)x.size())
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;
typedef tuple<ll,ll,ll> iii;
typedef vector<iii> viii;

bool solve(ll C0, ll C1, ll C2) {

  function<bool(const vi&, const vi&, const vii&)> rec = [&](const vi& cs0, const vi& cs1, const vii& game) -> bool {
    ll n = cs0.size(), m = cs1.size() - 1;
    if (n == 0 && m == 0) {
      auto [e0, l0] = game[0];
      auto [e1, l1] = game[1];
      auto [e2, l2] = game[2];

      return (e0 < l0) + (e1 < l1) + (e2 < l2) >= 2;
    }

    if (n == m && (game.empty() || game.back().first < game.back().second)) { // Edu
      fore(i, 0, n) {
        vi cs0_;
        fore(j, 0, n) if (j != i) {
          cs0_.push_back(cs0[j]);
        }
        vii game_ = game;
        game_.push_back({cs0[i], -1});

        bool this_ans = rec(cs0_, cs1, game_);
        if (this_ans) {
          return true;
        }
      }
      return false;
    } else if (n == m) { // Laino
      fore(i, 0, m + 1) {
        vi cs1_;
        fore(j, 0, m + 1) if (j != i) {
          cs1_.push_back(cs1[j]);
        }
        vii game_ = game;
        game_.push_back({-1, cs1[i]});
        bool this_ans = rec(cs0, cs1_, game_);
        if (!this_ans) {
          return false;
        }
      }
      return true;
    } else if (game.back().first == -1) { // Edu
      fore(i, 0, n) {
        vi cs0_;
        fore(j, 0, n) if (j != i) {
          cs0_.push_back(cs0[j]);
        }
        vii game_ = game;
        game_.back().first = cs0[i];

        bool this_ans = rec(cs0_, cs1, game_);
        if (this_ans) {
          return true;
        }
      }
      return false;
    } else { // Laino
      fore(i, 0, m + 1) {
        vi cs1_;
        fore(j, 0, m + 1) if (j != i) {
          cs1_.push_back(cs1[j]);
        }
        vii game_ = game;
        game_.back().second = cs1[i];
        bool this_ans = rec(cs0, cs1_, game_);
        if (!this_ans) {
          return false;
        }
      }
      return true;
    }
  };

  vi cs0 = {C0, C1, C2};
  vi big1;
  fore(i, 1, 8) {
    if (i != C0 && i != C1 && i != C2) {
      big1.push_back(i);
    }
  }

  vii game;
  bool ans = rec(cs0, big1, game);

  return ans;

}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll C0, C1, C2;
  cin >> C0 >> C1 >> C2;

  cout << (solve(C0, C1, C2) ? 'S' : 'N') << '\n';

}