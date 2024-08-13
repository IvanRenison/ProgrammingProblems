// https://codeforces.com/group/YjFmW2O15Q/contest/101811
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define SZ(x) ((ll)x.size())
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;

vector<string> vals = {"DO", "DO#", "RE", "RE#", "MI", "FA", "FA#", "SOL",
"SOL#", "LA", "LA#", "SI"};

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll S;
  cin >> S;
  string N;
  cin >> N;

  ll i = 0;
  fore(j, 0, vals.size()) {
    if (vals[j] == N) {
      i = j;
      break;
    }
  }

  i = (i + vals.size() - S) % vals.size();

  cout << vals[i] << '\n';
}