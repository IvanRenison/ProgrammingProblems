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
const ll MAXN = 110;
const ll MAXM = 110;


vector<int> g[MAXN];
int n,m;
int mat[MAXM]; bool vis[MAXN];
int match(int x){
    if(vis[x])return 0;
    vis[x]=true;
    for(int y:g[x])if(mat[y]<0||match(mat[y])){mat[y]=x;return 1;}
    return 0;
}
vector<pair<int,int>> max_matching(){
    vector<pair<int,int>> r;
    memset(mat,-1,sizeof(mat));
    fore(i,0,n)memset(vis,false,sizeof(vis)),match(i);
    fore(i,0,m)if(mat[i]>=0)r.pb({mat[i],i});
    return r;
}

bool calcu(string a, string b){
    ll sum_a = a[0]-'0'+a[1]-'0'+a[2]-'0';
    ll sum_b = b[3]-'0'+b[4]-'0'+b[5]-'0';
    return sum_a==sum_b;
}


int main(){FIN;
#ifdef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    cin>>n>>m;
    vector<string> ti_n(n), ti_m(m);
    fore(i,0,n)cin>>ti_n[i];
    fore(i,0,m)cin>>ti_m[i];
    fore(i,0,n){
        fore(j,0,m){
            if(calcu(ti_n[i],ti_m[j])||calcu(ti_m[j],ti_n[i])){
                g[i].pb(j);
            }
        }
    }
    vector<pair<int,int>> mat = max_matching();

    cout << SZ(mat) << "\n";
    for(auto i:mat){
        if(calcu(ti_n[i.fst],ti_m[i.snd])){
            cout << "AT " << ti_n[i.fst] << " " << ti_m[i.snd] << "\n";
        } else {
            cout << "TA " << ti_m[i.snd] << " " << ti_n[i.fst] << "\n";
        }
    }
    return 0;
}
