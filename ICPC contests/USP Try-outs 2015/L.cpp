// https://codeforces.com/gym/101047/problem/L
#include <bits/stdc++.h>
#define p push_back
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ggmat=b;i<ggmat;++i)
#define SZ(x) ((int)x.size())
#define mset(a,v) memset((a),(v),sizeof(a))
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ull mpow(ull x, ull y) {
    ull ans = 1;
    fore(i, 0, y) {
        ans *= x;
    }
    return ans;
}

int main(){FIN;

    ull T;cin >> T;
    while(T--) {
        ull C, D;
        cin >> C >> D;
        cout << (C+D > 0 ? mpow(26, C) * mpow(10, D) : 0 )<< '\n';
    }

    return 0;
}