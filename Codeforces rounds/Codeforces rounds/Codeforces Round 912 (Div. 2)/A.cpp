// https://codeforces.com/contest/1903

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
typedef long double ld;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()
#define DBG(x) cerr << #x << " = " << x << endl


bool isSorted(const vu& as) {
  fore(i, 1, as.size()) {
    if (as[i] < as[i - 1]) {
      return false;
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
    ull k, n;
    cin >> n >> k;
    vu as(n);
    fore(j, 0, n) {
      cin >> as[j];
    }

    if (k != 1 || isSorted(as)) {
      cout << "Yes\n";
    } else {
      cout << "No\n";
    }
  }

  return EXIT_SUCCESS;
}
