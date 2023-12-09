// https://codeforces.com/contest/1904/problem/B

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef tuple<ull, ull, ull> uuu;
typedef vector<uuu> vuuu;
typedef tuple<ull, ull, ull, ull> uuuu;
typedef vector<uuuu> vuuuu;
typedef tuple<ull, ull, ull, ull, ull> uuuuu;
typedef vector<uuuuu> vuuuuu;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;
typedef tuple<ll, ll, ll, ll> iiii;
typedef vector<iiii> viiii;
typedef tuple<ll, ll, ll, ll, ll> iiiii;
typedef vector<iiiii> viiiii;
typedef long double ld;
typedef vector<ld> vd;
typedef pair<ld, ld> dd;
typedef vector<dd> vdd;
typedef tuple<ld, ld, ld> ddd;
typedef vector<ddd> vddd;
typedef tuple<ld, ld, ld, ld> dddd;
typedef vector<dddd> vdddd;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()
#define DBG(x) cerr << #x << " = " << x << endl


vu solve1(vu as) {
  ull n = as.size();

  vuu as_i(n);
  fore(i, 0, n) {
    as_i[i] = {as[i], i};
  }
  sort(all(as_i));

  vuu dp(n);

  {
    auto [a, j] = as_i[0];
    dp[j].first = a;
    dp[j].second = 1;
    ull k = 1;
    while(k < n && as_i[k].first <= dp[j].first) {
      dp[j].first += as_i[k].first;
      k++;
      dp[j].second++;
    }
  }

  fore(i, 1, n) {
    auto [a, j] = as_i[i];
    auto [a_, j_] = as_i[i - 1];

    auto [ans_, k] = dp[j_];
    dp[j].first = ans_;
    dp[j].second = k;
    if (k <= i) {
      dp[j].first += a;
      dp[j].second++;
      k++;
    }

    while(k < n && as_i[k].first <= dp[j].first) {
      dp[j].first += as_i[k].first;
      k++;
      dp[j].second++;
    }
  }

  vu ans(n);
  fore(i, 0, n) {
    auto [a, j] = as_i[i];
    auto [ans_, k] = dp[j];
    ans[j] = ans_ >= a ? k - 1 : k;
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ull n;
    cin >> n;
    vu as(n);
    fore(j, 0, n) cin >> as[j];

    auto ans = solve1(as);
    for(auto a : ans) cout << a << " ";
    cout << '\n';
  }

  return EXIT_SUCCESS;
}
