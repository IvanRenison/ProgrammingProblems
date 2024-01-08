// https://codeforces.com/gym/104848/problem/D
#include <bits/stdc++.h>
#define ALL(x) x.begin(), x.end()
#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; i++)
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<bool> vb;

vi solve(const vector<vi>& ass) {
  ll n = ass.size();

  vector<set<ll>> ass_sets(n);
  fore(i, 0, n) {
    ass_sets[i] = set<ll>(ALL(ass[i]));
  }

  vi ans(n, -1), next(n, -1);
  vb valid_ans(n, false);

  for(ll i = 0; i < n;) {
    for (ll j = i + 1;; j++) {
      if (i == j % n) {
        return vi(n, ass[i][0]);
      }
      bool in = true;
      for(ll a : ass_sets[i]) {
        if (ass_sets[j % n].count(a) == 0) {
          in = false;
          break;
        }
      }
      if (in) {
        ans[j % n] = i;
      } else {
        next[i] = j % n;
        i = j;
        break;
      }
    }
  }

  fore(i, 0, n) {
    if (ans[i] == -1) {
      assert(next[i] != -1);
      for (ll a : ass_sets[i]) {
        if (ass_sets[next[i]].count(a) == 0) {
          ans[i] = a;
          break;
        }
      }
      assert(ans[i] != -1);
      valid_ans[i] = true;
    }
  }

  fore(i, 0, n) {
    if (!valid_ans[i]) {
      assert(ans[i] != -1);
      ans[i] = ans[ans[i]];
      valid_ans[i] = true;
    }
  }

  return ans;
}

int main() {
  FIN;

  ll n;
  cin >> n;
  vector<vi> ass(n);
  for (vi& as : ass) {
    ll k;
    cin >> k;
    as = vi(k);
    for (ll& a : as) {
      cin >> a;
      a--;
    }
    sort(ALL(as));
  }

  vi ans = solve(ass);
  if (ans.empty()) {
    cout << -1;
  } else {
    for (ll a : ans) {
      cout << a + 1 << ' ';
    }
  }
  cout << '\n';

  return 0;
}