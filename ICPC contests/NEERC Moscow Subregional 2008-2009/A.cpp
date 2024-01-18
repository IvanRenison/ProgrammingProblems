// https://codeforces.com/gym/100861
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define fore(i,a,b) for(int i=a,gmat=b;i<gmat;++i)
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define mset(a,v) memset((a),(v),sizeof(a))
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;

int main(){FIN;

  ll N;
  cin >> N;

  map<string, ll> m;

  vector<pair<string, string>> out;

  fore(i, 0, N) {
    string name, team;
    cin >> name >> team;
    if (name == "MSU" && m[name] < 4) {
      out.push_back({name, team});
      m[name]++;
    } else if (name != "SCH" && m[name] < 2) {
      out.push_back({name, team});
      m[name]++;
    }
    if (out.size() >= 10) {
      break;
    }
  }

  cout << out.size() << '\n';
  for (auto& [u, v] : out) {
    cout << u << ' ' << v << '\n';
  }

	return 0;
}