// https://codeforces.com/gym/101492/problem/I
#include <bits/stdc++.h>
using namespace std;

#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) for (ll i = a, carranza = b; i < carranza; i++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (ll)(x).size()
#define mset(a, v) memset(a, v, sizeof(a))
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef tuple<ll,ll,ll> iii;
typedef vector<iii> viii;

const ll eps = 0, inf = 1ll << 60;

typedef ll T; // long double, Rational, double + mod<P>...
typedef vector<T> vd;
typedef vector<vd> vvd;

#define MP make_pair
#define ltj(X) if(s == -1 || MP(X[j],N[j]) < MP(X[s],N[s])) s=j

struct LPSolver {
	ll m, n;
	vi N, B;
	vvd D;

	LPSolver(const vvd& A, const vd& b, const vd& c) :
			m(SZ(b)), n(SZ(c)), N(n+1), B(m), D(m+2, vd(n+2)) {
		fore(i,0,m) fore(j,0,n) D[i][j] = A[i][j];
		fore(i,0,m) {B[i]=n+i; D[i][n]=-1; D[i][n+1]=b[i];}
		fore(j,0,n) { N[j] = j; D[m][j] = -c[j]; }
		N[n] = -1, D[m+1][n] = 1;
	}

	void pivot(ll r, ll s) {
		T *a = D[r].data(), inv = 1 / a[s];
		fore(i,0,m+2) if (i != r && abs(D[i][s]) > eps) {
			T *b = D[i].data(), inv2 = b[s] * inv;
			fore(j,0,n+2) b[j] -= a[j] * inv2;
			b[s] = a[s] * inv2;
		}
		fore(j,0,n+2) if (j != s) D[r][j] *= inv;
		fore(i,0,m+2) if (i != r) D[i][s] *= -inv;
		D[r][s] = inv;
		swap(B[r], N[s]);
	}

	bool simplex(ll phase) {
		ll x = m + phase - 1;
		for (;;) {
			ll s = -1;
			fore(j,0,n+1) if (N[j] != -phase) ltj(D[x]);
			if (D[x][s] >= -eps) return true;
			ll r = -1;
			fore(i,0,m) {
				if (D[i][s] <= eps) continue;
				if (r == -1 || MP(D[i][n+1] / D[i][s], B[i])
				       < MP(D[r][n+1] / D[r][s], B[r])) r = i;
			}
			if (r == -1) return false;
			pivot(r, s);
		}
	}

	T solve(vd &x) {
		ll r = 0;
		fore(i,1,m) if (D[i][n+1] < D[r][n+1]) r = i;
		if (D[r][n+1] < -eps) {
			pivot(r, n);
			if (!simplex(2) || D[m+1][n+1] < -eps) return -inf;
			fore(i,0,m) if (B[i] == -1) {
				ll s = 0;
				fore(j,1,n+1) ltj(D[i]);
				pivot(i, s);
			}
		}
		bool ok = simplex(1); x = vd(n);
		fore(i,0,m) if (B[i] < n) x[B[i]] = D[i][n+1];
		return ok ? D[m][n+1] : inf;
	}
};

ll solve(vi& Bs, viii& LRCs) {
  ll N = Bs.size(), M = LRCs.size();

  vvd a(M, vd(N));
  vd b(M);
  fore(i, 0, M) {
    auto [L, R, C] = LRCs[i];
    fore(j, L, R) {
      a[i][j] = 1;
    }
    b[i] = C;
  }
  vd c(N);
  fore(j, 0, N) {
    c[j] = Bs[j];
  }

  vd r(N);
  ll ans = LPSolver(a, b, c).solve(r);

  assert(ans != inf);

  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  ll N, M;
  cin >> N >> M;
  vi Bs(N);
  for (ll& B : Bs) {
    cin >> B;
  }
  viii LRCs(M);
  for (auto& [L, R, C] : LRCs) {
    cin >> L >> R >> C;
    L--;
  }

  ll ans = solve(Bs, LRCs);
  cout << ans << '\n';
}
