#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()

const ull inf = 1ull << 60;

vu solveBigg(ull K, const vu& Vs) {
  vu ans;
  set<ull> anss;

  set<ull> seen;

  for (ull V : Vs) {
    if (anss.count(V) == 0) {
      seen.insert(V);
      if (seen.size() == K - ans.size()) {
        ans.push_back(V);
        anss.insert(V);
        seen = {};
      }
    }
  }

  fore(i, 0, K) {
    if (anss.count(i) == 0) {
      ans.push_back(i);
    }
  }

  return ans;
}

vu solveSmall(ull K, const vu& Vs) {
  ull N = Vs.size();

  vector<vu> poss(K);
  fore(i, 0, N) {
    poss[Vs[i]].push_back(i);
  }

  vuu dp(1 << K, {0, inf});

  fore(x, 1, 1 << K) {
    fore(v, 0, K) {
      if (x & (1 << v)) {
        ull this_ans = dp[x ^ (1 << v)].first;
        auto it = lower_bound(all(poss[v]), this_ans);
        if (it != poss[v].end()) {
          ull j = *it;
          if (j >= dp[x].first) {
            dp[x] = {j, v};
          }
        } else {
          vu ans;
          ull anss = 0;
          ull y = x ^ (1 << v);
          while (y != 0) {
            assert((anss & (1 << dp[y].second)) == 0);
            ans.push_back(dp[y].second);
            anss ^= 1 << dp[y].second;
            y ^= 1 << dp[y].second;
          }
          reverse(all(ans));
          ans.push_back(v);
          anss ^= 1 << v;
          fore(i, 0, K) {
            if ((anss & (1 << i)) == 0) {
              ans.push_back(i);
              // anss ^= 1 << i;
            }
          }
          return ans;
        }
      }
    }
  }

  return {};
}

vu solve(ull K, const vu& Vs) {
  ull N = Vs.size();
  if (K * (K + 1) / 2 > N) {
    return solveBigg(K, Vs);
  } else {
    return solveSmall(K, Vs);
  }
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N, K;
  cin >> N >> K;

  vu Vs(N);
  for (ull& V : Vs) {
    cin >> V;
    V--;
  }

  auto ans = solve(K, Vs);
  if (ans.size() == 0) {
    cout << '*';
  } else {
    for (ull a : ans) {
      cout << a + 1 << ' ';
    }
  }
  cout << '\n';

  return EXIT_SUCCESS;
}
