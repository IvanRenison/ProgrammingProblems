// https://codeforces.com/contest/1903/E

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;


#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()
#define DBG(x) cerr << #x << " = " << x << endl

void solve1(ll sx, ll sy, const vii& xys) {
  ull n = xys.size();

  vector<unordered_set<ull>> counts(2);
  fore(i, 0, n) {
    auto [x, y] = xys[i];
    counts[(abs(sx - x) % 2) ^ (abs(sy - y) % 2)].insert(i);
  }

  //DBG(counts[0].size());
  //DBG(counts[1].size());
  /* ull sum = 0;
  bool even = true;
  ll lastx = sx, lasty = sy; */

  if (counts[0].size() >= counts[1].size() && counts[1].size() > 0) {
    cout << "First" << endl;
    auto it = counts[1].begin();
    cout << *it + 1 << endl;
    /* auto [x, y] = xys[*it];
    sum += abs(lastx - x) + abs(lasty - y);
    lastx = x, lasty = y; */
    counts[1].erase(it);
  } else if (counts[1].size() == 0) {
    cout << "First" << endl;
    auto it = counts[0].begin();
    cout << *it + 1 << endl;
    /* auto [x, y] = xys[*it];
    sum += abs(lastx - x) + abs(lasty - y);
    lastx = x, lasty = y; */
    counts[0].erase(it);
  } else {
    //even = false;
    cout << "Second" << endl;
  }

  while (counts[0].size() + counts[1].size() > 0) {
    ll j;
    cin >> j;
    /* if (j == -1) {
      exit(EXIT_FAILURE);
    } */

    j--;
    auto [x, y] = xys[j];
    /* sum += abs(lastx - x) + abs(lasty - y);
    lastx = x, lasty = y; */

    ull st = (abs(sx - x) % 2) ^ (abs(sy - y) % 2);
    counts[st].erase(j);

    if (counts[0].size() + counts[1].size() == 0) {
      break;
    }

    if ((counts[st].size() > 0 && counts[st].size() > 1 + counts[1 - st].size()) || counts[1 - st].size() == 0) {
      auto it = counts[st].begin();
      cout << *it + 1 << endl;
      /* auto [x, y] = xys[*it];
      sum += abs(lastx - x) + abs(lasty - y);
      lastx = x, lasty = y; */
      counts[st].erase(it);
    } else {
      auto it = counts[1 - st].begin();
      cout << *it + 1 << endl;
      /* auto [x, y] = xys[*it];
      sum += abs(lastx - x) + abs(lasty - y);
      lastx = x, lasty = y; */
      counts[1 - st].erase(it);
    }
  }

  /* if (even) {
    assert(sum % 2 == 0);
  } else {
    assert(sum % 2 != 0);
  } */
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull t;
  cin >> t;

  fore(i, 0, t) {
    ll n;
    cin >> n;
    /* if (n == -1) {
      return EXIT_FAILURE;
    } */

    ll sx, sy;
    cin >> sx >> sy;
    vii xys(n);
    for (auto& [x, y] : xys) {
      cin >> x >> y;
    }

    solve1(sx, sy, xys);
  }

  return EXIT_SUCCESS;
}
