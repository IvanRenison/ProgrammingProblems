// https://codeforces.com/gym/103934/problem/G
#include <bits/stdc++.h>
using namespace std;

#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) for (ll i = a, efunca = b; i < efunca; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (ll)(x).size()
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<pair<ll, ll>> vii;
typedef long double ld;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ll t;
    cin >> t;
    while(t--){
        string s; cin >> s;
        ll n = SZ(s);
        string res;

        fore(i,0,n){
            if(i==0){
                if(n>1){
                    if(s[i]!=s[i+1]){
                        res.pb(s[i]);
                        res.pb(s[i]);
                    } else{
                        res.pb(s[i]);
                    }
                } else{
                        res.pb(s[i]);
                        res.pb(s[i]);
                }
            } else if(i==n-1){
                if(s[i]!=s[i-1]){
                        res.pb(s[i]);
                        res.pb(s[i]);
                    } else{
                        res.pb(s[i]);
                    }
            } else{
                if(s[i] != s[i+1] && s[i] != s[i-1]){
                    res.pb(s[i]);
                    res.pb(s[i]);
                } else{
                    res.pb(s[i]);
                }
            }
        }
        cout << res << "\n";
    }

}