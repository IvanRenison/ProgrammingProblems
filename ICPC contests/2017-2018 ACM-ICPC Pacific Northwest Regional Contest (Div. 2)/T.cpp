// https://codeforces.com/gym/101652

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef tuple<ull, ull, ull> uuu;
typedef vector<uuu> vuuu;
typedef tuple<ull, ull, ull, ull> uuuu;
typedef vector<uuuu> vuuuu;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()
#define DBG(x) cerr << #x << " = " << x << endl

ull solve(ull n, ull k, ull s, ull t, vuuuu abcds) {
  set<ull> ids;
  vector<vuuu> adj(n);
  for(auto& [a, b, c, d] : abcds) {
    ids.insert(c), ids.insert(d);
    adj[a].push_back({b, c, d});
  }

  set<ull> valid_ids;

  for(ull id : ids) {
    vu stack = {s};
    vector<bool> vis(n, false);
    vis[s] = true;

    while (!stack.empty()) {
      ull u = stack.back();
      stack.pop_back();

      for(auto& [v, c, d] : adj[u]) {
        if (!vis[v] && c <= id && id < d) {
          vis[v] = true;
          stack.push_back(v);
        }
      }
    }

    if (vis[t]) {
      valid_ids.insert(id);
    }
  }

  ull ans = 0;
  for(auto it = ids.begin(); it != ids.end(); it++) {
    auto it_next = next(it);

    if (it_next != ids.end()) {
      ull id = *it;
      ull id_next = *it_next;

      if (valid_ids.count(id)) {
        ans += id_next - id;
      }
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n, m, k, s, t;
  cin >> n >> m >> k >> s >> t;
  s--, t--;
  vuuuu abcds(m);
  for(auto& [a, b, c, d] : abcds) {
    cin >> a >> b >> c >> d;
    a--, b--, c--;
  }

  auto ans = solve(n, k, s, t, abcds);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
