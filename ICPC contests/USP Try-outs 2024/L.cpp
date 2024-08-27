// https://codeforces.com/gym/105297/problem/L

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

struct myCmp {
  bool operator()(const uu& a, const uu& b) const {
    auto [an, ad] = a;
    auto [bn, bd] = b;
    return an * bd < ad * bn;
  }
};

uu slope(ii p0, ii p1) {
  ll dx = abs(p1.first - p0.first);
  ll dy = abs(p1.second - p0.second);
  ll g = gcd(dx, dy);
  return {dy / g, dx / g};
}

vector<optional<uu>> solve(vii& points, const viii& queries) {
  ull Q = queries.size();

  map<ll, ll> x_y_points;
  for (auto [X, Y] : points) {
    x_y_points[X] = Y;
  }

  multiset<uu, myCmp> slopes;
  for (auto it = x_y_points.begin(); it != x_y_points.end(); it++) {
    auto it2 = next(it);
    if (it2 == x_y_points.end()) {
      break;
    }
    slopes.insert(slope(*it, *it2));
  }

  vector<optional<uu>> ans;
  ans.reserve(Q + 1);
  if (slopes.empty()) {
    ans.push_back({});
  } else {
    ans.push_back(*slopes.rbegin());
  }

  for (auto [t, X, Y] : queries) {
    if (t == 1) { // Insert
      assert(!x_y_points.count(X));
      x_y_points[X] = Y;
      auto it = x_y_points.find(X);
      auto it_n = next(it);
      if (it_n != x_y_points.end()) {
        uu s = slope(*it, *it_n);
        slopes.insert(s);
      }
      if (it != x_y_points.begin()) {
        auto it_b = prev(it);
        uu s = slope(*it_b, *it);
        slopes.insert(s);
        if (it_n != x_y_points.end()) {
          s = slope(*it_b, *it_n);
          slopes.erase(slopes.find(s));
        }
      }

    } else { // Delete
      assert(x_y_points.count(X));
      auto it = x_y_points.find(X);
      auto it_n = next(it);
      if (it_n != x_y_points.end()) {
        uu s = slope(*it, *it_n);
        slopes.erase(slopes.find(s));
      }
      if (it != x_y_points.begin()) {
        auto it_b = prev(it);
        uu s = slope(*it_b, *it);
        slopes.erase(slopes.find(s));
        if (it_n != x_y_points.end()) {
          s = slope(*it_b, *it_n);
          slopes.insert(s);
        }
      }
      x_y_points.erase(it);
    }

    if (slopes.empty()) {
      ans.push_back({});
    } else {
      ans.push_back(*slopes.rbegin());
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

#ifndef TEST
  ull N, Q;
  cin >> N >> Q;
  vii points(N);
  for (auto& [X, Y] : points) {
    cin >> X >> Y;
  }
  viii queries(Q);
  for (auto& [T, X, Y] : queries) {
    cin >> T >> X >> Y;
  }

  auto ans = solve(points, queries);

  for (auto AB : ans) {
    if (AB.has_value()) {
      cout << AB->first << ' ' << AB->second << '\n';
    } else {
      cout << "-1\n";
    }
  }
#else
  fore(_, 0, 1000) {
    ull N = rand() % 5;
    ull Q = rand() % 3;
    vii points(N);
    map<ll, ll> XYs;
    fore(i, 0, N) {
      ll X = rand() % 10;
      while (XYs.count(X)) {
        X = rand() % 10;
      }
      ll Y = rand() % 10;
      XYs[X] = Y;
      points[i] = {X, Y};
    }
    viii queries(Q);
    fore(i, 0, Q) {
      ll t = rand() % 2 + 1;
      if (t == 1 || XYs.empty()) {
        ll X = rand() % 10;
        while (XYs.count(X)) {
          X = rand() % 10;
        }
        ll Y = rand() % 10;
        XYs[X] = Y;
        queries[i] = {1, X, Y};
      } else {
        auto it = next(XYs.begin(), rand() % XYs.size());
        ll X = it->first;
        ll Y = it->second;
        XYs.erase(it);
        queries[i] = {t, X, Y};
      }
    }

    cerr << "Case " << _ << ":\n";
    cerr << N << ' ' << Q << '\n';
    for (auto [X, Y] : points) {
      cerr << X << ' ' << Y << '\n';
    }
    for (auto [T, X, Y] : queries) {
      cerr << T << ' ' << X << ' ' << Y << '\n';
    }
    cerr << endl;

    auto ans = solve(points, queries);
  }
#endif
}
