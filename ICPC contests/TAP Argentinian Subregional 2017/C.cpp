// https://codeforces.com/group/YjFmW2O15Q/contest/101811

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (x).size()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;


bool solve(ull K, const vi& Gs) {
  ull N = Gs.size();


  vi diffs(N);
  fore(i, 0, N) {
    ull j = (i + N - 1) % N;
    diffs[i] = Gs[i] - Gs[j];
  }

  ull D = gcd(K, N);
  ull C = N / D;

  vi vals(N);

  fore(s, 0, D) {
    ll m = 0, acc = 0;
    fore(j, 0, C) {
      ll diff = diffs[(s + j * K) % N];
      acc += diff;
      m = min(m, acc);
    }

    if (acc != 0) {
      return false;
    }

    ll d = diffs[s] - m;
    vals[s] = d;
    fore(j, 1, C) {
      d += diffs[(s + j * K) % N];
      vals[(s + j * K) % N] = d;
    }
  }

  fore(i, 0, N) {
    ll acc = 0;
    fore(k, 0, K) {
      acc += vals[(i - k + N) % N];
    }
    if ((Gs[i] - acc) < 0 || (Gs[i] - acc) % (K / D) != 0) {
      return false;
    }
  }

  return true;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ull N, K;
  cin >> N >> K;
  vi Gs(N);
  for (ll& G : Gs) {
    cin >> G;
  }

  bool ans = solve(K, Gs);
  if (ans) {
    cout << "S\n";
  } else {
    cout << "N\n";
  }

}
