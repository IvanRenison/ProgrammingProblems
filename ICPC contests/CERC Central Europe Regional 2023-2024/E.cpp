// https://codeforces.com/gym/104871/problem/E
#include <bits/stdc++.h>
#define pb push_back
#define SZ(x) ((ll)x.size())
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define ALL(x) x.begin(),x.end()
#define mset(a,v) memset((a),(v),sizeof(a))
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;

vector<pair<string, ll>> solve(const vector<tuple<ll, ll, string>>& fst, const vector<tuple<ll, ll, string>>& snd) {
  map<string, ll> counts1, counts2;
  set<string> names;
  for (auto [s, e, t] : fst) {
    names.insert(t);
    counts1[t] += e - s;
  }
  for (auto [s, e, t] : snd) {
    names.insert(t);
    counts2[t] += e - s;
  }

  vector<pair<string, ll>> ans;

  for (auto t : names) {
    ll d = counts2[t] - counts1[t];
    if (d != 0) {
      ans.push_back({t, d});
    }
  }

  return ans;
}

int main(){FIN;

  vector<tuple<ll, ll, string>> fst, snd;
  while (true) {
    string s, e, t;
    cin >> s;
    if (s[0] == '-') {
      break;
    }
    cin >> e >> t;
    ll s_ = stoi(s), e_ = stoi(e);
    fst.push_back({s_, e_, t});
  }
  while (true) {
    string s, e, t;
    cin >> s;
    if (s[0] == '=') {
      break;
    }
    cin >> e >> t;
    ll s_ = stoi(s), e_ = stoi(e);
    snd.push_back({s_, e_, t});
  }

  vector<pair<string, ll>> ans = solve(fst, snd);
  if (ans.size() == 0) {
    cout << "No differences found.\n";
  }
  for (auto [t, d] : ans) {
    cout << t << ' ' << (d > 0 ? "+" : "-") << abs(d) << '\n';
  }

	return 0;
}