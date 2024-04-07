// https://codeforces.com/gym/104270/problem/D
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((ll)x.size())
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;

bool check(vector<ll> &a, vector<ll> &b, string &c){
    ll it = 0;
    fore(i,0,SZ(a)){
        fore(j,0,SZ(b)){
            string chequeo = to_string((a[i])*(b[j]));
            fore(z,0,SZ(chequeo)){
                if(it==SZ(c)){
                    return false;
                }
                if(c[it]!=chequeo[z])return false;
                ++it;
            }
        }
    }
    return it==SZ(c);
}


optional<pair<vi, vi>> solve(ll n, ll m, string c) {
    if(n*m>SZ(c)){
        return {};
    }
    vector<pair<vector<ll>,vector<ll>>> ans;
    fore(i,1,10){
        vector<ll> a,b;
        a.pb(i);
        ll estoy_b = 0;ll it = 0;
        bool p = true;
        while(it<SZ(c) && estoy_b<m){
            ll aux = c[it]-'0';++it;
            if(aux%i==0 && aux/i<10){
                b.pb(aux/i);
            } else {
                aux *= 10;
                aux += c[it]-'0';
                if(aux%i==0 && aux/i<10){
                    b.pb(aux/i);
                } else {
                    p=false;break;
                }
                ++it;
            }
            ++estoy_b;
        }
        if(SZ(b)<m){
            p=false;
        }
        if(!p)continue;
        assert(SZ(b)==m);
        ll estoy_a = 1;estoy_b = 0;
        while(it < SZ(c) && estoy_a<n){
            ll aux = c[it]-'0';++it;
            if(aux%b[estoy_b]==0 && aux/b[estoy_b]<10){
                a.pb(aux/b[estoy_b]);
            } else {
                aux *= 10;
                aux += c[it]-'0';++it;
                if(aux%b[estoy_b]==0 && aux/b[estoy_b]<10){
                    a.pb(aux/b[estoy_b]);
                } else {
                    p = false;break;
                }
            }
            ++estoy_b;
            while(estoy_b<m){
                if(a[estoy_a]*b[estoy_b]>9) it+=2;
                else it++;
                ++estoy_b;
            }
            estoy_b=0;
            ++estoy_a;
        }
        if(SZ(a)<n){
            p=false;
        }
        if(!p)continue;
        assert(SZ(a)==n && SZ(b)==m);
        if(check(a,b,c)){
            ans.pb({a,b});
        }
    }
    if(SZ(ans)==0){
        return {};
    }
    sort(ALL(ans));

    vi ans_a, ans_b;
    fore(i,0,n){
        ans_a.push_back(ans[0].fst[i]);
    }
    fore(i,0,m){
        ans_b.push_back(ans[0].snd[i]);
    }

    assert(check(ans_a, ans_b, c));

    return {{ans_a, ans_b}};
}




int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    ll t;cin>>t;
    while(t--){
        ll n,m;cin>>n>>m;
        string c;cin>>c;

        auto ans = solve(n, m, c);

        if (!ans.has_value()) {
            cout << "Impossible\n";
        } else {
            auto [a, b] = *ans;
            assert(check(a, b, c));
            fore(i, 0, a.size()) {
                cout << a[i];
            }
            cout << ' ';
            fore(i, 0, b.size()) {
                cout << b[i];
            }
            cout << '\n';
        }
    }
/*
    fore(_, 0, 10000) {
        ll n = rand() % 10 + 1;
        ll m = rand() % 10 + 1;

        ll t = rand() % 105 + 1;
        string s;
        s.push_back('1' + rand() % 9);
        fore(i, 1, t) {
            s.push_back('0' + rand() % 10);
        }

        cout << n << ' ' << m << '\n';
        cout << s << '\n';
        cout << "---------------" << endl;


        auto ans = solve(n, m, s);
    } */


}
