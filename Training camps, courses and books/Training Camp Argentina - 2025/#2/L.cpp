// https://codeforces.com/group/3Zw9kC8et8/contest/620982/problem/L
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

const ll mod = 998244353;
const ll nmax = 1500000 + 5;

vi facts(nmax);
vi inv(nmax);
vi fact_invs(nmax);

void init() {
  facts[0] = 1;
  fore(i, 1, nmax) {
    facts[i] = facts[i - 1] * i;
    facts[i] %= mod;
  }

  inv[1] = 1;
  fact_invs[0] = fact_invs[1] = 1;
  fore(i, 2, nmax) {
    inv[i] = mod - mod / i * inv[mod % i] % mod;
    fact_invs[i] = (fact_invs[i - 1] * inv[i]) % mod;
  }
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);
  init();
  ll n;
  cin >> n;
  vi as(2 * n);
  for (ll& a : as) {
    cin >> a;
  }

  sort(ALL(as));

  ll ans = 0;

  ll magic = (((facts[2 * n] * fact_invs[n]) % mod) * fact_invs[n]) % mod;

  fore(i, 0, n) {
    ans -= as[i];
  }
  fore(i, n, 2 * n) {
    ans += as[i];
  }
  ans %= mod;
  ans *= magic;
  ans %= mod;

  cout << ans << '\n';
}