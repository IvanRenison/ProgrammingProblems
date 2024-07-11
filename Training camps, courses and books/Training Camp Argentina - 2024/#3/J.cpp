// https://codeforces.com/group/5GNF7zti59/contest/535420/problem/J
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;

int main(){
  ios::sync_with_stdio(0),cin.tie(0);
  ll n,k;cin>>n>>k;
  vector<ll> a(n);
  fore(i,0,n)cin>>a[i];
  string s;cin>>s;
  priority_queue<ll> pq;
  char c = s[0];pq.push(a[0]);
  ll res = 0;
  fore(i,1,n){
    if(s[i]==c){
      pq.push(a[i]);
    } else {
      ll co = 0;
      while(SZ(pq) && co<k){
        ll priti = pq.top();
        res += priti;
        pq.pop();
        ++co;
      }
      while(SZ(pq))pq.pop();
      c = s[i];
      pq.push(a[i]);
    }
  }
  ll co = 0;
  while(SZ(pq) && co<k){
    ll priti = pq.top();
    res += priti;
    pq.pop();
    ++co;
  }
  cout << res << '\n';
}