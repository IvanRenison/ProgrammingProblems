// https://codeforces.com/group/5GNF7zti59/contest/534709/problem/J
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((ll)x.size())
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef long double ld;

const ld eps = 1e-10;
const ld inf = 1e60;

/** Author: Ulf Lundstrom
 * Date: 2009-02-26
 * License: CC0
 * Source: My head with inspiration from tinyKACTL
 * Description: Class to handle points in the plane.
 * 	T can be e.g. double or long long. (Avoid ll.)
 * Status: Works fine, used a lot
 */
template <class T> ll sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
  typedef Point P;
  T x, y;
  explicit Point(T x=0, T y=0) : x(x), y(y) {}
  bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
  bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
  P operator+(P p) const { return P(x+p.x, y+p.y); }
  P operator-(P p) const { return P(x-p.x, y-p.y); }
  P operator*(T d) const { return P(x*d, y*d); }
  P operator/(T d) const { return P(x/d, y/d); }
  T dot(P p) const { return x*p.x + y*p.y; }
  T cross(P p) const { return x*p.y - y*p.x; }
  T cross(P a, P b) const { return (a-*this).cross(b-*this); }
  T dist2() const { return x*x + y*y; }
  ld dist() const { return sqrt((ld)dist2()); }
  // angle to x-axis in interval [-pi, pi]
  ld angle() const { return atan2(y, x); }
  ld angle(P p) { // redefine acos for values out of range
    return acos(dot(p)/(dist()*p.dist()));
  }
  P unit() const { return *this/dist(); } // makes dist()=1
  P perp() const { return P(-y, x); } // rotates +90 degrees
  P normal() const { return perp().unit(); }
  // returns point rotated 'a' radians ccw around the origin
  P rotate(ld a) const {
    return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
  P rot(P r){return P(cross(r),dot(r));}
  bool left(P p, P q){ // is it to the left of directed line pq?
    return (q-p).cross(*this-p) > eps;}
  friend ostream& operator<<(ostream& os, P p) {
    return os << "(" << p.x << "," << p.y << ")"; }
};

typedef Point<ld> P;


/** Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source: Basic math
 * Description:\
\begin{minipage}{75mm}
Returns the signed distance between point p and the line containing points a and b.
Positive value on left side and negative on right as seen from a towards b. a==b gives nan.
P is supposed to be Point<T> or Point3D<T> where T is e.g. double or ll.
It uses products in intermediate steps so watch out for overflow if using ll or ll.
Using Point3D will always give a non-negative distance. For Point3D, call .dist on the result of the cross product.
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{content/geometry/lineDistance}
\end{minipage}
 * Status: tested
 */
ld lineDist(const P& a, const P& b, const P& p) {
  return (ld)(b-a).cross(p-a)/(b-a).dist();
}

/** Author: Victor Lecomte, chilli
 * Date: 2019-05-05
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description:\
\begin{minipage}{75mm}
If a unique intersection point of the lines going through s1,e1 and s2,e2 exists \{1, point} is returned.
If no intersection point exists \{0, (0,0)} is returned and if infinitely many exists \{-1, (0,0)} is returned.
The wrong position will be returned if P is Point<ll> and the intersection point does not have integer coordinates.
Products of three coordinates are used in intermediate steps so watch out for overflow if using ll or ll.
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{content/geometry/lineIntersection}
\end{minipage}
 * Usage:
 * 	auto res = lineInter(s1,e1,s2,e2);
 * 	if (res.first == 1)
 * 		cout << "intersection point at " << res.second << endl;
 * Status: stress-tested, and tested through half-plane tests
 */
template<class P>
pair<ll, P> lineInter(P s1, P e1, P s2, P e2) {
  auto d = (e1 - s1).cross(e2 - s2);
  if (d == 0) // if parallel
    return {-(abs(s1.cross(e1, s2)) < eps), P(0, 0)};
  auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
  return {1, (s1 * p + e1 * q) / d};
}

