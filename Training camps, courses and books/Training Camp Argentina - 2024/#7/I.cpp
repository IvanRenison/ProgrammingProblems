// https://codeforces.com/group/5GNF7zti59/contest/534927/problem/I
#include<bits/stdc++.h>
#define fst first
#define snd second
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i =a,gmat=b;i<gmat;++i)
#define pb push_back
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;

vector<vector<string>> vals = {
  {"***", "***", "***", "***", "***"},
  {"*.*", "*.*", "*..", "*.*", "*.."},
  {"***", "***", "*..", "*.*", "***"},
  {"*.*", "*.*", "*..", "*.*", "*.."},
  {"*.*", "***", "***", "***", "***"}
};

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll N;
  cin >> N;
  string S;
  cin >> S;
  fore(i, 0, 5) {
    for (char c : S) {
      ll j = c - 'A';
      cout << vals[i][j];
    }
    cout << '\n';
  }


}