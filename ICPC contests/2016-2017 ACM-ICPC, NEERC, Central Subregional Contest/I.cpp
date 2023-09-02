// https://codeforces.com/gym/101243
#include <bits/stdc++.h>
#define fore(i, a, b) for (int i = a, thxMat = b; i < thxMat; ++i)
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
typedef unsigned long long ull;

typedef pair<double, double> P;

P operator-(P p1, P p2) {
  auto [x1, y1] = p1;
  auto [x2, y2] = p2;
  return {x1 - x2, y1 - y2};
}

P operator*(P p, double e) {
  auto [x, y] = p;
  return {x * e, y * e};
}

double dot(P p1, P p2) {
  auto [x1, y1] = p1;
  auto [x2, y2] = p2;

  return x1 * x2 + y1 * y2;
}

double norm2(P p) {
  return dot(p, p);
}

double norm(P p) {
  return sqrt(norm2(p));
}

double dist(P p1, P p2) {
  return norm(p1 - p2);
}

double segDist(P s, P e, P p) {
  if (s == e) {
    return dist(s, p);
  }
  double d = norm2(e - s);
  double t = min(d, max(0.0, dot(p - s, e - s)));
  return norm((p - s) * d - (e - s) * t) / d;
}

double solveCornerCorner(ull M, ull K, const vector<P>& XYs) {
  ull N = XYs.size();

  double ans = 1e100;

  fore(i, 0, N) {
    double this_ans = dist(XYs[i], XYs[(i + M - 1) % N]);
    ans = min(ans, this_ans);
  }

  return ans;
}

double solveCornerSide(ull M, ull K, const vector<P>& XYs) {
  ull N = XYs.size();

  double ans = 1e100;

  fore(i, 0, N) {
    double this_ans =
        segDist(XYs[(i + M - 2) % N], XYs[(i + M - 1) % N], XYs[i]);
    ans = min(ans, this_ans);
  }

  return ans;
}

double solveSideSide(ull M, ull K, const vector<P>& XYs) {
  ull N = XYs.size();

  double ans = 1e100;

  fore(i, 0, N) {
    double this_ans =
        segDist(XYs[(i + M - 3) % N], XYs[(i + M - 2) % N], XYs[i]);
    this_ans =
        min(this_ans,
            segDist(
                XYs[(i + M - 3) % N], XYs[(i + M - 2) % N], XYs[(i + N - 1) % N]
            ));
    this_ans =
        min(this_ans,
            segDist(XYs[(i + N - 1) % N], XYs[i], XYs[(i + M - 3) % N]));
    this_ans =
        min(this_ans,
            segDist(XYs[(i + N - 1) % N], XYs[i], XYs[(i + M - 2) % N]));
    ans = min(ans, this_ans);
  }

  return ans;
}

optional<double> solve(ull M, ull K, const vector<P>& XYs) {
  ull N = XYs.size();

  double ans;
  if (M + K == N + 2) {
    // Esquina con esquina
    ans = solveCornerCorner(M, K, XYs);
  } else if (M + K == N + 3) {
    // Esquina con lado
    ans = min(solveCornerSide(M, K, XYs), solveCornerSide(K, M, XYs));
  } else if (M + K == N + 4) {
    // Lado con lado
    ans = solveSideSide(M, K, XYs);
  } else {
    return {};
  }

  return ans;
}

int main() {
  FIN;
#ifdef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  cout << setprecision(3) << fixed;

  ull N, M, K;
  cin >> N >> M >> K;
  vector<P> XYs(N);
  for (auto& [X, Y] : XYs) {
    cin >> X >> Y;
  }

  auto ans = solve(M, K, XYs);
  if (!ans.has_value()) {
    cout << "-1\n";
  } else {
    cout << *ans << '\n';
  }

  return 0;
}
