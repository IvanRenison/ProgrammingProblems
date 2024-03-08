// https://codeforces.com/contest/1250/problem/E
#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(x) x.begin(),x.end()
#define SZ(x) (ll(x.size()))
#define fore(i,a,b) for(ll i=a, gmat=b;i<gmat;++i)
#define pb push_back
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;

struct UF {
  vi e;
  UF(ll n) : e(n, -1) {}
  bool sameSet(ll a, ll b) { return find(a) == find(b); }
  ll size(ll x) { return -e[find(x)]; }
  ll find(ll x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
  bool join(ll a, ll b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (e[a] > e[b]) swap(a, b);
    e[a] += e[b]; e[b] = a;
    return true;
  }
};

ll inv(ll m, ll x) {
  ll ans = 0;

  fore(i, 0, m) {
    if (x & (1ll << i)) {
      ans |= 1ll << (m - 1 - i);
    }
  }

  return ans;
}

optional<vi> solve(ll m, ll k, const vi& bitss) {
  ll n = bitss.size();

  vi invs(n);
  fore(i, 0, n) {
    invs[i] = inv(m, bitss[i]);
  }

  auto valid = [&](ll x, ll y) {
    return __builtin_popcountll(x ^ y) <= m - k;
  };

  vector<vi> has(n), has_not(n);

  fore(i, 0, n) {
    ll x = bitss[i];
    fore(j, i + 1, n) {
      ll y = bitss[j];

      bool norm = valid(x, y), neg = valid(x, invs[j]);

      if (!norm && !neg) {
        return {};
      }

      if (!norm) {
        has_not[i].push_back(j), has_not[j].push_back(i);
      }
      if (!neg) {
        has[i].push_back(j), has[j].push_back(i);
      }
    }
  }

  UF uf(n);

  fore(i, 0, n) {
    for (ll j : has[i]) {
      if (j > i) {
        uf.join(i, j);
      }
    }
  }

  map<ll, vi> reps;

  fore(i, 0, n) {
    reps[uf.find(i)].push_back(i);
  }

  map<ll, set<ll>> reps_nots;

  fore(i, 0, n) {
    for (ll j : has_not[i]) {
      reps_nots[uf.find(i)].insert(uf.find(j));
    }
  }

  ll ans = 0;
  vi ans_v;

  set<ll> vis;
  for (const auto& [i, _] : reps) {
    if (!vis.count(i)) {
      map<ll, bool> colors;
      vis.insert(i);
      vi s = {i};
      colors[i] = true;

      while (!s.empty()) {
        ll j = s.back();
        s.pop_back();

        ll c = colors[j];

        for (ll k : reps_nots[j]) {
          if (!colors.count(k)) {
            vis.insert(k);
            colors[k] = !c;
            s.push_back(k);
          } else if (colors[k] == c) {
            return {};
          }
        }
      }

      array<ll, 2> totals = {0, 0};

      for (auto [j, c] : colors) {
        totals[c] += uf.size(j);
      }

      bool b = totals[0] > totals[1];
      ans += totals[b];
      for (auto [j, c] : colors) {
        if (c == b) {
          for (ll k : reps[j]) {
            ans_v.push_back(k);
          }
        }
      }
    }
  }

  return ans_v;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);

  ll t;
  cin >> t;

  while (t--) {
    ll n, m, k;
    cin >> n >> m >> k;

    vi bitss(n);
    for (ll& bits : bitss) {
      fore(i, 0, m) {
        char c;
        cin >> c;
        bits |= (ll(c == '1')) << i;
      }
    }

    auto ans = solve(m, k, bitss);
    if (!ans.has_value()) {
      cout << "-1\n";
    } else {
      cout << ans->size() << '\n';
      for (ll a : *ans) {
        cout << a + 1 << ' ';
      }
      cout << '\n';
    }
  }

  return 0;
}