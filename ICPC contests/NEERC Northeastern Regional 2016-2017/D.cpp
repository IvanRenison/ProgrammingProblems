// https://codeforces.com/gym/
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;
typedef vector<bool> vb;
typedef long double ld;

/** Author: Stanford
 * Source: Stanford Notebook
 * License: MIT
 * Description: Solves a general linear maximization problem: maximize c^T x$ subject to Ax \le b$, x \ge 0$.
 * Returns -inf if there is no solution, inf if there are arbitrarily good solutions, or the maximum value of c^T x$ otherwise.
 * The input vector is set to an optimal x$ (or in the unbounded case, an arbitrary solution fulfilling the constraints).
 * Numerical stability is not guaranteed. For better performance, define variables such that x = 0$ is viable.
 * Usage:
 * vvd A = {{1,-1}, {-1,1}, {-1,-2}};
 * vd b = {1,1,-4}, c = {-1,-1}, x;
 * T val = LPSolver(A, b, c).solve(x);
 * Time: O(NM * \#pivots), where a pivot may be e.g. an edge relaxation. O(2^n) in the general case.
 * Status: seems to work?
 */
/* typedef double T; // long double, Rational, double + mod<P>...
typedef vector<T> vd;
typedef vector<vd> vvd;

const T eps = 1e-8, inf = 1/.0;
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
}; */

typedef vector<double> vd;
typedef vector<vd> vvd;

const double eps = 1e-8;
vector<int> X,Y;
vector<vector<double> > A;
vector<double> b,c;
double z;
int n,m;
void pivot(int x,int y){
  swap(X[y],Y[x]);
  b[x]/=A[x][y];
  fore(i,0,m)if(i!=y)A[x][i]/=A[x][y];
  A[x][y]=1/A[x][y];
  fore(i,0,n)if(i!=x&&abs(A[i][y])>eps){
    b[i]-=A[i][y]*b[x];
    fore(j,0,m)if(j!=y)A[i][j]-=A[i][y]*A[x][j];
    A[i][y]=-A[i][y]*A[x][y];
  }
  z+=c[y]*b[x];
  fore(i,0,m)if(i!=y)c[i]-=c[y]*A[x][i];
  c[y]=-c[y]*A[x][y];
}
pair<double,vector<double> > simplex( // maximize c^T x s.t. Ax<=b, x>=0
    vector<vector<double> > _A, vector<double> _b, vector<double> _c){
  // returns pair (maximum value, solution vector)
  A=_A;b=_b;c=_c;
  n=b.size();m=c.size();z=0.;
  X=vector<int>(m);Y=vector<int>(n);
  fore(i,0,m)X[i]=i;
  fore(i,0,n)Y[i]=i+m;
  while(1){
    int x=-1,y=-1;
    double mn=-eps;
    fore(i,0,n)if(b[i]<mn)mn=b[i],x=i;
    if(x<0)break;
    fore(i,0,m)if(A[x][i]<-eps){y=i;break;}
    assert(y>=0); // no solution to Ax<=b
    pivot(x,y);
  }
  while(1){
    double mx=eps;
    
    int x=-1,y=-1;
    fore(i,0,m)if(c[i]>mx)mx=c[i],y=i;
    if(y<0)break;
    double mn=1e200;
    fore(i,0,n)if(A[i][y]>eps&&b[i]/A[i][y]<mn)mn=b[i]/A[i][y],x=i;
    assert(x>=0); // c^T x is unbounded
    pivot(x,y);
  }
  vector<double> r(m);
  fore(i,0,n)if(Y[i]<m)r[Y[i]]=b[i];
  return {z,r};
}

