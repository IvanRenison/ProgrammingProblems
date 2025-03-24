// https://codeforces.com/gym/105789/problem/G
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((ll)x.size())
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define mset(a,v) memset((a),(v),sizeof(a))
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;

const ll inf = 1ll << 60;

typedef ii T;
typedef ll L;
const T tneut = {inf, -inf};
const L lneut = 0;
T f(T a, T b) {
  auto [am, aM] = a;
  auto [bm, bM] = b;
  return {min(am, bm), max(aM, bM)};
}
T apply(T v, L l, ll s, ll e) {
  auto [m, M] = v;
  return {m + l, M + l};
}
L comb(L a, L b) {
  return a + b;
}
struct Tree {
  ll n;
  vector<T> st;
  vector<L> lazy;
  Tree(ll n) : n(n), st(4*n, tneut), lazy(4*n, lneut) {}
  Tree(vector<T> a) : n(SZ(a)), st(4*n, tneut), lazy(4*n, lneut) {
    init(1, 0, n, a);
  }
  void init(ll k, ll s, ll e, vector<T>& a) {
    lazy[k] = lneut;
    if (s + 1 == e) {
      st[k] = a[s];
      return;
    }
    ll m = (s + e) / 2;
    init(2*k, s, m, a), init(2*k+1, m, e, a);
    st[k] = f(st[2*k], st[2*k+1]);
  }
  void push(ll k, ll s, ll e) {
    if (lazy[k] == lneut) return;
    st[k] = apply(st[k], lazy[k], s, e);
    if (s + 1 < e) {
      lazy[2*k] = comb(lazy[2*k], lazy[k]);
      lazy[2*k+1] = comb(lazy[2*k+1], lazy[k]);
    }
    lazy[k] = lneut;
  }
  void upd(ll k, ll s, ll e, ll a, ll b, L v) {
    push(k, s, e);
    if (s >= b || e <= a) return;
    if (s >= a && e <= b) {
      lazy[k] = comb(lazy[k], v);
      push(k, s, e);
      return;
    }
    ll m = (s + e) / 2;
    upd(2*k, s, m, a, b, v), upd(2*k+1, m, e, a, b, v);
    st[k] = f(st[2*k], st[2*k+1]);
  }
  T query(ll k, ll s, ll e, ll a, ll b) {
    if (s >= b || e <= a) return tneut;
    push(k, s, e);
    if (s >= a && e <= b) return st[k];
    ll m = (s + e) / 2;
    return f(query(2*k, s, m, a, b), query(2*k+1, m, e, a, b));
  }
  void upd(ll a, ll b, L v) { upd(1, 0, n, a, b, v); }
  T query(ll a, ll b) { return query(1, 0, n, a, b); }
};

string solve(vector<tuple<char, ll, ll>> segs) {
  ll N = segs.size();


  vi vals;
  for (auto [C, L, P] : segs) {
    vals.push_back(P);
    if (C == '-') {
      vals.push_back(P + L - 1);
      vals.push_back(P + L);
    } else {
      vals.push_back(P + 1);
    }
  }

  sort(ALL(vals));
  vals.erase(unique(ALL(vals)), vals.end());

  auto new_val = [&](ll x) -> ll {
    auto it = lower_bound(ALL(vals), x);
    return it - vals.begin();
  };

  for (auto& [C, L, P] : segs) {
    ll old_P = P;
    P = new_val(P);
    if (C == '-') {
      L = new_val(old_P + L - 1) - P + 1;
    }
  }

  Tree tree(vector<T>(vals.size(), {0, 0}));

  string ans;

  for (auto [C, L, P] : segs) {
    if (C == '|') {
      auto [m, M] = tree.query(P, P + 1);
      assert(m == M);
      tree.upd(P, P + 1, L);
      ans += 'S';
    } else {
      auto [m, M] = tree.query(P, P + L);
      if (m == M) {
        tree.upd(P, P + L, 1);
        ans += 'S';
      } else {
        ans += 'U';
      }
    }
  }

  return ans;
}

const ll P_lim = 20;
string force(vector<tuple<char, ll, ll>>& segs) {
  ll N = segs.size();

  string ans;
  vi vals(P_lim);
  for (auto [C, L, P] : segs) {
    if (C == '|') {
      vals[P] += L;
      ans += 'S';
    } else {
      bool all_eq = true;
      fore(i, 1, L) {
        if (vals[P] != vals[P + i]) {
          all_eq = false;
          break;
        }
      }
      if (all_eq) {
        fore(i, 0, L) {
          vals[P + i]++;
        }
        ans += 'S';
      } else {
        ans += 'U';
      }
    }
  }

  return ans;
}

int main(){
    ios::sync_with_stdio(0),cin.tie(0);
#ifndef TEST
  ll N;
  cin >> N;
  vector<tuple<char, ll, ll>> segs(N);
  for (auto& [C, L, P] : segs) {
    cin >> C >> L >> P;
  }

  string ans = solve(segs);
  cout << ans << '\n';
#else
  fore(_, 0, 1000000) {
    //cerr << "case " << _ << '\n';
    ll N = rand() % 15 + 1;
    vector<tuple<char, ll, ll>> segs(N);
    for (auto& [C, L, P] : segs) {
      if (rand() % 2) {
        C = '|';
      } else {
        C = '-';
      }
      L = rand() % 8 + 1;
      P = rand() % 8;
    }

    string ans = solve(segs);
    string ansf = force(segs);
    if (ans != ansf) {
      cerr << "ERROR\n";
      cerr << N << '\n';
      for (auto [C, L, P] : segs) {
        cerr << C << ' ' << L << ' ' << P << '\n';
      }
      cout << ans << '\n' << ansf << '\n';
      return 1;
    }
  }
#endif
}