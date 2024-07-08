// https://codeforces.com/group/5GNF7zti59/contest/534272/problem/C
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
typedef long double ld;

int main(){
  ios::sync_with_stdio(0),cin.tie(0);
  ll t;cin>>t;
  while(t--){
    ll n,m;cin>>n>>m;
    vector<ll> a(n), b(m);
    ll men = 0, may = 0;
    fore(i,0,n){
      cin>>a[i];
      men += a[i]<0, may += a[i]>0;
    }
    vector<ll> posis, negs;
    fore(i,0,m){
      cin>>b[i];
      if(b[i]>0){
        posis.pb(b[i]);
      } else {
        negs.pb(b[i]);
      }
    }
    reverse(ALL(posis));
    ll act = 0;
    ll res_neg = 0;
    fore(i,0,SZ(negs)){
      ll l = i+1, r = SZ(negs);
      while(l<=r){
        ll mid = (l+r)/2;
        ll busco = lower_bound(ALL(a),negs[i])-a.begin();
        if(negs[mid-1]-negs[i]+1<=men-busco)l=mid+1;
        else r=mid-1;
      }
      res_neg = max(res_neg, act+r-i);
      ll hay = lower_bound(ALL(a),negs[i])-a.begin();
      if(hay<SZ(a) && a[hay]==negs[i])++act;
    }
    act = 0;
    ll res_pos = 0;
    fore(i,0,SZ(posis)){
      ll l = i+1, r = SZ(posis);
      while(l<=r){
        ll mid = (l+r)/2;
        ll busco = upper_bound(ALL(a),posis[i])-a.begin();
        busco = n-busco;
        if(posis[i]-posis[mid-1]+1<=may-busco)l=mid+1;
        else r=mid-1;
      }
      res_pos = max(res_pos,act+r-i);
      ll hay = lower_bound(ALL(a),posis[i])-a.begin();
      if(hay<SZ(a) && a[hay]==posis[i])++act;
    }
    cout << res_neg+res_pos << "\n";
  }
}