enum TY { BAD, JUST, GOOD };
TY type(P p, P q, P a, P b, P c) {
  auto inter = lineInter(p, q, b, c);
  if (inter.first <= 0) {
    return JUST;
  }

  ld ad = lineDist(p, q, a);
  ld bd = lineDist(p, q, b);
  ld cd = lineDist(p, q, c);

  if (ad >= bd - eps && cd >= bd - eps) {
    return GOOD;
  } else {
    return BAD;
  }
}


/** Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source: tinyKACTL
 * Description: Returns twice the signed area of a polygon.
 *  Clockwise enumeration gives negative area. Watch out for overflow if using ll as T!
 * Status: Stress-tested and tested on kattis:polygonarea
 */
template<class T>
T polygonArea2(vector<Point<T>>& v) {
  T a = v.back().cross(v[0]);
  fore(i,0,SZ(v)-1) a += v[i].cross(v[i+1]);
  return a;
}

/** Author: Stjepan Glavina, chilli
 * Date: 2019-05-05
 * License: Unlicense
 * Source: https://github.com/stjepang/snippets/blob/master/convex_hull.cpp
 * Description:
\\begin{minipage}{75mm}
Returns a vector of the points of the convex hull in counter-clockwise order.
Points on the edge of the hull between two other points are not considered part of the hull.
\end{minipage}
\begin{minipage}{15mm}
\vspace{-6mm}
\includegraphics[width=\textwidth]{content/geometry/ConvexHull}
\vspace{-6mm}
\end{minipage}
 * Time: O(n \log n)
 * Status: stress-tested, tested with kattis:convexhull
 */
vector<P> convexHull(vector<P> pts) {
  if (SZ(pts) <= 1) return pts;
  sort(ALL(pts));
  vector<P> h(SZ(pts)+1);
  ll s = 0, t = 0;
  for (ll it = 2; it--; s = --t, reverse(ALL(pts)))
    for (P p : pts) {
      while (t >= s + 2 && h[t-2].cross(h[t-1], p) <= 0) t--;
      h[t++] = p;
    }
  return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}

// Compute Minkowski sum of two CONVEX polygons (remove collinear first)
// Returns answer in CCW order
void reorder(vector<P> &p){
  if(!p[2].left(p[0],p[1])) reverse(ALL(p));
  ll pos=0;
  fore(i,1,SZ(p)) if(P(p[i].y,p[i].x) < P(p[pos].y,p[pos].x)) pos=i;
  rotate(p.begin(), p.begin()+pos, p.end());
}
vector<P> minkowski_sum(vector<P> p, vector<P> q){
  if(min(SZ(p),SZ(q))<3){
    vector<P> v;
    for(P pp:p) for(P qq:q) v.pb(pp+qq);
    return convexHull(v);
  }
  reorder(p); reorder(q);
  fore(i,0,2) p.pb(p[i]), q.pb(q[i]);
  vector<P> r;
  ll i=0,j=0;
  while(i+2<SZ(p)||j+2<SZ(q)){
    r.pb(p[i]+q[j]);
    auto cross=(p[i+1]-p[i]).cross(q[j+1]-q[j]);
    i+=cross>=-eps;
    j+=cross<=eps;
  }
  return r;
}

P ccw90(1,0);

int sgn2(double x){return x<0?-1:1;}
struct ln {
  P p,pq;
  ln(P p, P q):p(p),pq(q-p){}
  ln(){}
  bool has(P r){return dist(r)<=eps;}
  bool seghas(P r){return has(r)&&(r-p).dot(r-(p+pq))<=eps;}
//	bool operator /(ln l){return (pq.unit()^l.pq.unit()).norm()<=eps;} // 3D
  bool operator/(ln l){return abs((pq.unit()).cross(l.pq.unit()))<=eps;} // 2D
  bool operator==(ln l){return *this/l&&has(l.p);}
  P operator^(ln l){ // intersection
    if(*this/l)return P(inf,inf);
    P r=l.p+l.pq*((p-l.p).cross(pq)/((l.pq).cross(pq)));
//		if(!has(r)){return P(NAN,NAN,NAN);} // check only for 3D
    return r;
  }
  double angle(ln l){return pq.angle(l.pq);}
  int side(P r){return has(r)?0:sgn2(pq.cross(r-p));} // 2D
  P proj(P r){return p+pq*((r-p).dot(pq)/pq.dist2());}
  P ref(P r){return proj(r)*2-r;}
  double dist(P r){return (r-proj(r)).dist();}
  ln rot(auto a){return ln(p,p+pq.rot(a));} // 2D
};
ln bisector(ln l, ln m){ // angle bisector
  P p=l^m;
  return ln(p,p+l.pq.unit()+m.pq.unit());
}
ln bisector(P p, P q){ // segment bisector (2D)
  return ln((p+q)*.5,p).rot(ccw90);
}

