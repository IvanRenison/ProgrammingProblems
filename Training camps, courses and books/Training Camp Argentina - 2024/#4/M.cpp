// https://codeforces.com/group/5GNF7zti59/contest/535722/problem/M
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
typedef vector<ii> vii;

vector<ll> a;
ll n,h;

bool can(ll mid){
  vector<ll> aux;
  fore(i,0,mid){
    aux.pb(a[i]);
  }
  sort(ALL(aux));
  ll acc = 0;
  if(mid&1)acc+=aux[0];
  if(acc>h)return false;
  // if(mid==3) cout << acc << "\n";
  fore(i,mid%2,mid){
    if(i+1<mid){
      if(aux[i+1]+acc>h)return false;
      acc+=aux[i+1];
      ++i;
    } else {
      if(aux[i]+acc>h)return false;
    }
  }
  // if(mid==3)cout << "hola\n";
  return true;
}


int main(){
  ios::sync_with_stdio(0),cin.tie(0);
  cin>>n>>h;
  a.resize(n);
  fore(i,0,n)cin>>a[i];
  ll l = 0, r = n;
  while(l<=r){
    ll mid = (l+r)/2;
    if(can(mid))l=mid+1;
    else r=mid-1;
  }
  cout << r << '\n';
}