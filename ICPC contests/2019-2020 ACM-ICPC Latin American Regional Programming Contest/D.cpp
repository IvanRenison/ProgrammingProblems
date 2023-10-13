// https://codeforces.com/gym/102428

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef vector<ull> vu;
typedef vector<ll> vi;
typedef pair<ull, ull> uu;
typedef pair<ll, ll> ii;
typedef vector<uu> vuu;
typedef vector<ii> vii;
typedef tuple<ll, ll, ull> iiu;
typedef vector<iiu> viiu;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

#define PI 3.14159265358979323846
constexpr double eps = 1e-9;

struct Interval {
  double a, b;

  Interval(double a = 0, double b = -1) : a(a), b(b) {}

  Interval intersect(Interval o) {
    return Interval(max(a, o.a), min(b, o.b));
  }

  bool empty() {
    return b + eps < a;
  }

  bool point() {
    return abs(a - b) < eps;
  }
};

struct AngleInterval {

  // [0, π), [π, 2π]
  Interval I0, I1;

  AngleInterval(double a = 0, double b = 2*PI) {
    assert(abs(a - b) > eps);
    if (a + eps < b) {
      if (a + eps < PI) {
        if (b + eps < PI) {
          I0 = Interval(a, b);
          I1 = Interval();
        } else {
          I0 = Interval(a, PI);
          I1 = Interval(PI, b);
        }
      } else {
        I0 = Interval();
        I1 = Interval(a, b);
      }
    } else {
      assert(a + eps >= PI);
      assert(b + eps < PI);

      I0 = Interval(0, b);
      I1 = Interval(a, 2*PI);
    }
  }

  AngleInterval intersect(AngleInterval o) {
    AngleInterval ans;

    ans.I0 = I0.intersect(o.I0);
    ans.I1 = I1.intersect(o.I1);

    return ans;
  }


  bool empty() {
    return I0.empty() && I1.empty();
  }
};


AngleInterval get(iiu a, iiu b) {
  auto [X0, Y0, B0] = a;
  auto [X1, Y1, B1] = b;

  if (B0 == B1) {
    return AngleInterval();
  }

  if (B0 > B1) {
    swap(X0, X1), swap(Y0, Y1), swap(B0, B1);
  }

  double dX = X1 - X0, dY = Y1 - Y0;

  double beta = atan2(dY, dX);
  if (beta + eps < 0) {
    beta += 2*PI;
  }

  double i0 = beta + PI/2.0;
  double i1 = beta - PI/2.0;

  if (i0 + eps >= 2*PI) {
    i0 -= 2*PI;
  }
  if (i1 + eps < 0) {
    i1 += 2*PI;
  }

  return AngleInterval(i0, i1);
}

bool solve(viiu XYBs) {
  ull N = XYBs.size();

  AngleInterval ans;

  fore(i, 0, N) {
    fore(j, i+1, N) {
      ans = ans.intersect(get(XYBs[i], XYBs[j]));
    }
  }

  return !ans.empty();
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N;
  cin >> N;
  viiu XYBs(N);
  for(auto& [X, Y, B] : XYBs) {
    cin >> X >> Y >> B;
  }

  if (solve(XYBs)) {
    cout << "Y\n";
  } else {
    cout << "N\n";
  }

  return EXIT_SUCCESS;
}

