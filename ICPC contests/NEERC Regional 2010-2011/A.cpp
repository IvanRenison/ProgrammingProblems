// https://codeforces.com/gym/101309
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define mset(a,v) memset((a),(v),sizeof(a))
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;

int main(){
  ios::sync_with_stdio(0),cin.tie(0);
//#ifdef ONLINE_JUDGE
  freopen("alignment.in", "r", stdin);
  freopen("alignment.out", "w", stdout);
//#endif

  vector<string> lines;
  while (!cin.eof()) {
    string s;
    getline(cin, s);
    lines.push_back(s);
  }
  while (lines.back().empty()) {
    lines.pop_back();
  }

  ll n = lines.size();

  vector<vector<string>> words(n);
  fore(i, 0, n) {
    ll k = lines[i].size();
    fore(j, 0, k) {
      char c = lines[i][j];
      if (j == 0 || (c == ' ' && lines[i][j - 1] != ' ')) {
        words[i].push_back("");
      }
      if (c != ' ') {
        words[i].back() += c;
      }
    }
    while (words[i].back().empty()) {
      words[i].pop_back();
    }
  }

  ll max_count = 0;
  fore(i, 0, n) {
    max_count = max(max_count, (ll)words[i].size());
  }

  vi max_szs(max_count);
  fore(j, 0, max_count) {
    ll a = 0;
    fore(i, 0, n) {
      if (words[i].size() > j) {
        a = max(a, (ll)words[i][j].size());
      }
    }
    max_szs[j] = a;
  }

  fore(i, 0, n) {
    fore(j, 0, words[i].size()) {
      cout << words[i][j];
      if (j + 1 != words[i].size()) {
        fore(_, words[i][j].size(), max_szs[j] + 1) {
          cout << ' ';
        }
      }
    }
    cout << '\n';
  }

}
