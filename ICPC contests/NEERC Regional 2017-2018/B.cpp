// https://codeforces.com/gym/101630
#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define SZ(x)  (ll(x.size()))
#define pb push_back
#define mset(a,v) memset((a),(v),sizeof(a))
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;

int main(){
    ios::sync_with_stdio(0),cin.tie(0);

    array<ll, 3> s;
    cin >> s[0] >> s[1] >> s[2];
    ll w, h; cin >> w >> h;
    sort(ALL(s));
    do {
        auto [a, b, c] = s;
        vector<ii> opts = {
            {2*c+a, 2*c+2*b},
            {a+b+c, 2*c+2*b},
            {2*c+a, 2*b+c+a},
            {2*c+a+b, a+b+c},
            {3*a+b+c, b+c},
            {a+b+c, 2*a+b+c}
        };
        for (auto [wi, hi] : opts) {
            if ((wi <= w && hi <= h) || (wi <= h && hi <= w)) {
                cout << "Yes\n";
                return 0;
            }
        }
    } while(next_permutation(ALL(s)));
    cout << "No\n";
}