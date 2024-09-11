// https://contest.ucup.ac/contest/1784/problem/9246
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


const ll n_max = 5000;

typedef bitset<(size_t)n_max> B;

optional<iii> solve(vector<B>& adj) {
  ll n = adj.size();

  vi ans;
  fore(i, 0, n) {
    B x = adj[i];
    x[i] = 1;
    fore(j, 0, n) {
      if (adj[i][j]) {
        x |= adj[j];
      }
    }


    ll count = x.count();
    if (count == n) {
      ans.push_back(i);
      if (ans.size() >= 3) {
        break;
      }
    }
  }

  if (ans.size() < 3)  {
    return {};
  }

  return {{ans[0], ans[1], ans[2]}};
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll n;
  cin >> n;
  vector<B> adj(n);
  fore(i, 0, n) {
    fore(j, 0, n) {
      char c;
      cin >> c;
      adj[i][j] = c == '1';
    }
  }

  auto ans = solve(adj);
  if (!ans.has_value()) {
    cout << "NOT FOUND\n";
  } else {
    auto [a, b, c] = *ans;
    cout << a+1 << ' ' << b+1 << ' ' << c+1 << '\n';
  }
}