// polygon intersecting left side of halfplanes
struct halfplane:public ln{
  double angle;
  halfplane(){}
  halfplane(P a,P b){p=a; pq=b-a; angle=atan2(pq.y,pq.x);}
  bool operator<(halfplane b)const{return angle<b.angle;}
  bool out(P q){return pq.cross(q-p)<-eps;}
};
vector<P> intersect(vector<halfplane> b){ // O(n*log(n))
  vector<P>bx={P{inf,inf},P{-inf,inf},P{-inf,-inf},P{inf,-inf}};
  fore(i,0,4) b.pb(halfplane(bx[i],bx[(i+1)%4]));
  sort(ALL(b));
  int n=SZ(b),q=1,h=0;
  vector<halfplane> c(SZ(b)+10);
  fore(i,0,n){
    while(q<h&&b[i].out(c[h]^c[h-1])) h--;
    while(q<h&&b[i].out(c[q]^c[q+1])) q++;
    c[++h]=b[i];
    if(q<h&&abs(c[h].pq.cross(c[h-1].pq))<eps){
      if(c[h].pq.dot(c[h-1].pq)<=0) return {};
      h--;
      if(b[i].out(c[h].p)) c[h]=b[i];
    }
  }
  while(q<h-1&&c[q].out(c[h]^c[h-1]))h--;
  while(q<h-1&&c[h].out(c[q]^c[q+1]))q++;
  if(h-q<=1)return {};
  c[h+1]=c[q];
  vector<P> s;
  fore(i,q,h+1) s.pb(c[i]^c[i+1]);
  return s;
}


ld solve(const vector<P>& A, const vector<P>& B) {
  ll N = A.size(), M = B.size();

  ll j = 0;

  vector<pair<P, P>> planes;
  fore(i, 0, N) {
    P p = A[i], q = A[(i+1)%N];

    while (true) {
      P a = B[j%M], b = B[(j+1)%M], c = B[(j+2)%M];
      TY ty = type(p, q, a, b, c);
      if (ty == GOOD) {
        j = (j + M - 1) % M;
      } else {
        break;
      }
    }

    while (true) {
      P a = B[j%M], b = B[(j+1)%M], c = B[(j+2)%M];
      TY ty = type(p, q, a, b, c);

      if (ty == GOOD || ty == JUST) {
        P d = b - B[0];

        planes.push_back({p - d, q - d});
      }
      if (ty == GOOD) {
        break;
      }
      j++;
    }
  }

  vector<halfplane> hps;
  for (auto [p, q] : planes) {
    hps.push_back(halfplane(p, q));
  }

  vector<P> poly = intersect(hps);

  vector<P> poly_ans = minkowski_sum(B, poly);
  ld ans = polygonArea2(poly_ans) / 2.0;

  return ans;
}


signed main(){
  ios::sync_with_stdio(0),cin.tie(0);

  ll N, M;
  cin >> N >> M;
  vector<P> A(N), B(M);
  for (auto& [x, y] : A) {
    ll a, b;
    cin >> a >> b;
    x = a, y = b;
  }
  for (auto& [x, y] : B) {
    ll a, b;
    cin >> a >> b;
    x = a, y = b;
  }

  ld ans = solve(A, B);
  cout << setprecision(8) << fixed;
  cout << ans << '\n';

}