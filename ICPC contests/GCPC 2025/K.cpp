// https://codeforces.com/gym/106129/problem/K
#include <bits/stdc++.h>
using namespace std;

#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) for (ll i = a, mpisp = b; i < mpisp; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (ll)(x).size()
typedef long long ll;
typedef pair<ll, ll> ii;
typedef tuple<ll, ll, ll> iii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef vector<iii> viii;
typedef long double ld;


optional<vi> solve(ll n, ll a, ll b) {
  if (a + b > n + 1 || a + b == 2) {
    return {};
  }

  if (b == 1) {
    auto ans = *solve(n, b, a);
    reverse(ALL(ans));
    return ans;
  }

  vi ans(n);
  ll val = 0;
  fore(i, 0, a - 1) {
    ans[i] = val;
    val++;
  }
  ans[a - 1] = n - 1;

  if (a + b < n + 1) {
    ans[n - b + 1] = n - 2;
  }
  for (ll i = n; i--; ) {
    if (a - 1 == i) {
      break;
    }
    if (a + b == n + 1 || i != n - b + 1) {
      ans[i] = val;
      val++;
    }
  }

  return ans;
}


int main() {
	cin.tie(0)->sync_with_stdio(0);

  ll n, a, b;
  cin >> n >> a >> b;

  auto ans = solve(n, a, b);
  if (ans) {
    cout << "yes\n";
    for (ll a : *ans) {
      cout << a + 1 << ' ';
    }
    cout << '\n';
  } else {
    cout << "no\n";
  }

}
