// https://codeforces.com/group/5GNF7zti59/contest/535183/problem/A
#include <bits/stdc++.h>
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((ll)x.size())
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;

template<class T>
struct RMinQ {
  vector<vector<T>> jmp;
  RMinQ(const vector<T>& V) : jmp(1, V) {
    for (ll pw = 1, k = 1; pw * 2 <= SZ(V); pw *= 2, ++k) {
      jmp.emplace_back(SZ(V) - pw * 2 + 1);
      fore(j,0,SZ(jmp[k]))
        jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
    }
  }
  T query(ll a, ll b) {
    if (a == b) {
      return {1ll << 60, 1ll << 60};
    }
    ll dep = 63 - __builtin_clzll(b - a);
    return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
  }
};

template<class T>
struct RMaxQ {
  vector<vector<T>> jmp;
  RMaxQ(const vector<T>& V) : jmp(1, V) {
    for (ll pw = 1, k = 1; pw * 2 <= SZ(V); pw *= 2, ++k) {
      jmp.emplace_back(SZ(V) - pw * 2 + 1);
      fore(j,0,SZ(jmp[k]))
        jmp[k][j] = max(jmp[k - 1][j], jmp[k - 1][j + pw]);
    }
  }
  T query(ll a, ll b) {
    if (a == b) {
      return {-1, -1};
    }
    ll dep = 63 - __builtin_clzll(b - a);
    return max(jmp[dep][a], jmp[dep][b - (1 << dep)]);
  }
};

ll solve(const vi& ps) {
  ll n = ps.size();

  vi ps_inv(n);
  vii ps_i(n);
  fore(i, 0, n) {
    ll p = ps[i];
    ps_i[i] = {p, i};
    ps_inv[p] = i;
  }

  RMinQ mins(ps_i);
  RMaxQ maxs(ps_i);

  map<ii, ll> goods;
  ll val_count = 0;

  fore(i, 0, n) {
    ll pi = ps[i];
    auto [pl, l] = maxs.query(0, i);
    auto [pr, r] = mins.query(i + 1, n);
    if (pi == i && pl < i && pr > i) {
      val_count++;
    } else if (pi == i) {
      assert(i != 0 && i + 1 != n);

      auto [pl2, l2] = max(maxs.query(0, l), maxs.query(l + 1, i));
      auto [pr2, r2] = min(mins.query(i + 1, r), mins.query(r + 1, n));

      if (pl2 < pi && pi < pr2) {
        goods[{l, r}]++;
      }
    } else {
      ll j = ps_inv[i];
      assert(ps[j] == i);
      if (j < i) {
        auto [pl, l] = max(maxs.query(0, j), maxs.query(j + 1, i));
        if (ps[i] < i && pl < i) {
          goods[{j, i}]++;
        }
      } else {
        auto [pr, r] = min(mins.query(i + 1, j), mins.query(j + 1, n));
        if (i < ps[i] && i < pr) {
          goods[{i, j}]++;
        }
      }
    }
  }

  if (val_count == n) {
    return n - 2;
  }

  ll max_goods = 0;
  for (auto [_, c] : goods) {
    max_goods = max(max_goods, c);
  }

  return val_count + max_goods;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll t;
  cin >> t;
  while (t--) {
    ll n;
    cin >> n;
    vi ps(n);
    for (ll& p : ps) {
      cin >> p;
      p--;
    }
    ll ans = solve(ps);
    cout << ans << '\n';
  }
}
