// https://codeforces.com/gym/102346
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define fore(i,a,b) for(int i=a,gmat=b;i<gmat;i++)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(),x.end()
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const ll NMAX = 1e5+10;


ll num[NMAX];
ll n,c,t;

bool can(ll m){
    ll actual = 1; ll aux = 0;
    fore(i,0,n){
        if((num[i]+t-1)/t>m)return false;
        if((num[i]+aux+t-1)/t>m){
            actual++;
            aux = 0;
        }
        aux += num[i];
    }
    return actual<=c;
}

int main(){FIN;
    cin>>n>>c>>t;
    fore(i,0,n)cin>>num[i];
    ll l=1,r=1e10;
    while(l<=r){
        ll m = (l+r)/2;
        if(can(m)) r = m-1;
        else l = m+1;
    }
    cout << l << "\n";
  return 0;
}