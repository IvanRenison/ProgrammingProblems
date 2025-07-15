// https://codeforces.com/group/3Zw9kC8et8/contest/620982/problem/F
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


typedef unsigned long long ull;
struct H {
  ull x;
  H(ull x = 0) : x(x) {}
  H operator+(H o) { return x + o.x + (x + o.x < x); }
  H operator-(H o) { return *this + ~o.x; }
  H operator*(H o) { auto m = (__uint128_t)x * o.x;
    return H((ull)m) + (ull)(m >> 64); }
  ull get() const { return x + !~x; }
  bool operator==(H o) const { return get() == o.get(); }
  bool operator<(H o) const { return get() < o.get(); }
};
static const H C = (ll)1e11 + 3;

struct HashInterval {
  vector<H> ha, pw;
  HashInterval(string& str) : ha(SZ(str) + 1), pw(ha) {
    pw[0] = 1;
    fore(i, 0, SZ(str)) {
      ha[i+1] = ha[i] * C + str[i];
      pw[i+1] = pw[i] * C;
    }
  }
  H hashInterval(ll a, ll b) {
    //assert(a < b);
    //assert(b < ha.size());
    return ha[b] - ha[a] * pw[b - a];
  }
};

ll solve(string& s, string& t) {
  ll n = s.size(), m = t.size();

  if (s[0] == '1') {
    for (char& c : s) {
      if (c == '0') {
        c = '1';
      } else {
        c = '0';
      }
    }

  }

  ll cnt0 = 0, cnt1 = 0;
  for (char c : s) {
    cnt0 += c == '0';
    cnt1 += c == '1';
  }

  ll first1 = -1;
  fore(i, 0, n) {
    if (s[i] == '1') {
      first1 = i;
      break;
    }
  }

  HashInterval ht(t);

  ll ans = 0;
  fore(l0, 1, m) {
    ll totall0 = l0 * cnt0;
    if (totall0 >= m) {
      break;
    }
    ll totall1 = m - totall0;

    if (totall1 % cnt1 == 0) {
      ll l1 = totall1 / cnt1;

      ll a0 = 0;
      ll b0 = l0;

      ll a1 = first1 * l0;
      ll b1 = a1 + l1;

      H h0 = ht.hashInterval(a0, b0);
      H h1 = ht.hashInterval(a1, b1);

      if (h0 == h1) {
        goto next;
      }

      ll i = 0;
      for (char c : s) {
        if (c == '0') {
          H h = ht.hashInterval(i, i + l0);
          if (!(h0 == h)) {
            goto next;
          }
          i += l0;
        } else {
          H h = ht.hashInterval(i, i + l1);
          if (!(h1 == h)) {
            goto next;
          }
          i += l1;
        }
      }
      ans++;
    }


    next:;
  }

  return ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);
  string s, t;
  cin >> s >> t;

  ll ans = solve(s, t);
  cout << ans << '\n';
}