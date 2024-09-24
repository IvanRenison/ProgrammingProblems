// https://codeforces.com/gym/101190
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define mset(a,v) memset((a),(v),sizeof(a))
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;
typedef long double ld;
const ld eps = 1e-13;

typedef bitset<10000> B;

optional<ll> solve1(ll h, const vii& lks) {
  ll m = lks.size();
  fore(q, 0, m) {
    auto [l, k] = lks[q];
    if (k != h - 1 - q) {
      return q;
    }
  }
  return {};
}

optional<ll> solve(ll n, ll h, const vii& lks) {
  if (n == 1) return solve1(h, lks);
  ll m = lks.size();

  vi sums(h);
  vi counter(h);
  vi total_counter(h);
  for (ll count = 0, sum = 0, j = h - 1; j >= 0; j -= 2) {
    counter[j] += count;
    sums[j] = sum;
    count += n;
    sum += n*n;
  }
  for (ll count = 0, sum = 0, j = h - 2; j >= 0; j -= 2) {
    counter[j] += count;
    sums[j] = sum;
    count += n;
    sum += n*n;
  }
  for (ll count = 0, j = h - 1; j >= 0; j--) {
    total_counter[j] = count;
    count += n;
  }

  B B_neut;
  fore(i, 0, n) {
    B_neut[i] = 1;
  }
  vector<B> ons(h, B_neut);
  vi first_on(h);
  vi last_on(h, n - 1);

  fore(q, 0, m) {
    auto [l, k] = lks[q];

    ons[l][k] = false;
    first_on[l] = last_on[l] = -1;
    fore(i, 0, n) {
      if (ons[l][i]) {
        first_on[l] = i;
        break;
      }
    }
    if (l < h - 1 && first_on[l] == -1) {
      return q;
    } else if (first_on[l] == -1) {
      h--;
    }
    for (ll i = n; i--;) {
      if (ons[l][i]) {
        last_on[l] = i;
        break;
      }
    }
    if (l + 1 < h) {
      if (counter[l] == 0) {
        if (total_counter[l] != 0) {
          if (first_on[l] * 2 >= n || (last_on[l] + 1) * 2 <= n) {
            return q;
          }
        }
      } else {
        ld c = (ld)sums[l] / 2.0 / (ld)counter[l];
        ll perp_count = l == 0 ? ons[1].count() + counter[l + 1] : counter[l-1];
        c = (c * (ld)counter[l] + (ld)n/2.0 * (ld)perp_count) / ((ld)(counter[l] + perp_count));
        if (c - eps <= (ld)first_on[l] || c + eps >= (ld)(last_on[l] + 1)) {
          return q;
        }
      }
    }
    for (ll j = l % 2; j < l; j += 2) {
      sums[j] -= 2 * k + 1;
      counter[j]--;
    }
    fore(j, 0, l) {
      total_counter[j]--;
    }
    for (ll j = l % 2; j < l; j += 2) {
      if (counter[j] == 0) {
        if (total_counter[j] != 0) {
          if (first_on[j] * 2 >= n || (last_on[j] + 1) * 2 <= n) {
            return q;
          }
        }
      } else {
        ld c = (ld)sums[j] / 2.0 / (ld)counter[j];
        ll perp_count = j == 0 ? ons[1].count() + counter[j + 1] : counter[j-1];
        c = (c * (ld)counter[j] + (ld)n/2.0 * (ld)perp_count) / ((ld)(counter[j] + perp_count));
        if (c - eps <= (ld)first_on[j] || c + eps >= (ld)(last_on[j] + 1)) {
          return q;
        }
      }
    }

  }

  return {};
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);
#ifdef ONLINE_JUDGE
  freopen("jenga.in", "r", stdin);
  freopen("jenga.out", "w", stdout);
#endif

  ll n, w, h, m;
  cin >> n >> w >> h >> m;
  vii lks(m);
  for (auto& [l, k] : lks) {
    cin >> l >> k;
    l--, k--;
  }

  auto ans = solve(n, h, lks);
  if (ans.has_value()) {
    cout << "yes\n" << *ans + 1 << '\n';
  } else {
    cout << "no\n";
  }
}
