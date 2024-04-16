// https://codeforces.com/gym/102916/problem/I

#ifndef ONLINE_JUDGE
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
//#define _GLIBCXX_DEBUG_BACKTRACE 1
#define _GLIBCXX_CONCEPT_CHECKS 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

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
typedef tuple<ull, ull, ull, ull, ull> uuuuu;
typedef vector<uuuuu> vuuuuu;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;
typedef tuple<ll, ll, ll, ll> iiii;
typedef vector<iiii> viiii;
typedef tuple<ll, ll, ll, ll, ll> iiiii;
typedef vector<iiiii> viiiii;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define ALL(x) x.begin(), x.end()
#define DBG(x) cerr << #x << " = " << x << endl

const ull inf = 1ull << 60;

void force(ull n, ull k) {
  vuu games;
  fore(i, 0, n - 1) {
    games.push_back({i, i + 1});
    i++;
  }
  fore(i, 0, n - 2) {
    games.push_back({i + 1, i + 2});
    i++;
  }
  fore(i, 0, n) {
    fore(j, i + 2, n) {
      games.push_back({i, j});
    }
  }

  auto time = [k](const vuu& ord) -> ull {
    ull ans = 1;
    set<ull> in;
    for (auto [i, j] : ord) {
      if (in.size() >= 2*k || in.count(i) || in.count(j)) {
        ans++;
        in = {i, j};
      } else {
        in.insert(i), in.insert(j);
      }
    }
    return ans;
  };

  ull real_ans = (n * (n - 1) / 2 + k - 1) / k;

  ull ans_v = time(games);
  vuu ans_ord = games;

  while (ans_v > real_ans && next_permutation(ALL(games))) {
    ull cur_v = time(games);
    if (cur_v < ans_v) {
      ans_v = cur_v;
      ans_ord = games;
    }
  }

  cerr << "ord:\n";
  for (auto [i, j] : ans_ord) {
    cerr << i << ' ' << j << '\n';
  }
  cerr << "ans: " << ans_v << '\n';
}

vector<vuu> solve(ull n, ull k) {

  vuu pairs;

  deque vals = {0};
  fore(i, 1, n) {
    vals.push_back(i);
  }

  if (n % 2 == 1) {
    fore(i, 0, n) {
      fore(j, 0, n / 2) {
        pairs.push_back({vals[j], vals[n - 1 - j]});
      }

      ull f = vals.front();
      vals.pop_front();
      vals.push_back(f);
    }
  } else {
    vals.pop_front();
    fore(i, 0, (n - 1)) {
      pairs.push_back({0, vals[0]});
      fore(j, 0, n / 2 - 1) {
        pairs.push_back({vals[j + 1], vals[n - 2 - j]});
      }

      ull f = vals.front();
      vals.pop_front();
      vals.push_back(f);
    }
  }

  //cerr << pairs.size() << '\n';
  assert(pairs.size() == n * (n - 1) / 2);

  vector<vuu> ans;

  fore(i, 0, pairs.size()) {
    if (i % k == 0) {
      ans.push_back({});
    }
    ans.back().push_back(pairs[i]);
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ull n, k;
  cin >> n >> k;

  auto ans = solve(n, k);
  cout << ans.size() << '\n';
  for (vuu vals : ans) {
    cout << vals.size() << '\n';
    for (auto [i, j] : vals) {
      cout << i + 1 << ' ' << j + 1 << '\n';
    }
  }

  /* ull n, k;
  cin >> n >> k;
  force(n, k); */

  return EXIT_SUCCESS;
}
/*

*/