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

ll dp[510][510];
ll h,w;


ll f(ll x, ll y){
    if(x>=h-1 || y>=w-1)return 0;
    ll &res = dp[x][y];
    if(res!=-1) return res;
    res = max(h-1-x+f(x,y+2)+(y<w-2),w-1-y+f(x+2,y)+(x<h-2));
    return res;
}

vector<pair<ll,ll>> ans;

void build(ll x, ll y){
    if(x>=h-1||y>=w-1)return;
    ll res = f(x,y);
    if(res == h-1-x + f(x,y+2)+(y<w-2)){
        fore(i,x,h-1){
            ans.pb({i+1,y+1});
        }
        if(y<w-2){
            ans.pb({h-1,y+2});
        }
        build(x,y+2);
    } else {
        fore(i,y,w-1){
            ans.pb({x+1,i+1});
        }
        if(x<h-2){
            ans.pb({x+2,w-1});
        }
        build(x+2,y);
    }
}


int main(){FIN;
#ifdef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    cin>>h>>w;
    fore(i,0,h)fore(j,0,w)dp[i][j]=-1;
    build(0,0);
    cout << f(0,0) << "\n";
    for(auto i:ans){
        cout << i.fst << " " << i.snd << "\n";
    }
    return 0;
}