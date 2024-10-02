// https://codeforces.com/gym/101309
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define mset(a,v) memset((a),(v),sizeof(a))
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;
typedef long double ld;
typedef tuple<ll, ll, ll> iii;

void move(ll r, ll c, ll k) {
  cout << r + 1 << ' ' << c + 1 << ' ' << k << endl;
}

void WIN(ll r, ll c, ll k) {
  cout << r + 1 << ' ' << c + 1 << ' ' << k << " WIN" << endl;
}

iii read() {
  ll r, c, k;
  cin >> r >> c >> k;
  r--, c--;
  return {r, c, k};
}

void solve() {
  vector<vi> board(4, vi(4, -1));

  auto directWin = [&](ll r, ll c) -> optional<ll> {
    if (board[r][c] != -1) {
      return {};
    }
    ll sum = 0;
    fore(i, 0, 4) if (i != c) {
      if (board[r][i] == -1) {
        goto next;
      }
      sum += board[r][i];
    }
    if (sum >= 6 && sum <= 9) {
      return 10 - sum;
    }

    next:;
    sum = 0;
    fore(i, 0, 4) if (i != r) {
      if (board[i][c] == -1) {
        return {};
      }
      sum += board[i][c];
    }
    if (sum >= 6 && sum <= 9) {
      return 10 - sum;
    }
    return {};
  };

  auto findDirectWin = [&]() -> optional<iii> {
    fore(r, 0, 4) fore(c, 0, 4) {
      auto k = directWin(r, c);
      if (k.has_value()) {
        return {{r, c, *k}};
      }
    }
    return {};
  };

  while (true) {
    auto [r0, c0, k0] = read();
    board[r0][c0] = k0;
    auto win = findDirectWin();
    if (win.has_value()) {
      auto [r1, c1, k1] = *win;
      WIN(r1, c1, k1);
      return;
    }
    ll r1 = r0;
    ll c1 = c0 ^ 1;
    ll k1 = 5 - k0;
    board[r1][c1] = k1;
    move(r1, c1, k1);

    fore(r, 0, 4) {
      fore(c, 0, 4) {
        cerr << board[r][c] << ' ';
      }
      cerr << endl;
    }
  }


}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  solve();

}