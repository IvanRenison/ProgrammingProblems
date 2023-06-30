//Si x es hoja, gana el primero
//Solo se saca el penúltimo cuando sea la única opción
//Entonces solo se saca x cuando queden dos nodos
//n-2 es par => gana el segundo
//n-2 es impar => gana el primero

#include <bits/stdc++.h>
#define pb push_back
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ggdem=b;i<ggdem;++i)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(),x.end()
#define mset(a,v) memset((a),(v)sizeof(a))
#define FIN ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
typedef vector<ll> vvl;

int main(){FIN;
    ll t; cin >> t;
    while(t--){
        ll n,x; cin >> n >> x;
        ll cant = 0;
        fore(i,0,n-1){
            ll n1,n2; cin >> n1 >> n2;
            cant += (n1==x || n2==x);
        }
        if(cant<=1){cout << "Ayush\n";continue;}
        if((n-2)&1){cout << "Ashish\n";continue;}
        cout << "Ayush\n";
    }
    return 0;
}