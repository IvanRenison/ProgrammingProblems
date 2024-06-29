// https://codeforces.com/group/gmV7IkT2pN/contest/520377/problem/G

#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
typedef long long ll;
typedef vector<ll> vi;

template <typename T>
using rpriority_queue = priority_queue<T, vector<T>, greater<T>>;

uint solve(const vi& as) {
  uint ans = 0;
  ll sum = 0;
  rpriority_queue<ll> pq;

  for (ll a : as) {
    sum += a;
    ans++;
    pq.push(a);
    while (sum < 0) {
      sum -= pq.top();
      pq.pop();
      ans--;
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  uint n;
  cin >> n;
  vi as(n);
  for (ll& a : as) {
    cin >> a;
  }

  uint ans = solve(as);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}

