// https://codeforces.com/gym/104505/problem/A
#include <bits/stdc++.h>
#define ALL(x) x.begin(),x.end()
#define SZ(x) (ll(x.size()))
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef tuple<ll, ll, ll> iii;

const ll maxk = 2e5;

const ll mod = 1e9 + 7;

ll euclid(ll a, ll b, ll &x, ll &y) {
  if (!b) return x = 1, y = 0, a;
  ll d = euclid(b, a % b, y, x);
  return y -= a/b * x, d;
}

struct Mod {
  ll x;
  Mod(ll xx = 0) : x((xx + mod) % mod) {}
  Mod operator+(Mod b) const { return Mod((x + b.x) % mod); }
  Mod operator-(Mod b) const { return Mod((x + mod - b.x) % mod); }
  Mod operator*(Mod b) const { return Mod((x * b.x) % mod); }
  Mod operator/(Mod b) const {return *this * invert(b); }
  Mod invert(Mod a) const {
    ll x, y, g = euclid(a.x, mod, x, y);
    assert(g == 1);
    return Mod((x + mod) % mod);
  }
  Mod operator^(ll e) const {
    if (!e) return Mod(1);
    Mod r = *this ^ (e / 2); r = r * r;
    return e&1 ? *this * r : r;
  }
};

typedef vector<Mod> vm;
typedef pair<Mod, Mod> mm;
typedef vector<mm> vmm;

vm facts(2 * maxk + 10);
vm inv_facts(2 * maxk + 10);

void init() {
  facts[0] = Mod(1);
  fore(i, 1, 2 * maxk + 10) {
    facts[i] = facts[i - 1] * Mod(i);
  }
  fore(i, 0, 2 * maxk + 10) {
    inv_facts[i] = Mod(1) / facts[i];
  }
}


Mod interpolate(vm ys, Mod x) { // O(n log n)
  ll n = ys.size();

  if (x.x < n) {
    return ys[x.x];
  }

  Mod prod_num = Mod(1);
  fore(i, 0, n) {
    Mod xi = Mod(i);
    prod_num = prod_num * (x - xi);
  }

  Mod ans = Mod(0);

  fore(i, 0, n) {
    Mod xi = Mod(i), yi = ys[i];
    Mod term = yi;
    term = term * prod_num / (x - xi);
    term = term * inv_facts[i] * inv_facts[n - 1 - i];
    if ((n - 1 - i) % 2 == 1) {
      term = term * Mod(-1);
    }

    ans = ans + term;
  }

  return ans;
}

Mod solveNum(ll n, ll k) {
  // sum (i = 1 to n) i^k * (n - i + 1)^k

  vm ys(2 * k + 2, Mod(0));

  fore(i, 1, 2 * k + 2) {
    ys[i] = ys[i - 1] + (Mod(i) ^ k) * (Mod(n - i + 1) ^ k);
  }

  Mod ans = interpolate(ys, Mod(n));

  return ans;
}

/* Mod solveNumForce(ll n, ll k) {
  Mod ans = Mod(0);
  fore(i, 1, n + 1) {
    ans = ans + (Mod(i) ^ k) * (Mod(n - i + 1) ^ k);
    cerr << " + " << (Mod(i) ^ k).x << " * " << (Mod(n - i + 1) ^ k).x;
  }
  cerr << '\n';

  return ans;
} */

Mod solveDem(ll n, ll k) {
  // sum (i = 1 to n) i^k

  vm ys(k + 2, Mod(0));
  fore(i, 1, k + 2) {
    ys[i] = ys[i - 1] + (Mod(i) ^ k);
  }

  Mod ans = interpolate(ys, Mod(n));

  return ans;
}



Mod solve(ll n, ll k) {
  Mod num = solveNum(n, k);
  //Mod numf = solveNumForce(n, k);
  //assert(num.x == numf.x);
  Mod dem = solveDem(n, k);

  Mod ans = num / dem;

  return ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  init();

  ll n, k;
  cin >> n >> k;

  Mod ans = solve(n, k);

  cout << ans.x << '\n';

  return 0;
}
