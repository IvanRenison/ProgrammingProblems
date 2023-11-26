// https://codeforces.com/contest/1900/problem/C

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

const ull inf = 1ull << 60;

ull solve1(const string& s, const vuu& lrs) {

  function<ull(ull)> f = [&](ull i) {
    auto [l, r] = lrs[i - 1];
    if (l == 0 && r == 0) {
      return 0ull;
    }

    ull ans_l = l == 0 ? inf : f(l);
    ull ans_r = r == 0 ? inf : f(r);

    ull add_l = s[i - 1] == 'L' ? 0 : 1;
    ull add_r = s[i - 1] == 'R' ? 0 : 1;

    return min(ans_l + add_l, ans_r + add_r);
  };

  return f(1);
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
    vuu lrs(n);
    for(auto& [l, r] : lrs) {
      cin >> l >> r;
    }

    auto ans = solve1(s, lrs);
    cout << ans << '\n';
  }

  return EXIT_SUCCESS;
}
