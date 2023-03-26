// https://codeforces.com/gym/103640/problem/J

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

ull pairs[100000][4];


static inline bool solve(ull W, ull H, ull N) {
  #define in_border(X, Y) (X == 0 || X == W || Y == 0 || Y == H)
  #define convert_to_border(X, Y) (\
      Y == 0 ? X                   \
    : X == W ? W + Y               \
    : Y == H ? W + H + (W - X)     \
             : W + H + W + (H - Y) )

  map<ull, ull> border_points;

  fore (i, 0, N) {
    ull X1 = pairs[i][0], Y1 = pairs[i][1], X2 = pairs[i][2], Y2 = pairs[i][3];

    if (in_border(X1, Y1) && in_border(X2, Y2)) {
      ull border_0 = convert_to_border(X1, Y1);
      ull border_1 = convert_to_border(X2, Y2);
      border_points[border_0] = i;
      border_points[border_1] = i;
    }

  }

  set<ull> colors_passed;
  vector<ull> colors_passed_vec;

  for (std::pair<const ull, ull> point : border_points) {
    ull color = point.second;

    if (colors_passed.find(color) == colors_passed.end()) {
      colors_passed.insert(color);
      colors_passed_vec.push_back(color);
    }
    else if (colors_passed_vec[colors_passed_vec.size() - 1] == color) {
      colors_passed_vec.pop_back();
      colors_passed.erase(color);
    }
    else {
      return false;
    }

  }

  return true;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull W, H, N;

  cin >> W >> H;
  cin >> N;

  for (ull i = 0; i < N; i++) {
    cin >> pairs[i][0] >> pairs[i][1] >> pairs[i][2] >> pairs[i][3];
  }

  cout << (solve(W, H, N) ? "Y" : "N") << endl;


  return EXIT_SUCCESS;
}
