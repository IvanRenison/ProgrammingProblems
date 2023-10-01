// https://redprogramacioncompetitiva.com/contests/2023/11
#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((int)x.size())
#define fore(i,a,b) for(int i=a,gmat=b;i<gmat;++i)
#define pb push_back
#define mset(a,v) memset((a),(v),sizeof(a))
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vii;
typedef pair<ll,ll> ii;

int main(){FIN;
    ll n;cin>>n;
    vector<ll> p(n);
    vector<ll> p_inv(n);
    fore(i,0,n){
        cin>>p[i];--p[i];
        p_inv[p[i]]=i;
    }
    ll cant_s=0;
    fore(i,0,n){
        if(p[i]==i)continue;
        cant_s++;
        ll aux = p[i];
        p[i]=i;p[p_inv[i]]=aux;
        p_inv[aux]=p_inv[i];
    }
    //cout << cant_s << "\n";
    if(cant_s&1) cout << "Smokin Joe!\n";
    else cout << "Oh No!\n";
    return 0;
}