pair<ll, vb> solve(ll k, ll ms, ll me, const vi& vs, const vi& ve) {
  ll n = vs.size();

  // We have n variables and n + 2 * (n - k + 1) constraints
  vvd A(n + 2 * (n - k + 1), vd(n));
  vd b(n + 2 * (n - k + 1));
  fore(i, 0, n) {
    A[i][i] = 1;
    b[i] = 1;
  }
  fore(i, 0, n - k + 1) {
    fore(j, i, i + k) {
      A[n + i][j] = 1;
      A[n + (n - k + 1) + i][j] = -1;
    }
    b[n + i] = k - me;
    b[n + (n - k + 1) + i] = -ms;
  }

  vd c(n);
  fore(i, 0, n) {
    c[i] = vs[i] - ve[i];
  }

  auto [val, x] = simplex(A, b, c);
  val += accumulate(ALL(ve), 0ll);

  //assert(val != inf && val != -inf);

  ll valll = (ll)(val + 0.5);
  //assert(abs(val - (ld)valll) < 10*eps);

  vb ans(n);
  fore(i, 0, n) {
    //assert(abs((ld)((ll)(x[i] + eps)) - x[i]) < 10*eps);
    ans[i] = x[i] + 0.5 > 1.0;
  }

  return {valll, ans};
}

optional<ll> checkAns(ll k, ll ms, ll me, const vi& vs, const vi& ve, const vb& ans) {
  ll n = vs.size();

  fore(i, 0, n - k + 1) {
    ll s = 0, e = 0;
    fore(j, i, i + k) {
      s += ans[j];
      e += !ans[j];
    }
    if (s < ms || e < me) {
      return false;
    }
  }

  ll sum = 0;
  fore(i, 0, n) {
    if (ans[i]) {
      sum += vs[i];
    } else {
      sum += ve[i];
    }
  }

  return sum;
}

ll force(ll k, ll ms, ll me, const vi& vs, const vi& ve) {
  ll n = vs.size();

  ll ans = 0;
  fore(x, 0, 1 << n) {
    vb mask(n);
    fore(i, 0, n) if (x & (1 << i)) {
      mask[i] = true;
    }

    auto val = checkAns(k, ms, me, vs, ve, mask);
    if (val.has_value()) {
      ans = max(ans, *val);
    }
  }

  return ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);
#ifdef ONLINE_JUDGE
  freopen("delight.in", "r", stdin);
  freopen("delight.out", "w", stdout);
#endif
#ifndef TEST
  ll n, k, ms, me;
  cin >> n >> k >> ms >> me;
  vi vs(n), ve(n);
  for (ll& s : vs) {
    cin >> s;
  }
  for (ll& e : ve) {
    cin >> e;
  }
  auto [val, ans] = solve(k, ms, me, vs, ve);
  // auto checked = checkAns(k, ms, me, vs, ve, ans);
  // assert(checked.has_value() && *checked == val);
  // assert(val == force(k, ms, me, vs, ve));
  cout << val << '\n';
  for (bool a : ans) {
    cout << (a ? 'S' : 'E');
  }
  cout << '\n';
#else
  fore(_, 0, 1000000) {
    ll n = rand() % 10 + 1;
    ll k = rand() % n + 1;
    ll ms = rand() % k;
    ll me = rand() % (k - ms + 1);
    vi vs(n), ve(n);
    for (ll& s : vs) {
      s = rand() % 10;
    }
    for (ll& e : ve) {
      e = rand() % 10;
    }
    auto [val, ans] = solve(k, ms, me, vs, ve);
    auto checked = checkAns(k, ms, me, vs, ve, ans);
    ll valf = force(k, ms, me, vs, ve);
    if (!checked.has_value() || val != *checked || val != valf) {
      cerr << "ERROR\n";
      cerr << n << ' ' << k << ' ' << ms << ' ' << me << '\n';
      for (ll& s : vs) {
        cerr << s << ' ';
      }
      cerr << '\n';
      for (ll& e : ve) {
        cerr << e << ' ';
      }
      cerr << '\n';
      cerr << "ans:\n" << val << '\n';
      for (bool a : ans) {
        cerr << (a ? 'S' : 'E');
      }
      cerr << '\n';
      cerr << "valf: " << valf << endl;
      return 1;
    }
  }
#endif
}
