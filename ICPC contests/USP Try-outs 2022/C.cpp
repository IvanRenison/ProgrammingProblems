// https://codeforces.com/gym/103934/problem/C
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

vector<pair<vector<ll>,char>> trie;

void insert_trie(string &key, int node, int i, ll kv){
    if(i>=SZ(key)){
        ll nw = SZ(trie);
        trie[node].first.pb(nw);
        trie.pb({{kv},'$'});
        return;
    }
    for(auto next: trie[node].fst){
        if(trie[next].second == key[i]){
            insert_trie(key,next,i+1,kv);
            return;
        }
    }
    ll nw = SZ(trie);
    trie.pb({{},key[i]});
    trie[node].first.pb(nw);
    insert_trie(key,nw,i+1,kv);
}

ll max_trie(int node, ll carry){
    for(auto i: trie[node].fst){
        if(trie[i].second == '$'){
            carry += trie[i].first[0];
        }
    }
    ll res = carry;
    for(auto i: trie[node].fst){
        if(trie[i].second != '$'){
            res = max(res,max_trie(i,carry));
        }
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    trie.pb({{},'#'});
    int n;
    cin>>n;
    fore(i,0,n){
        string s;
        cin>>s;
        ll v;
        cin>>v;
        insert_trie(s,0,0,v);
    }
    cout<<max_trie(0,0)<<'\n';
    return 0;
}
