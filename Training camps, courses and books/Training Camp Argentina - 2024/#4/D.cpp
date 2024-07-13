// https://codeforces.com/group/5GNF7zti59/contest/535722/problem/D
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define SZ(x) ((ll)x.size())
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;
const ll MOD = 998244353;

vector<ll> fact(2e5 + 10, 1);


ll modmul(ll x, ll y) {
    return x * y % MOD;
}

ll fpow(ll b, ll e){
    if(e==0)return 1;
    ll x = fpow(b,e/2);
    if(e&1){
        return modmul(x,modmul(x,b));
    } else {
        return modmul(x,x);
    }
}



void solve() {
    ll n; cin >> n;
    string s; cin >> s;
    ll z = 0, g = 0;
    fore(i, 0, n) {
        if (s[i] == '0') {
            z++;
            continue;
        }
        if (i != n - 1 && s[i+1] == '1') {
            g++;
            i++;
        }
    }

    // cout << z << ' ' << g << '\n';

    ll res = fact[z + g];
    ll den = modmul(fact[z], fact[g]);
    res = modmul(res,fpow(den,MOD-2));
    cout << res << '\n';
}


int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  fore(i, 1, 2e5 + 10) {
    fact[i] = modmul(i, fact[i-1]);
  }

    ll t; cin >> t;
    while(t--) {
        solve();
    }
}