// https://codeforces.com/gym/102861/problem/L
#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; i++)
#define ALL(x) begin(x), end(x)
#define SZ(x) (ll)(x).size()
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

ll solve(vector<string>& mat, vector<string>& words) {
  ll L = mat.size(), C = mat[0].size();
  ll N = words.size();


  fore(k, 0, N) {
    sort(ALL(words[k]));
  }

  vector<vi> matches(L, vi(C));

  fore(k, 0, N) {
    ll tam = words[k].size();
    fore(i, 0, L) fore(j, 0, C) {
      // Horizontal
      if (j + tam <= C) {
        string this_W;
        fore(j_, j, j + tam) {
          this_W.push_back(mat[i][j_]);
        }
        sort(ALL(this_W));
        if (this_W == words[k]) {
          fore(j_, j, j + tam) {
            matches[i][j_] |= 1 << k;
          }
        }
      }

      // Vertical
      if (i + tam <= L) {
        string this_W;
        fore(i_, i, i + tam) {
          this_W.push_back(mat[i_][j]);
        }
        sort(ALL(this_W));
        if (this_W == words[k]) {
          fore(i_, i, i + tam) {
            matches[i_][j] |= 1 << k;
          }
        }
      }

      // Diagonal 1
      if (i + tam <= L && j + tam <= C) {
        string this_W;
        fore(d, 0, tam) {
          this_W.push_back(mat[i + d][j + d]);
        }
        sort(ALL(this_W));
        if (this_W == words[k]) {
          fore(d, 0, tam) {
            matches[i + d][j + d] |= 1 << k;
          }
        }
      }

      // Diagonal 2
      if (i + tam <= L && j >= tam - 1) {
        string this_W;
        fore(d, 0, tam) {
          this_W.push_back(mat[i + d][j - d]);
        }
        sort(ALL(this_W));
        if (this_W == words[k]) {
          fore(d, 0, tam) {
            matches[i + d][j - d] |= 1 << k;
          }
        }
      }
    }
  }

  ll ans = 0;
  fore(i, 0, L) fore(j, 0, C) {
    if (__builtin_popcountll(matches[i][j]) > 1) {
      ans++;
    }
  }
  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  ll L, C;
  cin >> L >> C;
  vector<string> mat(L);
  for (string& row : mat) {
    cin >> row;
  }
  ll N;
  cin >> N;
  vector<string> words(N);
  for (string& word : words) {
    cin >> word;
  }

  ll ans = solve(mat, words);
  cout << ans << '\n';


}
