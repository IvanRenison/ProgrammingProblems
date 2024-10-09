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

optional<vi> solve(vi& as) {
    ll n = as.size();

    vi ans;
    ll zeros = 0;
    multiset<ll> have;
    for (ll a : as) {
        if (a > 0) {
            have.insert(a);
        } else if (a == 0) {
            zeros++;
        } else {
            auto it = have.find(-a);
            if (it == have.end()) {
                if (zeros > 0) {
                    ans.push_back(-a);
                    zeros--;
                } else {
                    return {};
                }
            } else {
                have.erase(it);
            }
        }
    }
    while (zeros > 0) {
        ans.push_back(1);
        zeros--;
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(0),cin.tie(0);

    ll n;
    cin >> n;
    vi as(n);
    for (ll& a : as) {
        cin >> a;
    }
    optional<vi> ans = solve(as);
    if (ans) {
        cout << "Yes\n";
        for (ll a : *ans) {
            cout << a << ' ';
        }
    } else {
        cout << "No";
    }
    cout << '\n';

}