// https://qoj.ac/contest/1699/problem/8519
#include <bits/stdc++.h>
using namespace std;

#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; i++)
#define ALL(x) begin(x), end(x)
#define SZ(x) (ll)(x).size()
#define mset(a, v) memset((a), (v), sizeof(a))
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef long double ld;

const ll inf = 1ll << 60;

ll solveLowerHalf(const vector<vi>& board) {
  ll n = board.size();

  ll ans = inf;
  fore(i, 0, n/2) {
    ll this_ans = board[i][n/2];
    ans = min(ans, this_ans);
  }

  ll minLeft = inf, minRight = inf;
  fore(j, 0, n/2 + 1) {
    fore(i, 0, n/2 + 1) {
      minLeft = min(minLeft, board[i][j]);
      minRight = min(minRight, board[i][n/2 + j]);
    }
  }

  ans = min(ans, minLeft + minRight);

  return ans;
}

ll solveHorizontal(vector<vi> board) { // Partir horizontalmente
  ll n = board.size();

  ll ans = solveLowerHalf(board);
  fore(i, 0, n/2) {
    swap(board[i], board[n-1-i]);
  }
  ans += solveLowerHalf(board);

  return ans;
}

ll solve(vector<vi>& board) {
  ll n = board.size();

  ll ans = board[n/2][n/2];

  ans = min(ans, solveHorizontal(board));

  vector<vi> board2(n, vi(n));
  fore(i, 0, n) {
    fore(j, 0, n) {
      board2[i][j] = board[j][i];
    }
  }
  ans = min(ans, solveHorizontal(board2));

  return ans;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);

  ll t;
  cin >> t;

  while (t--) {
    ll n;
    cin >> n;

    vector<vi> board(n, vi(n));
    for (vi& row : board) {
      for (ll& a : row) {
        cin >> a;
      }
    }

    ll ans = solve(board);
    cout << ans << '\n';
  }

}
