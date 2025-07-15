// https://codeforces.com/group/3Zw9kC8et8/contest/620982/problem/A
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
typedef vector<ii> vii;

ll inf = 1ll << 60;



#include "ext/pb_ds/priority_queue.hpp"

const ll INF = numeric_limits<ll>::max() / 4;

struct MCMF {
    struct edge {
        ll from, to, rev;
        ll cap, cost, flow;
    };
    ll N;
    vector<vector<edge>> ed;
    vi seen;
    vi dist, pi;
    vector<edge*> par;

    MCMF(ll N):N(N), ed(N), seen(N), dist(N), pi(N), par(N) {}

    void addEdge(ll from, ll to, ll cap, ll cost){
        if (from == to) return;
        ed[from].pb(edge{from,to,SZ(ed[to]),cap,cost,0});
        ed[to].pb(edge{to,from,SZ(ed[from])-1,0,-cost,0});
    }

    void path(ll s){
        fill(ALL(seen), 0);
        fill(ALL(dist), INF);
        dist[s] = 0;ll di;

        __gnu_pbds::priority_queue<ii> q;
        vector<decltype(q)::point_iterator> its(N);
        q.push({0,s});

        while(!q.empty()){
            s = q.top().snd; q.pop();
            seen[s] = 1;di = dist[s] + pi[s];
            for(edge &e: ed[s]) if(!seen[e.to]){
                ll val = di - pi[e.to] + e.cost;
                if(e.cap - e.flow > 0 && val < dist[e.to]){
                    dist[e.to] = val;
                    par[e.to] = &e;
                    if(its[e.to] == q.end())
                        its[e.to] = q.push({-dist[e.to],e.to});
                    else
                        q.modify(its[e.to], {-dist[e.to],e.to});
                }
            }
        }
        fore(i,0,N) pi[i] = min(pi[i] + dist[i], INF);
    }

    ii maxflow(ll s, ll t){
        ll totflow = 0, totcost = 0;
        while(path(s), seen[t]){
            ll fl = INF;
            for(edge* x = par[t]; x; x = par[x->from])
                fl = min(fl, x->cap - x->flow);
            totflow += fl;
            for(edge *x = par[t]; x; x = par[x->from]){
                x->flow += fl;
                ed[x->to][x->rev].flow -= fl;
            }
        }
        fore(i,0,N) for (edge& e:ed[i])
            totcost += e.cost * e.flow;
        return {totflow, totcost/2};
    }

    void setpi(ll s){
        fill(ALL(pi),INF); pi[s] = 0;
        ll it = N, ch = 1; ll v;
        while(ch-- && it--)
            fore(i,0,N) if(pi[i] != INF)
                for(edge &e : ed[i]) if(e.cap)
                    if((v = pi[i] + e.cost) < pi[e.to])
                        pi[e.to] = v, ch = 1;
        assert(it >= 0);
    }
};






vi solve(ll k, vii& abs) {
  ll n = abs.size();

  ll N = 1 + n + k + 1 + 1;
  MCMF mcmf(N);
  fore(i, 0, n) {
    mcmf.addEdge(0, 1 + i, 1, 0);
  }
  fore(i, 0, n) {
    auto [ai, bi] = abs[i];
    fore(j, 0, k) {
      mcmf.addEdge(1 + i, 1 + n + j, 1, -(ai + bi * j));
    }
    mcmf.addEdge(1 + i, 1 + n + k, 1, -(bi * (k - 1)));
  }
  fore(j, 0, k) {
    mcmf.addEdge(1 + n + j, 1 + n + k + 1, 1, 0);
  }
  mcmf.addEdge(1 + n + k, 1 + n + k + 1, n - k, 0);

  mcmf.setpi(0);
  mcmf.maxflow(0, N - 1);

  vi summon(k, -1);
  vi killes;
  fore(i, 0, n) {
    bool sum = false;
    for (auto e : mcmf.ed[1 + i]) {
      if (e.flow == 1) {
        ll j = e.to - 1 - n;
        if (j == k) {
          break;
        }
        assert(summon[j] == -1);
        summon[j] = i;
        sum = true;
        break;
      }
    }
    if (!sum) {
      killes.push_back(i);
    }
  }


  vi ans;
  fore(j, 0, k - 1) {
    ans.push_back(summon[j] + 1);
  }
  for (ll i : killes) {
    ans.push_back(i + 1);
    ans.push_back(-i - 1);
  }
  ans.push_back(summon.back() + 1);

  return ans;

/*   ll sum_bs = 0;
  for (auto [a, b] : abs) {
    sum_bs += b;
  }

  vi ans;
  vector<bool> used(n, false);

  fore(c, 0, k - 1) {
    ll best_val = -1;
    ll best_i = -1;

    fore(i, 0, n) if (!used[i]) {
      auto [a, b] = abs[i];
      ll this_val = a + sum_bs - b;

      if (this_val > best_val) {
        best_val = this_val;
        best_i = i;
      }
    }

    assert(best_i != -1);

    ans.push_back(best_i + 1);
    used[best_i] = true;

    sum_bs -= abs[best_i].second;
  }

  ll best_val = -inf;
  ll best_i = -1;
  fore(i, 0, n) if (!used[i]) {
    auto [a, b] = abs[i];
    ll this_val = a - b * (k - 1);

    if (this_val > best_val) {
      best_val = this_val;
      best_i = i;
    }
  }

  used[best_i] = true;

  fore(i, 0, n) if (!used[i]) {
    ans.push_back(i + 1);
    ans.push_back(-i - 1);
  }

  ans.push_back(best_i); */

/*   return ans; */
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll T;
  cin >> T;
  while (T--) {
    ll n, k;
    cin >> n >> k;
    vii abs(n);
    for (auto& [a, b] : abs) {
      cin >> a >> b;
    }
    vi ans = solve(k, abs);
    cout << ans.size() << '\n';
    for (ll a : ans) {
      cout << a << ' ';
    }
    cout << '\n';
  }


}