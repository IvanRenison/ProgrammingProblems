// https://codeforces.com/gym/103640/problem/J

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

ull pairs[100000][4];

ull points[2][100000][2];

static inline bool intersect(pair<ull, ull> P1, pair<ull, ull> P2) {
  ull P1_1 = P1.first, P1_2 = P1.second;
  ull P2_1 = P2.first, P2_2 = P2.second;

  return (
      P1_1 < P2_1 && P2_1 < P1_2
        ? P2_2 < P1_1 || P1_2 < P2_2
    : P1_1 < P2_2 && P2_2 < P1_2
        ? P2_1 < P1_1 || P1_1 < P2_2
        : false
  );
}

static inline bool solve_only_borders(ull start, ull end, ull iteration) {
  ull n = end - start;

  if (n == 0) {
    return true;
  }

  ull points_array = iteration % 2;
  ull points_array_next = 1 - iteration % 2;

  ull i = rand() % n + start;

  ull P1_0 = points[points_array][i][0];
  ull P1_1 = points[points_array][i][1];

  ull updated_start = start;
  ull updated_end = end;


  fore (j, start, end) {
    if (j != i) {

      ull P_0 = points[points_array][j][0];
      ull P_1 = points[points_array][j][1];

      if (intersect({P1_0, P1_1}, {P_0, P_1})) {
        return false;
      }

      if (P1_0 < P_0 && P_0 < P1_1) {
        points[points_array_next][updated_start][0] = P_0;
        points[points_array_next][updated_start][1] = P_1;
        updated_start++;
      }
      else {
        points[points_array_next][updated_end-1][0] = P_0;
        points[points_array_next][updated_end-1][1] = P_1;
        updated_end--;
      }
    }
  }

  iteration++;

  return solve_only_borders(start, updated_start, iteration) && solve_only_borders(updated_end, end, iteration);
}

static inline bool solve(ull W, ull H, ull N) {
  #define in_border(X, Y) (X == 0 || X == W || Y == 0 || Y == H)
  #define convert_to_border(X, Y) (\
      Y == 0 ? X                   \
    : X == W ? W + Y               \
    : Y == H ? W + H + (W - X)     \
             : W + H + W + (H - Y) )

  ull end_border_points = 0;

  fore (i, 0, N) {
    ull X1 = pairs[i][0], Y1 = pairs[i][1], X2 = pairs[i][2], Y2 = pairs[i][3];

    if (in_border(X1, Y1) && in_border(X2, Y2)) {
      ull border_0 = convert_to_border(X1, Y1);
      ull border_1 = convert_to_border(X2, Y2);
      points[0][end_border_points][0] = min(border_0, border_1);
      points[0][end_border_points][1] = max(border_0, border_1);

      end_border_points++;
    }

  }

  return solve_only_borders(0, end_border_points, 0);
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
