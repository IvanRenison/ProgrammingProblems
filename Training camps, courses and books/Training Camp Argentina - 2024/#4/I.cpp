// https://codeforces.com/group/5GNF7zti59/contest/535722/problem/I
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define SZ(x) ((ll)x.size())
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;

/** Author: chilli
 * Date: 2019-04-16
 * License: CC0
 * Source: based on KACTL's FFT
 * Description: ntt(a) computes $\hat f(k) = \sum_x a[x] g^{xk}$ for all k$, where g=\text{root}^{(mod-1)/N}$.
 * N must be a power of 2.
 * Useful for convolution modulo specific nice primes of the form ^a b+1$,
 * where the convolution result has size at most ^a$. For arbitrary modulo, see FFTMod.
   \texttt{conv(a, b) = c}, where c[x] = \sum a[i]b[x-i]$.
   For manual convolution: NTT the inputs, multiply
   pointwise, divide by n, reverse(start+1, end), NTT back.
 * Inputs must be in [0, mod).
 * Time: O(N \log N)
 * Status: stress-tested
 */
const ll mod = (119 << 23) + 1, root = 62; // = 998244353
// For p < 2^30 there is also e.g. 5 << 25, 7 << 26, 479 << 21
// and 483 << 21 (same root). The last two are > 10^9.
ll modpow(ll b, ll e) {
  ll ans = 1;
  for (; e; b = b * b % mod, e /= 2)
    if (e & 1) ans = ans * b % mod;
  return ans;
}
void ntt(vi &a) {
  ll n = SZ(a), L = 63 - __builtin_clzll(n);
  static vi rt(2, 1);
  for (static ll k = 2, s = 2; k < n; k *= 2, s++) {
    rt.resize(n);
    ll z[] = {1, modpow(root, mod >> s)};
    fore(i,k,2*k) rt[i] = rt[i / 2] * z[i & 1] % mod;
  }
  vi rev(n);
  fore(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
  fore(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
  for (ll k = 1; k < n; k *= 2)
    for (ll i = 0; i < n; i += 2 * k) fore(j,0,k) {
      ll z = rt[j + k] * a[i + j + k] % mod, &ai = a[i + j];
      a[i + j + k] = ai - z + (z > ai ? mod : 0);
      ai += (ai + z >= mod ? z - mod : z);
    }
}
vi conv(const vi &a, const vi &b) {
  if (a.empty() || b.empty()) return {};
  ll s = SZ(a) + SZ(b) - 1, B = 64 - __builtin_clzll(s),
      n = 1 << B;
  ll inv = modpow(n, mod - 2);
  vi L(a), R(b), out(n);
  L.resize(n), R.resize(n);
  ntt(L), ntt(R);
  fore(i,0,n)
    out[-i & (n - 1)] = (ll)L[i] * R[i] % mod * inv % mod;
  ntt(out);
  return {out.begin(), out.begin() + s};
}

vi solve(const string& s) {
  ll n = s.size();

  vi a(n);
  fore(i, 0, n) {
    if (s[i] == 'V') {
      a[i] = 1;
    } else if (s[i] == 'K') {
      a[i] = 2;
    }
  }
  vi b(a.rbegin(), a.rend());

  /*

    c[d] = ∑{i,j : j - i = d} (a[i] * a[j]) * (a[i] - a[j])**2
    ⇔ (j = d + i)
    c[d] = ∑{i} (a[i] * a[d+i]) * (a[i] - a[d+i])**2
    c[d] = ∑{i} (a[i] * a[d+i]) * a[i]**2 - 2 * (a[i] * a[d+i]) * a[i] * a[d+i] + (a[i] * a[d+i]) * a[d+i]**2
    c[d] = ∑{i} a[d+i] * a[i]**3 - 2 * a[i]**2 * a[d+i]**2 + a[i] * a[d+i]**3

    c0[d] = ∑{i} a[i]**3 * a[d+i]
    c1[d] = ∑{i} a[i]**2 * a[d+i]**2
    c2[d] = ∑{i} a[i] * a[d+i]**3


    c0[d] = ∑{i} a[i]**3 * a[d+i]
    c0[n-1-d] = ∑{i} a[i]**3 * a[n-1-d+i]
    c0[n-1-d] = ∑{i} a[i]**3 * b[d-i]

  */

  vi a2 = a, a3 = a, b2 = b, b3 = b;
  for (ll& a : a2) {
    a *= a;
  }
  for (ll& a : a3) {
    a *= a * a;
  }
  for (ll& b : b2) {
    b *= b;
  }
  for (ll& b : b3) {
    b *= b * b;
  }


  vi c0 = conv(a3, b);
  vi c1 = conv(a2, b2);
  vi c2 = conv(a, b3);

  vi c(n);
  fore(i, 0, n) {
    c[n - 1 - i] = c0[i] - 2 * c1[i] + c2[i];
  }

  vi ans;
  fore(i, 1, n) {
    bool valid = true;
    for (ll j = i; j < n; j += i) {
      if (c[j] != 0) {
        valid = false;
        break;
      }
    }
    if (valid) {
      ans.push_back(i);
    }
  }
  ans.push_back(n);

  return ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll t;
  cin >> t;
  while (t--) {
    ll n;
    cin >> n;
    string s;
    cin >> s;

    vi ans = solve(s);
    cout << ans.size() << '\n';
    for (ll x : ans) {
      cout << x << ' ';
    }
    cout << '\n';
  }
}