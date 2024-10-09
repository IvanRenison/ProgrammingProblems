// https://codeforces.com/gym/101630
#include <bits/stdc++.h>
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define SZ(x)  (ll(x.size()))
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;
typedef array<ll, 3> iii;
typedef vector<iii> viii;

optional<viii> solveOrd(ll a, ll b, ll c) {
  assert(a <= b && b <= c);
  if (a * b < c) {
    return {};
  }

  if (a + b - 1 <= c) {
    viii ans;
    fore(y, 0, a) {
      ans.push_back({0, y, 0});
    }
    fore(z, 1, b) {
      ans.push_back({0, 0, z});
    }

    ll count_c = a + b - 1;
    fore(y, 1, a) {
      fore(z, 1, b) {
        if (count_c == c) {
          goto end;
        }
        ans.push_back({0, y, z});
        count_c++;
      }
    }
    end:;
    return ans;
  }

  viii ans;

  ll d = a + b - 1 - c;
  fore(y, 0, a - d) {
    ans.push_back({0, y, 0});
  }
  fore(z, 1, d) {
    ans.push_back({0, a - 1 - d + z, z});
  }
  fore(z, d, b) {
    ans.push_back({0, a - 1, z});
  }

  return ans;
}

optional<viii> solve(ll a, ll b, ll c) {

  array<ii, 3> arr;
  arr[0] = {a, 0}, arr[1] = {b, 1}, arr[2] = {c, 2};
  sort(ALL(arr));

  optional<viii> ans = solveOrd(arr[0].first, arr[1].first, arr[2].first);
  if (!ans) {
    return {};
  }

  ll i = arr[0].second, j = arr[1].second, k = arr[2].second;

  for (auto& xyz : *ans) {
    auto [x, y, z] = xyz;

    if (i == 0 && j == 1 && k == 2) {
      break;
    } else if (i == 0 && j == 2 && k == 1) {
      xyz = {y, x, z};
    } else if (i == 1 && j == 0 && k == 2) {
      xyz = {x, z, y};
    } else if (i == 1 && j == 2 && k == 0) {
      xyz = {y, z, x};
    } else if (i == 2 && j == 0 && k == 1) {
      xyz = {z, x, y};
    } else { // i == 2 && j == 1 && k == 0
      xyz = {z, y, x};
    }

  }

  return ans;
}

bool check(ll a, ll b, ll c, viii ans) {
  set<ii> xy, xz, yz;

  for (auto [x, y, z] : ans) {
    xy.insert({x, y});
    xz.insert({x, z});
    yz.insert({y, z});
  }

  return xy.size() == a && xz.size() == b && yz.size() == c;
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);

#ifndef TEST
  ll a, b, c;
  cin >> a >> b >> c;
  auto ans = solve(a, b, c);
  if (ans) {
    cout << ans->size() << '\n';
    for (auto [x, y, z] : *ans) {
      cout << x << ' ' << y << ' ' << z << '\n';
    }
    //cout << endl;
    //assert(check(a, b, c, *ans));
  } else {
    cout << "-1\n";
  }
#else
  fore(_, 0, 1000) {
    ll a = rand() % 5 + 1, b = rand() % 5 + 1, c = rand() % 5 + 1;
    optional<viii> ans = solve(a, b, c);
    if (ans) {
      if (!check(a, b, c, *ans)) {
        cerr << a << ' ' << b << ' ' << c << '\n';
        cerr << ans->size() << '\n';
        for (auto [x, y, z] : *ans) {
          cerr << x << ' ' << y << ' ' << z << '\n';
        }
        cerr << endl;
        return 1;
      }
    }
  }
#endif
}
