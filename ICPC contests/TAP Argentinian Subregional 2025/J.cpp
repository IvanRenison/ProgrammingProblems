// https://codeforces.com/gym/106054/problem/J
#include <bits/stdc++.h>
using namespace std;

#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) for (ll i = a, teo = b; i < teo; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (ll)(x).size()
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;

bool solve(vector<vi>& Xss1, vector<vi>& Xss2) {
  ll T = Xss1.size();

  vi Xs1;
  for (vi& Xs : Xss1) {
    for (ll X : Xs) {
      Xs1.push_back(X);
    }
  }
  vi Xs2;
  for (vi& Xs : Xss2) {
    for (ll X : Xs) {
      Xs2.push_back(X);
    }
  }

  sort(ALL(Xs1));
  sort(ALL(Xs2));

  if (Xs1 != Xs2) {
    return false;
  }

  if (T != 2) {
    return true;
  }

  if (Xss1 == Xss2) {
    return true;
  }

  // Hagamos que la primera esté demasiado alta
  if (Xss1[0].size() < Xss2[0].size()) {
    swap(Xss1[0], Xss1[1]);
    swap(Xss2[0], Xss2[1]);
  }

  // Hay que pasar de la primera a la segunda
  ll diff = Xss1[0].size() - Xss2[0].size();

  // La única opción es pasar diff
  fore(_, 0, diff) {
    Xss1[1].push_back(Xss1[0].back());
    Xss1[0].pop_back();
  }

  return Xss1 == Xss2;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  ll T;
  cin >> T;
  vector<vi> Xss1(T), Xss2(T);
  for (vi& Xs : Xss1) {
    ll K;
    cin >> K;
    Xs = vi(K);
    for (ll& X : Xs) {
      cin >> X;
    }
  }
  for (vi& Xs : Xss2) {
    ll K;
    cin >> K;
    Xs = vi(K);
    for (ll& X : Xs) {
      cin >> X;
    }
  }

  bool ans = solve(Xss1, Xss2);
  if (ans) {
    cout << "S\n";
  } else {
    cout << "N\n";
  }
}
