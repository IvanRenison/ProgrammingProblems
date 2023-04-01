//

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
#define fore(i, a, b) for (ull i = a; i < b; i++)

pair<vector<ull>, vector<pair<ull, ull>>> parse1(void) {
  ull n, m;
  cin >> n >> m;
  vector<ull> a(n);
  vector<pair<ull, ull>> b(m);
  fore(i, 0, n) {
    cin >> a[i];
  }
  fore(i, 0, m) {
    ull v, w;
    cin >> v >> w;
    b[i] = {v - 1, w - 1};
  }
  return {a, b};
}

bool solve1(vector<ull> weights, vector<pair<ull, ull>> edges) {
  ull n = weights.size();
  ull m = edges.size();

  vector<vector<ull>> neighbors(n);

  for (auto [v, w] : edges) {
    neighbors[v].push_back(w);
    neighbors[w].push_back(v);
  }

  vector<bool> ceros_visited(n, false);


  fore(i, 0, n) {
    if (weights[i] == 0 && !ceros_visited[i]) {
      queue<ull> queue;
      vector<bool> visited(n, false);
      visited[i] = true;
      ull visited_amount = 1;
      ull killed_amount = 0;
      queue.push(i);

      bool flag = true;
      while (queue.size() > 0 && flag) {
        ull first_try = queue.front();
        ull v = first_try;
        queue.pop();
        while (weights[v] > killed_amount) {
          queue.push(v);
          v = queue.front();
          queue.pop();
          if (v == first_try) {
            flag = false;
            break;
          }
        }
        if (flag) {
          killed_amount++;
          for (ull w : neighbors[v]) {
            if (!visited[w]) {
              queue.push(w);
              visited_amount++;
              visited[w] = true;
              if (weights[w] == 0) {
                ceros_visited[w] = true;
              }
            }
          }
        }
      }

      if (visited_amount == n) {
        return true;
      }
    }
  }

  return false;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull t;

  cin >> t;

  fore(i, 0, t) {
    auto [a, b] = parse1();
    if (solve1(a, b)) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }
  }

  return EXIT_SUCCESS;
}
