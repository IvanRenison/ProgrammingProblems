// https://codeforces.com/gym/102861/problem/I
#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; i++)
#define ALL(x) begin(x), end(x)
#define SZ(x) (ll)(x).size()
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

ll euclid(ll a, ll b, ll& x, ll& y) {
  if (!b) return x = 1, y = 0, a;
  ll d = euclid(b, a % b, y, x);
  return y -= a/b * x, d;
}
const ll mod = 1000000007;
struct Mod {
  ll x;
  Mod(ll xx = 0) : x(xx) {}
  Mod operator+(Mod b) { return Mod((x + b.x) % mod); }
  Mod operator-(Mod b) { return Mod((x - b.x + mod) % mod); }
  Mod operator*(Mod b) { return Mod((x * b.x) % mod); }
  Mod operator/(Mod b) { return *this * invert(b); }
  Mod invert(Mod a) {
    ll x, y, g = euclid(a. x, mod, x, y);
    assert(g == 1);
    return Mod((x + mod) % mod);
  }
};

typedef pair<Mod, Mod> mm;
typedef vector<mm> vmm;

Mod solve(const vi& Ps) {
  ll N = Ps.size() + 1;

  vector<vi> suns(N);
  fore(i, 0, N - 1) {
    suns[Ps[i]].push_back(i + 1);
  }

  // (no se cuanto valgo, si lo se)
  function<mm(ll)> f = [&](ll u) -> mm {
    if (suns[u].empty()) {
      return {1, 1};
    }

    ll k = suns[u].size();
    vmm recs(k);
    fore(i, 0, k) {
      recs[i] = f(suns[u][i]);
    }

    vector<Mod> prod_pref(k + 1), prod_pos(k + 1);
    prod_pref[0] = 1;
    prod_pos[k] = 1;
    fore(i, 0, k) {
      prod_pref[i + 1] = prod_pref[i] * recs[i].first;
      prod_pos[k - i - 1] = prod_pos[k - i] * recs[k - i - 1].first;
    }

    Mod ans_yes = 0;
    fore(i, 0, k) {
      Mod this_ans = prod_pref[i] * prod_pos[i + 1] * recs[i].second;
      ans_yes = ans_yes + this_ans;
    }

    Mod ans_no = ans_yes + prod_pref[k];

    return {ans_no, ans_yes};
  };

  auto [ans_no, ans_yes] = f(0);

  return ans_no;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  ll N;
  cin >> N;
  vi Ps(N - 1);
  for (ll& P : Ps) {
    cin >> P;
    P--;
  }

  Mod ans = solve(Ps);

  cout << ans.x << '\n';

/*   fore(_, 0, 10) {

    ll N = 1e5;
    vi Ps(N - 1);
    fore(i, 0, N - 1) {
      Ps[i] = rand() % (i + 1);
    }

    Mod ans = solve(Ps);
  } */

}
