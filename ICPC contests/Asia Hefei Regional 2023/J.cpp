// https://codeforces.com/gym/104857/problem/F
#include <bits/stdc++.h>
#pragma GCC optimize("O2,unroll-loops,modulo-sched,modulo-sched-allow-regmoves,gcse-sm,gcse-las,ipa-pta,tree-loop-im,tree-loop-ivcanon,ivopts,tree-vectorize")
#pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,tune=native")
#define fst first
#define snd second
#define pb push_back
#define fore(i,a,b) for(int i=a,gmat=b;i<gmat;++i)
#define mset(a,v) memset((a),(v),sizeof(a))
#define SZ(x) (ll(x.size()))
#define ALL(x) x.begin(),x.end()
#define FIN ios::sync_with_stdio(0),cout.tie(0),cin.tie(0)
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<ll,ll> ii;
const int NMAX = 1e9;

struct UF {
	vi e;
	UF(int n) : e(n, -1) {}
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
		return true;
	}
};

int n,m;
vector<pair<int,int>> edges;
vector<pair<int,int>> adj;

bool can(int me){
    UF u(n);
    int r = lower_bound(ALL(edges),make_pair(me+1,0))-edges.begin();
    --r;
    fore(i,0,m){
        if(r<i)break;
        if(r==i){
            u.join(adj[edges[i].snd].fst,adj[edges[i].snd].snd);
            return u.find(0)==u.find(n-1);
        }
        while(r>i && edges[r].fst+edges[i].fst>me){
            int pax = u.find(adj[edges[r].snd].fst), pay = u.find(adj[edges[r].snd].snd);
            if((u.find(0)==pax&&u.find(n-1)==pay) || (u.find(0)==pay&&u.find(n-1)==pax) || (u.find(0)==u.find(n-1)))return true;
            --r;
            if(r==i){
                u.join(adj[edges[r].snd].fst,adj[edges[r].snd].snd);
                return u.find(0)==u.find(n-1);
            }
        }
        if(r<i)break;
        u.join(adj[edges[i].snd].fst,adj[edges[i].snd].snd);
    }
    return u.find(0)==u.find(n-1);
}


int main(){FIN;
    cin>>n>>m;
    fore(i,0,m){
        int x,y,w;cin>>x>>y>>w;--x;--y;
        edges.pb({w,i});
        adj.pb({x,y});
    }
    sort(ALL(edges));
    ll l = 0, r = 2*NMAX+1;
    while(l<=r){
        int me = (ll(l+r))/2;
        if(can(me))r=me-1;
        else l=me+1;
    }
    cout << l << "\n";
    return 0;
}
