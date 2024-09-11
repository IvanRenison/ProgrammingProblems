// https://contest.ucup.ac/contest/1784/problem/9248
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define mset(a,v) memset((a),(v),sizeof(a))
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef tuple<ll,ll,ll> iii;

ll solve(ll n) {
    vi fact;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            fact.push_back(0);
            while (n % i == 0) {
                fact.back()++;
                n /= i;
            }
        }
    }
    if (n > 1) {
        fact.push_back(1);
    }

    ll ans = 1;
    for (ll e : fact) {
        ans *= 2 * e + 1;
    }

    ans = ans / 2 + 1;

    return ans;
}

int main(){
    ios::sync_with_stdio(0),cin.tie(0);

    ll q;
    cin >> q;
    while (q--) {
        ll n;
        cin >> n;
        cout << solve(n) << '\n';
    }
}