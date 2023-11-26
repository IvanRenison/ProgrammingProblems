// https://codeforces.com/contest/1900/problem/A

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


ull solve1(string s) {
  ull n = s.size();

  ull count_total = 0, count_segudos = 0;
  ull this_seguidos = 0;
  for(auto c : s) {
    if (c == '#') {
      count_segudos = max(count_segudos, this_seguidos);
      this_seguidos = 0;
    } else {
      this_seguidos++;
      count_total++;
    }
  }
  count_segudos = max(count_segudos, this_seguidos);

  if (count_segudos >= 3) {
    return 2;
  } else {
    return count_total;
  }

}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;
    string s;
    cin >> s;

    auto ans = solve1(s);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
