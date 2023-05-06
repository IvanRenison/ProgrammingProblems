// https://codeforces.com/contest/1829/problem/E

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

ull lake[1000][1000];

pair<ull, ull> parse1(void) {
  ull n, m;
  cin >> n >> m;

  fore(i, 0, n) {
    fore(j, 0, m) {
      cin >> lake[i][j];
    }
  }

  return {n, m};
}

bool visited[1000][1000];

ull volume_from(ull i, ull j, ull n, ull m) {
  ull volume = 0;
  if (i >= n || j >= m || visited[i][j] || lake[i][j] == 0) {
    return volume;
  }

  visited[i][j] = true;

  vector<pair<ull, ull>> q = {{i, j}};

  while (q.size() > 0) {
    auto [i, j] = q.back();
    q.pop_back();

    volume += lake[i][j];

    if (i > 0 && !visited[i - 1][j] && lake[i - 1][j] > 0) {
      visited[i - 1][j] = true;
      q.push_back({i - 1, j});
    }
    if (i < n - 1 && !visited[i + 1][j] && lake[i + 1][j] > 0) {
      visited[i + 1][j] = true;
      q.push_back({i + 1, j});
    }
    if (j > 0 && !visited[i][j - 1] && lake[i][j - 1] > 0) {
      visited[i][j - 1] = true;
      q.push_back({i, j - 1});
    }
    if (j < m - 1 && !visited[i][j + 1] && lake[i][j + 1] > 0) {
      visited[i][j + 1] = true;
      q.push_back({i, j + 1});
    }
  }

  return volume;
}

ull solve1(ull n, ull m) {
  // Clean visited
  fore(i, 0, n) {
    fore(j, 0, m) {
      visited[i][j] = false;
    }
  }

  ull max_volume = 0;
  fore(i, 0, n) {
    fore(j, 0, m) {
      if (visited[i][j]) {
        continue;
      }
      if (lake[i][j] == 0) {
        visited[i][j] = true;
        continue;
      }

      ull volume = volume_from(i, j, n, m);
      max_volume = max(max_volume, volume);
    }
  }

  return max_volume;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    auto [n, m] = parse1();
    cout << solve1(n, m) << "\n";
  }

  return EXIT_SUCCESS;
}
