// https://codeforces.com/group/3Zw9kC8et8/contest/620982/problem/C
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


typedef ll T;
typedef ll L;
const T tneut = 0;
const L lneut = 0;
T f(T a, T b) { return a + b; }
T apply(T v, L l, ll s, ll e) {
  return v + l * (e - s);
}
L comb(L a, L b) {
  return a + b;
}

struct Tree {
  ll n;
  vector<T> st;
  vector<L> lazy;
  Tree(ll n) : n(n), st(4 * n, tneut), lazy(4*n, lneut) {}

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


ll dist(const string& s, const string& t) {
  ll n = s.size();

  map<char, vi> apps;
  fore(i, 0, n) {
    char c = t[i];
    apps[c].push_back(i);
  }

  map<char, ll> is;

  Tree tree(n);

  ll ans = 0;

  fore(j, 0, n) {
    char c = s[j];

    ll i = apps[c][is[c]];
    is[c]++;

    ll d = tree.query(i, i + 1);
    ans += i - j + d;

    tree.upd(0, i, 1);
  }




/*   vi A, N, O, T;

  fore(i, 0, n) {
    char c = t[i];
    if (c == 'A') {
      A.push_back(i);
    } else if (c == 'N') {
      N.push_back(i);
    } else if (c == 'O') {
      O.push_back(i);
    } else {
      T.push_back(i);
    }
  }

  ll dA = 0, dN = 0, dO = 0, dT = 0;
  ll iA = 0, iN = 0, iO = 0, iT = 0;
  ll ans = 0;

  for (char c : s) {
    if (c == 'A') {
      assert(iA < A.size());
      ans += A[iA] + dA;
      iA++;
      dN++, dO++, dT++;
    } else if (c == 'N') {
      assert(iN < N.size());
      ans += N[iN] + dN;
      iN++;
      dA++, dO++, dT++;
    } else if (c == 'O') {
      assert(iO < O.size());
      ans += O[iO] + dO;
      iO++;
      dA++, dN++, dT++;
    } else {
      assert(iT < T.size());
      ans += T[iT] + dT;
      iT++;
      dA++, dN++, dO++;
    }
  }

  assert(iA == A.size());
  assert(iN == N.size());
  assert(iO == O.size());
  assert(iT == T.size()); */

  return ans;
}


string solve(string& s) {

  map<char, ll> cnt;
  for (char c : s) {
    cnt[c]++;
  }

  string ANOT = "ANOT";
  sort(ALL(ANOT));

  ll ans_val = -1;
  string ans;

  do {
    string t;
    for (char c : ANOT) {
      fore(_, 0, cnt[c]) {
        t += c;
      }
    }

    ll this_ans_val = dist(s, t);
    if (this_ans_val > ans_val) {
      ans = t;
      ans_val = this_ans_val;
    }
  } while (next_permutation(ALL(ANOT)));

  assert(ans_val != -1);

  return ans;
}



int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  //string a = "TONNA", b = "ANTON";
  //cout << dist(a, b) << endl;
  ll t;
  cin >> t;
  while (t--) {
    string a;
    cin >> a;
    string ans = solve(a);
    cout << ans << '\n';
    //cerr << dist(a, ans) << endl;
  }
}
// OAANTTON
// NNTTAAOO



