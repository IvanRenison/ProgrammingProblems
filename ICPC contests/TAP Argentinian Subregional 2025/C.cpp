// https://codeforces.com/gym/106054/problem/C
#include <bits/stdc++.h>
using namespace std;

#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) for (ll i = a, teo = b; i < teo; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (ll)(x).size()
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;

ll solve(vi& Ps) {
  ll N = Ps.size();

  vi Ps2(2 * N);
  fore(i, 0, 2 * N) {
    Ps2[i] = i + Ps[i % N];
  }


  map<ll, ll> count;

  fore(i, 0, N) {
    count[Ps2[i]]++;
  }

  ll ans = N;

  fore(i, 0, N) {
    assert(count[Ps2[i]] >= 1);
    ans += 2 * (count[Ps2[i]] - 1);
    count[Ps2[i]]--;
    count[Ps2[i + N]]++;
  }

  return ans;
}

vi rot(vi Ps, ll r) {
  ll N = Ps.size();
  vi ans(N);
  fore(i, 0, N) {
    ans[i] = Ps[(i + r) % N];
  }
  return ans;
}

ll force(vi Ps) {
  ll N = Ps.size();

  ll ans = 0;

  fore(r, 0, N) {
    vi rs = rot(Ps, r);
    fore(i, 0, N) {
      if (rs[rs[i]] == i) {
        ans++;
      }
    }
  }

  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

#ifndef TEST
  ll N;
  cin >> N;
  vi Ps(N);
  for (ll& P : Ps) {
    cin >> P;
    P--;
  }


  ll ans = solve(Ps);
	cout << ans << '\n';

#else
  fore(tc, 0, 10000) {
    ll N = rand() % 3 + 1;

    vi Ps(N);
    iota(ALL(Ps), 0ll);

    random_shuffle(ALL(Ps));

    ll ans = solve(Ps);
    ll ansf = force(Ps);
    if (ans != ansf) {
      cout << N << '\n';
      for (ll P : Ps) {
        cout << P + 1 << ' ';
      }
      cout << '\n';
      cout << "ans: " << ans << '\n';
      cout << "ansf: " << ansf << '\n';
      return 1;
    }

  }
#endif
}
