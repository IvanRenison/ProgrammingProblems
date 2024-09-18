// https://codeforces.com/gym/105327/problem/I
#include <bits/stdc++.h>
using namespace std;

#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; i++)
#define ALL(x) begin(x), end(x)
#define SZ(x) (ll)(x).size()

typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef long double ld;

const ll V_lim = 1e6 + 1;

vi solveCount(vi& Vs, vi& Xs) {
  ll N = Vs.size(), Q = Xs.size();

  vector<vi> primes(V_lim);
  fore(i, 2, V_lim) {
    if (primes[i].empty()) {
      for (ll j = i; j < V_lim; j += i) {
        primes[j].push_back(i);
      }
    }
  }

  auto simp = [&](ll x) -> ll {
    for (ll p : primes[x]) {
      while ((x / p) % p == 0) {
        x /= p;
      }
    }
    return x;
  };

  for (ll& V : Vs) {
    V = simp(V);
  }
  for (ll& X : Xs) {
    X = simp(X);
  }

  vi count(V_lim);
  for (ll V : Vs) {
    ll n_primes = primes[V].size();
    fore(mask, 0, 1 << n_primes) {
      ll v = 1;
      fore(i, 0, n_primes) {
        if (mask & (1 << i)) {
          v *= primes[V][i];
        }
      }
      count[v]++;
    }
  }


  vi ans(Q);
  fore(q, 0, Q) {
    ll X = Xs[q];

    ll& this_ans = ans[q];

    ll n_primes = primes[X].size();
    fore(mask, 0, 1 << n_primes) {
      ll v = 1;
      fore(i, 0, n_primes) {
        if (mask & (1 << i)) {
          v *= primes[X][i];
        }
      }

      if (__builtin_popcountll(mask) & 1) {
        this_ans -= count[v];
      } else {
        this_ans += count[v];
      }
    }

  }

  return ans;
}

const ll mod = 1e9 + 7;

struct Mod {
  ll x;
  Mod(ll xx) : x(xx) {}
  Mod operator*(Mod b) { return Mod((x * b.x) % mod); }
  Mod operator^(ll e) {
    if (!e) return Mod(1);
    Mod r = *this ^ (e / 2);
    r = r * r;
    return e & 1 ? *this * r : r;
  }
};

vector<Mod> solve(vi& Vs, vi& Xs) {
  vi ansC = solveCount(Vs, Xs);
  vector<Mod> ans;
  for (ll a : ansC) {
    ans.push_back(Mod(2) ^ a);
  }
  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  ll N;
  cin >> N;
  vi Vs(N);
  for (ll& V : Vs) {
    cin >> V;
  }
  ll Q;
  cin >> Q;
  vi Xs(Q);
  for (ll& X : Xs) {
    cin >> X;
  }

  auto ans = solve(Vs, Xs);
  for (Mod a : ans) {
    cout << a.x << '\n';
  }

}
