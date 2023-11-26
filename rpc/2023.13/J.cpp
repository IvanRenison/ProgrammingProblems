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
    ll f,r;cin>>f>>r;
    vector<ll> rots(r);
    fore(i,0,r)cin>>rots[i];
    vector<vector<char>> mat_aux(3);
    fore(i,0,3)mat_aux[i].resize(3);
    vector<vector<char>> initial;
    if(f==1){
        initial={{'A','-','-'},
                 {'B','-','-'},
                 {'C','D','-'}
        };
    }
    if(f==2){
        initial={{'-','-','A'},
                 {'-','-','B'},
                 {'-','D','C'}
        };
    }
    if(f==3){
        initial={{'-','-','-'},
                 {'A','B','-'},
                 {'-','C','D'}
        };
    }
    if(f==4){
        initial={{'-','-','-'},
                 {'-','C','D'},
                 {'A','B','-'}
        };
    }
    if(f==5){
        initial={{'-','-','-'},
                 {'-','D','-'},
                 {'A','B','C'}
        };
    }
    if(f==6){
        initial={{'-','-','-'},
                 {'A','B','-'},
                 {'C','D','-'}
        };
    }

    fore(i,0,r){
        ll op = rots[i]>0;
        ll aux = abs(rots[i]);
        while(aux>0){
            if(op){
                mat_aux[0][0]=initial[2][0];
                mat_aux[0][1]=initial[1][0];
                mat_aux[0][2]=initial[0][0];
                mat_aux[1][0]=initial[2][1];
                mat_aux[1][1]=initial[1][1];
                mat_aux[1][2]=initial[0][1];
                mat_aux[2][0]=initial[2][2];
                mat_aux[2][1]=initial[1][2];
                mat_aux[2][2]=initial[0][2];
            } else {
                mat_aux[0][0]=initial[0][2];
                mat_aux[0][1]=initial[1][2];
                mat_aux[0][2]=initial[2][2];
                mat_aux[1][0]=initial[0][1];
                mat_aux[1][1]=initial[1][1];
                mat_aux[1][2]=initial[2][1];
                mat_aux[2][0]=initial[0][0];
                mat_aux[2][1]=initial[1][0];
                mat_aux[2][2]=initial[2][0];
            }
            initial=mat_aux;
            aux-=90;
        }
    }
    fore(i,0,3){
        fore(j,0,3){
            cout << initial[i][j];
        }
        cout << "\n";
    }

    return 0;
}
