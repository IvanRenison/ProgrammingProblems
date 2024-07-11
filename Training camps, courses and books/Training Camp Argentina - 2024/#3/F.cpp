// https://codeforces.com/group/5GNF7zti59/contest/535420/problem/F
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;

typedef vi T;
const T neut = vi(26, -1);
T f(T a, T b) {
  fore(i, 0, 26) {
    if (a[i] == -1) {
      a[i] = b[i];
    }
  }
  return a;
}
struct Tree {
  vector<T> s;
  ll n;
  Tree(ll n = 0, T def = neut) : s(2*n, def), n(n) {}
  void upd(ll pos, T val) {
    for (s[pos += n] = val; pos /= 2;)
      s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
  }
  T query(ll b, ll e) {
    T ra = neut, rb = neut;
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if (b % 2) ra = f(ra, s[b++]);
      if (e % 2) rb = f(s[--e], rb);
    }
    return f(ra, rb);
  }
};

typedef uint64_t ull;
struct H {
  ull x; H(ull x = 0) : x(x) {}
  H operator+(H o) { return x + o.x + (x + o.x < x); }
  H operator-(H o) { return *this + ~o.x; }
  H operator*(H o) {
    auto m = (__uint128_t)x * o.x;
    return H((ull)m) + (ull)(m >> 64);
  }
  ull get() const{ return x + !~x;}
  bool operator==(H o) const {return get() == o.get(); }
  bool operator<(H o) const {return get() < o.get(); }
};
static const H C = (ll)1e11 + 3;

struct HashInterval {
  vector<H> ha, pw;
  HashInterval(string& str) : ha(SZ(str)+1), pw(ha) {
    pw[0] = 1;
    fore(i, 0, SZ(str))
      ha[i+1] = ha[i]*C+str[i],
      pw[i+1] = pw[i] * C;
  }
  H hashInterval(ll a, ll b) {
    return ha[b] - ha[a] * pw[b - a];
  }
};

vector<bool> solve(const string& s, const viii& queries) {
  ll n = s.size(), m = queries.size();

  Tree t(n);
  fore(i, 0, n) {
    ll c = s[i] - 'a';
    vi v(26, -1);
    v[c] = i;
    t.upd(i, v);
  }

  vector<HashInterval> hashes;
  fore(c, 0, 26) {
    string sc;
    fore(i, 0, n) {
      sc += (s[i] - 'a' == c ? '1' : '0');
    }
    hashes.push_back(HashInterval(sc));
  }

  vector<bool> ans(m);
  fore(q, 0, m) {
    auto [x, y, len] = queries[q];
    vi firsts_pos = t.query(x, x + len);
    vi iso(26, -1);
    fore(c, 0, 26) {
      if (firsts_pos[c] != -1) {
        iso[c] = s[y + firsts_pos[c] - x] - 'a';
      }
    }

    bool this_ans = true;
    fore(c, 0, 26) {
      if (iso[c] != -1) {
        H hx = hashes[c].hashInterval(x, x + len);
        H hy = hashes[iso[c]].hashInterval(y, y + len);
        if (!(hx == hy)) {
          this_ans = false;
          break;
        }
      }
    }

    ans[q] = this_ans;
  }

  return ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll n, m;
  cin >> n >> m;
  string s;
  cin >> s;
  viii queries(m);
  for (auto& [x, y, len] : queries) {
    cin >> x >> y >> len;
    x--, y--;
  }

  vector<bool> ans = solve(s, queries);
  for (bool b : ans) {
    cout << (b ? "YES" : "NO") << '\n';
  }

}