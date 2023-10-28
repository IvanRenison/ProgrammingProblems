// https://codeforces.com/contest/1890/problem/D

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef vector<ull> vu;
typedef vector<ll> vi;
typedef pair<ull, ull> uu;
typedef pair<ll, ll> ii;
typedef vector<uu> vuu;
typedef vector<ii> vii;
typedef tuple<ull, ull, ull> uuu;
typedef tuple<ll, ll, ll> iii;
typedef vector<uuu> vuuu;
typedef vector<iii> viii;
typedef tuple<ull, ull, ull, ull> uuuu;
typedef tuple<ll, ll, ll, ll> iiii;
typedef vector<uuuu> vuuuu;
typedef vector<iiii> viiii;
typedef tuple<ull, ull, ull, ull, ull> uuuuu;
typedef tuple<ll, ll, ll, ll, ll> iiiii;
typedef vector<uuuuu> vuuuuu;
typedef vector<iiiii> viiiii;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()
#define DBG(x) cerr << #x << " = " << x << endl

bool solve1(vu as, ull c) {
  ull n = as.size();

  vii as_i(n);
  fore(i, 0, n) {
    as_i[i] = {(ll)(i+1)*c - (ll)as[i], i};
  }
  sort(as_i.begin(), as_i.end());

  ull sum = as[0];
  fore(j, 0, n) {
    ull i = as_i[j].second;
    if (i != 0) {
      if (sum + as[i] < (i+1)*c) {
        return false;
      }
      sum += as[i];
    }
  }

  return true;
}


int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n, c;
    cin >> n >> c;
    vu as(n);
    fore(j, 0, n) {
      cin >> as[j];
    }

    if (solve1(as, c)) {
      cout << "Yes\n";
    } else {
      cout << "No\n";
    }
  }

  return EXIT_SUCCESS;
}
