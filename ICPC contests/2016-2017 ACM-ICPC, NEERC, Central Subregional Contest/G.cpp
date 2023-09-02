// https://codeforces.com/gym/101243
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((int) x.size())
#define fore(i,a,b) for(int i=a,thxMat=b;i<thxMat;++i)
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int main(){FIN;
#ifdef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    ll n;cin>>n;
    map<ll,ll> fact;

    for(int i = 2; i * i <= n; ++i){
        while(n%i==0){
            fact[i]++;
            n/=i;
        }
    }
    if(n>1){
        fact[n]++;
    }

    if(SZ(fact)!=3){
        cout << "NO\n";
        return 0;
    }
    bool p = true;
    for(auto i:fact){
        if(i.snd>1){
            p=false;
            break;
        }
    }
    if(p) cout << "YES\n";
    else cout << "NO\n";
    return 0;
}