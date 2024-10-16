// https://codeforces.com/gym/100553
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define SZ(x) ((ll)x.size())
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define ALL(x) x.begin(),x.end()
#define mset(a,v) memset((a),(v),sizeof(a))
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef tuple<ll,ll,ll> iii;
typedef vector<iii> viii;
typedef __float128 ld;
typedef vector<ld> vd;

const ld zero = 0;
const ld eps = 1e-16;

optional<tuple<ld, ld, vd>> solve(ll A, ll B, viii& gabs) {
  ll n = gabs.size();

  vi ord(n);
  iota(ALL(ord), 0);
  sort(ALL(ord), [&](ll i, ll j) {
    auto [gi, ai, bi] = gabs[i];
    auto [gj, aj, bj] = gabs[j];
    // ai / bi > aj / bj
    return ai * bj > aj * bi;
  });

  vd ans(n);
  ld A_sum = 0, B_sum = 0;

  for (ll i : ord) {
    auto [g, a, b] = gabs[i];
    ld d = b == 0 ? (ld)g : ((ld)B - B_sum) / (ld)b;
    d = max(zero, min(d, (ld)g));

    A_sum += d * (ld)a;
    B_sum += d * (ld)b;
    ans[i] = d;
  }

  //assert(B_sum <= (ld)B + eps);
  if (A_sum + eps < (ld)A) {
    return {};
  }

  B_sum = min((ld)B, max(B_sum, zero));
  A_sum = max((ld)A, A_sum);

  return {{A_sum, B_sum, ans}};
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);
#ifdef ONLINE_JUDGE
  freopen("burrito.in", "r", stdin);
  freopen("burrito.out", "w", stdout);
#endif

  ll n, A, B;
  cin >> n >> A >> B;
  viii gabs(n);
  for (auto& [g, a, b] : gabs) {
    cin >> g >> a >> b;
  }

  auto ans = solve(A, B, gabs);
  if (ans) {
    auto [a, b, vals] = *ans;
    cout << setprecision(12) << fixed;
    cout << (long double)a << ' ' << (long double)b << '\n';
    for (ld v : vals) {
      cout << (long double)v << ' ';
    }
    cout << '\n';
  } else {
    cout << "-1 -1\n";
  }

}