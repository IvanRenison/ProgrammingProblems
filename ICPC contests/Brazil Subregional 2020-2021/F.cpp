// https://codeforces.com/gym/102861/problem/F
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
typedef tuple<ll, ll, ll, ll, bool> iiiib;
typedef vector<iiiib> viiiib;

viiiib solve(const string& s) {
  viiiib ans;

  ll GL = 0, PL = 0, GR = 0, PR = 0;
  bool ended = false;

  bool saque_L = true;

  for (char c : s) {
    if (c == 'Q') {
      if (ended) {
        ans.push_back({GL, -1, GR, -1, saque_L});
      } else {
        ans.push_back({GL, PL, GR, PR, saque_L});
      }
    } else if (c == 'S') {
      if (saque_L) {
        PL++;
      } else {
        PR++;
      }
    } else {
      if (saque_L) {
        PR++;
        saque_L = false;
      } else {
        PL++;
        saque_L = true;
      }
    }

    // gana L
    if (PL >= 5 && (PL - PR >= 2 || PL >= 10)) {
      GL++;
      PL = 0;
      PR = 0;
    }

    // Gana R
    if (PR >= 5 && (PR - PL >= 2 || PR >= 10)) {
      GR++;
      PL = 0;
      PR = 0;
    }

    if (GL >= 2 || GR >= 2) {
      ended = true;
    }
  }

  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  string s;
  cin >> s;

  viiiib ans = solve(s);
  for (auto [GL, PL, GR, PR, s] : ans) {
    if (PL == -1) {
      if (GL > GR) {
        cout << GL << " (winner) - " << GR << "\n";
      } else {
        cout << GL << " - " << GR << " (winner)\n";
      }
    } else {
      if (s) {
        cout << GL << " (" << PL << "*) - " << GR << " (" << PR << ")\n";
      } else {
        cout << GL << " (" << PL << ") - " << GR << " (" << PR << "*)\n";
      }
    }
  }

}
