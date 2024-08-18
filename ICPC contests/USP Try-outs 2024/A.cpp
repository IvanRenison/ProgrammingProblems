// https://codeforces.com/gym/105297/problem/A
#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((ll)x.size())
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define pb push_back
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef tuple<ll,ll,ll> iii;
typedef vector<iii> viii;
typedef tuple<ll,ll,ll,ll> iiii;
typedef vector<iiii> viiii;

vi solve(viii& tmcs) {
  ll n = tmcs.size();

  viiii tmc_i_s(n);
  fore(i, 0, n) {
    auto [t, m, c] = tmcs[i];
    tmc_i_s[i] = {t, m, c, i};
  }

  sort(ALL(tmc_i_s));

  vector<bool> sad(n, false);

  queue<iii> q;
  ll curr = -1;
  ll curr_t = 0;

  fore(j, 0, n) {
    auto [t, m, c, i] = tmc_i_s[j];

    if (c == 0) {
      q.push({i, t, m});
    } else {
      while (curr_t <= t && !q.empty()) {
        auto [k, t_, m_] = q.front();
        q.pop();

        curr_t = max(curr_t, t_) + m_;
        curr = k;
      }

      if (curr_t <= t) {
        curr_t = t + m;
        curr = i;
      } else {
        if (curr != -1) {
          //cerr << curr << endl;
          sad[curr] = true;
        }
        curr_t = t + m;
        curr = i;
      }
    }

  }


  vi ans;
  fore(i, 0, n) {
    if (sad[i]) {
      ans.push_back(i);
    }
  }

  return ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll n;
  cin >> n;
  viii tmcs(n);
  for (auto& [t, m, c] : tmcs) {
    cin >> t >> m >> c;
  }

  vi ans = solve(tmcs);

  cout << ans.size() << '\n';
  for (ll a : ans) {
    cout << a + 1 << ' ';
  }
  cout << '\n';


}