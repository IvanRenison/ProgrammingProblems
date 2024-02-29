// https://codeforces.com/gym/104505/problem/D
#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(x) x.begin(),x.end()
#define SZ(x) (ll(x.size()))
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define pb push_back
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef tuple<ll, ll, ll> iii;

vi solve(ll k, const vector<ii>& events) {
  ll n = events.size() / 2;

  vector<queue<ii>> qs(k);
  vector<bool> out(n, false);
  vector<ll> in_ord;
  ll out_i = 0;

  vector<bool> angry(n, false);

  fore(i, 0, 2 * n) {
    auto [p, f] = events[i];
    if (p != -1) {
      qs[f].push({p, in_ord.size()});
      in_ord.push_back(p);
    } else {
      assert(!qs[f].empty());

      auto [p, in_t] = qs[f].front();
      qs[f].pop();

      out[p] = true;

      if (out_i < in_t) {
        fore(j, out_i, in_t) {
          if (!out[in_ord[j]]) {
            angry[in_ord[j]] = true;
          }
        }

        out_i = in_t;
      }
    }
  }

  vi ans;
  fore(i, 0, n) {
    if (angry[i]) {
      ans.push_back(i);
    }
  }

  return ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll n, k;
  cin >> n >> k;

  vector<ii> events(2 * n);
  for (auto& [p, f] : events) {
    ll ty;
    cin >> ty;
    if (ty == 1) {
      cin >> p >> f;
      p--, f--;
    } else {
      p = -1;
      cin >> f;
      f--;
    }
  }

  vi ans = solve(k, events);

  cout << ans.size() << '\n';
  for (ll a : ans) {
    cout << a + 1 << ' ';
  }
  cout << '\n';

  return 0;
}