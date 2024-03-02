// https://atcoder.jp/contests/abc343/tasks/abc343_d

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
#define sz(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;
const ld eps = 1e-7;


vu solve(ull N, const vuu& ABs) {
  ull T = sz(ABs);

  vu scores(N, 0);
  map<ull, ull> vals;
  vals[0] = N;

  vu ans(T);

  fore(i, 0, T) {
    auto [A, B] = ABs[i];
    vals[scores[A]]--;
    if (vals[scores[A]] == 0) {
      vals.erase(scores[A]);
    }
    scores[A] += B;
    vals[scores[A]]++;

    ans[i] = vals.size();
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull N, T;
  cin >> N >> T;
  vuu ABs(T);
  for (auto& [A, B] : ABs) {
    cin >> A >> B;
    A--;
  }

  auto ans = solve(N, ABs);
  for (auto& x : ans) {
    cout << x << '\n';
  }

  return EXIT_SUCCESS;
}
