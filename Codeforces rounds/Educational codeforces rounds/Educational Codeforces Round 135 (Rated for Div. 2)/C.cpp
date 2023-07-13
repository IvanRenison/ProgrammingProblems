//

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;

static inline pair<vector<uint>, vector<uint>> parse(void) {
  uint n;
  cin >> n;

  vector<uint> as(n);
  for (uint i = 0; i < n; i++) {
    cin >> as[i];
  }

  vector<uint> bs(n);
  for (uint i = 0; i < n; i++) {
    cin >> bs[i];
  }

  return {as, bs};
}

static inline uint solve(vector<uint> as, vector<uint> bs) {

  uint n = as.size();

  // Insert as in to a priority_queue
  priority_queue<uint> aq;
  for (uint i = 0; i < n; i++) {
    aq.push(as[i]);
  }

  // Insert bs in to a priority_queue
  priority_queue<uint> bq;
  for (uint i = 0; i < n; i++) {
    bq.push(bs[i]);
  }

  uint res = 0;

  while (!aq.empty()) {
    uint a = aq.top();
    uint b = bq.top();

    if (a == b) {
      aq.pop();
      bq.pop();
    } else if (a > b) {
      res += 1;

      aq.pop();
      uint new_a = to_string(a).size();
      aq.push(new_a);
    } else {
      res += 1;

      bq.pop();
      uint new_b = to_string(b).size();
      bq.push(new_b);
    }
  }

  return res;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  uint t;

  cin >> t;

  for (uint i = 0; i < t; i++) {
    auto [as, bs] = parse();
    cout << solve(as, bs) << endl;
  }

  return EXIT_SUCCESS;
}
