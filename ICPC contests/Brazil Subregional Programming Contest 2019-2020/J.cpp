// https://codeforces.com/gym/102346
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(), x.end()
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ull choose(vector<ull> d) {
  map<ull, ull> m;
  for (ull a : d) {
    m[a]++;
  }

  ull cho = 1000;

  for (auto [a, c] : m) {
    if (cho == 1000) {
      cho = a;
    } else {
      if (c < m[cho] || (c == m[cho] && a < cho)) {
        cho = a;
      }
    }
  }

  fore(i, 0, d.size()) {
    if (cho == d[i]) {
      return i;
    }
  }
}

bool is_win(vector<ull> d) {
  return d.size() == 4 && d[0] == d[1] && d[1] == d[2] && d[2] == d[3];
}

vector<ull> takeout(ull i, vector<ull> deck) {
  vector<ull> new_deck;
  fore(j, 0, deck.size()) {
    if (j != i) {
      new_deck.push_back(deck[j]);
    }
  }
  return new_deck;
}

ull solve(ull K, vector<vector<ull>> H) {
  ull N = H.size();

  { // Check if it starts win
    ull win = 100;
    ull win_value = 100;

    fore(i, 0, N) {
      ull a = H[i][0], b = H[i][1], c = H[i][2], d = H[i][3];
      if (K != i && a == b && b == c && c == d && d < win_value) {
        win = i;
        win_value = d;
      }
    }

    if (win != 100) {
      return win;
    }
  }

  vector<vector<ull>> deck = H;

  ull wildcard = K;
  bool wildcard_new = true;

  for (ull i = K;; i = (i + 1) % N) {
    if (wildcard == i && !wildcard_new) {
      wildcard = (wildcard + 1) % N;
      wildcard_new = true;
    } else {
      ull j = choose(deck[i]);
      deck[(i + 1) % N].push_back(deck[i][j]);
      deck[i] = takeout(j, deck[i]);
      if (wildcard == i) {
        wildcard_new = false;
      }
    }

    if (wildcard != i && is_win(deck[i])) {
      return i;
    }
  }
}

int main() {
  FIN;
  ull N, K;
  cin >> N >> K;

  vector<vector<ull>> H(N, vector<ull>(4));
  fore(i, 0, N) {
    char a[4];
    cin >> a[0] >> a[1] >> a[2] >> a[3];
    fore(j, 0, 4) {
      if (a[j] == 'A') {
        H[i][j] = 0;
      } else if (a[j] == 'D') {
        H[i][j] = 9;
      } else if (a[j] == 'Q') {
        H[i][j] = 10;
      } else if (a[j] == 'J') {
        H[i][j] = 11;
      } else if (a[j] == 'K') {
        H[i][j] = 12;
      } else {
        H[i][j] = a[j] - '1';
      }
    }
  }

  cout << solve(K - 1, H) + 1 << '\n';

  return 0;
}