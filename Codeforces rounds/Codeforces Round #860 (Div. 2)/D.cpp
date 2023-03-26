// https://codeforces.com/contest/1798/problem/D

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define fore(i, a, b) for (ll i = a; i < b; i++)

vector<ll> parse1(void) {
  ll n;
  cin >> n;
  vector<ll> as(n);
  fore(i, 0, n) {
    cin >> as[i];
  }
  return as;
}

optional<vector<ll>> solve1(vector<ll> as) {
  ll n = as.size();

  sort(as.begin(), as.end());

  ll front = 0;
  ll back = n - 1;

  if (as[front] == as[back]) {
    return nullopt;
  }

  vector<ll> ans(n);
  ll sum = 0;
  fore(i, 0, n) {
    if (sum >= 0) {
      ans[i] = as[front];
      sum += as[front];
      front++;
    }
    else {
      ans[i] = as[back];
      sum += as[back];
      back--;
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ll t;

  cin >> t;

  fore(i, 0, t) {
    optional<vector<ll>> ans = solve1(parse1());
    if (!ans) {
      cout << "No" << endl;
      continue;
    }
    cout << "Yes" << endl;
    for(ll a : *ans) {
      cout << a << " ";
    }
    cout << endl;
  }

  return EXIT_SUCCESS;
}
