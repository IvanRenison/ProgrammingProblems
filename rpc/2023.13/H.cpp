// https://redprogramacioncompetitiva.com/contests/2023/13
#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define fst first
#define snd second
#define str string
#define fore(i,a,b) for(int i=a,thxMat=b;i<thxMat;++i)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(),x.end()
#define mset(a,v) memset((a),(v),sizeof(a))
#define FIN ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
using namespace std;
typedef long long ll;
const ll NMAX = 2e5+10;
const ll MOD = 1e9+7;

int main(){FIN;
    ll n;cin>>n;
    vector<ll> mon(n);
    vector<ll> pre_s(n+1);
    fore(i,0,n){
        cin>>mon[i];
        pre_s[i+1]=mon[i]+pre_s[i];
    }
    ll d1,m1,y1;cin>>d1>>m1>>y1;--m1;
    ll d2,m2,y2;cin>>d2>>m2>>y2;--m2;
    if(y1==y2){
        if(m1==m2){
            cout << d2-d1 << "\n";
            return 0;
        } else {
            ll res = mon[m1]-d1+pre_s[m2]-pre_s[m1+1]+d2;
            cout << res << "\n";
            return 0;
        }
    } else {
        ll res = mon[m1]-d1;
        res += pre_s[n]-pre_s[m1+1];
        res += pre_s[n]*(y2-y1-1);
        res += pre_s[m2]+d2;
        cout << res << "\n";
    }
    return 0;
}
