// https://codeforces.com/group/5GNF7zti59/contest/534709/problem/A
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((ll)x.size())
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll n;
  cin >> n;
  fore(i, 0, n) {
    cout << i % 2;
  }
  cout << '\n';
}