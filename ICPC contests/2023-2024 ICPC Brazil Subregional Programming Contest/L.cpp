// https://codeforces.com/gym/104555/problem/L
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define fore(i,a,b) for(int i=a,gmat=b;i<gmat;++i)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(),x.end()
#define FIN ios::sync_with_stdio(0);cin.tie(0),cout.tie(0)
#define mset(a,v) memset((a),(v),sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int main(){FIN;
    string s;cin>>s;
    ll k;cin>>k;
    vector<vector<char>> ks(k);
    fore(i,0,SZ(s)){
        ks[i%k].pb(s[i]);
    }
    fore(i,0,k){
        sort(ALL(ks[i]));
        reverse(ALL(ks[i]));
    }
    fore(i,0,SZ(s)){
        cout << ks[i%k].back();
        ks[i%k].pop_back();
    }
    cout << "\n";
    return 0;
}