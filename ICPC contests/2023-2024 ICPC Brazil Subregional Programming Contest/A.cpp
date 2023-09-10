// https://codeforces.com/gym/104555/problem/A
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

    ull N, H;
    cin >> N >> H;
    vector<ull> As(N);
    ull count = 0;
    for(ull& A : As) {
        cin >> A;
        if (A <= H) {
            count++;
        }
    }
    cout << count << '\n';

    return 0;
}