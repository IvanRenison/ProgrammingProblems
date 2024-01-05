#include <bits/stdtr1c++.h>
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(int i=a,gmat=b;i<gmat;i++)
#define FIN ios::sync_with_stdio(0);cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;

/* void force() {

  map<ll, ll> vals;

  for (ll x = 12; x < 1e11; x += 3) {
    if (x % ((ll)3e6) == 0) {
      cerr << "Reached: " << (x/((ll)1e6)) << "e6" << endl;
    }



    vi ds;
    for (ll y = x; y > 0; y /= 10) {
      ds.push_back(y % 10);
    }

    ll ds_size = ds.size();

    // Check that the digits are non decreasing (except maybe for 0's) an not all equal
    bool non_decreasing = true, non_equal = false;
    fore(i, 1, ds_size - 1) {
      if (ds[i] > ds[i - 1]) {
        non_decreasing = false;
        break;
      }
      if (ds[i] < ds[i - 1]) {
        non_equal = true;
      }
    }
    if (ds[ds_size - 2] != 0) {
      if (ds[ds_size - 1] > ds[ds_size - 2]) {
        non_decreasing = false;
      }
      if (ds[ds_size - 1] < ds[ds_size - 2]) {
        non_equal = true;
      }
    } else {
      if (ds_size > 2 && ds[ds_size - 1] > ds[ds_size - 3]) {
        non_decreasing = false;
      }
      non_equal = true;
    }
    if (!non_decreasing || !non_equal) {
      continue;
    }

    reverse(ALL(ds));

    ll g = x;

    do {
      ll y = 0;
      ll p = 1;
      for (ll d : ds) {
        y += d * p;
        p *= 10;
      }

      g = gcd(g, y);

      if (g < 12) {
        break;
      }

    } while (next_permutation(ALL(ds)));

    if (g >= 12) {
      if (vals.count(g) == 0) {
        vals[g] = x;
        cout << "{" << g << ", " << x << " }," << endl;
      }
    }

  }

} */

const map<ll, ll> vals = {
  {12, 48 },
  {18, 288 },
  {27, 3699 },
  {15, 5055 },
  {21, 7077 },
  {24, 8088 },
  {36, 48888 },
  {63, 111888 },
  {54, 222888888 },
  {45, 5055555555 },
  {72, 8088888888 },
  {81, 9099999999 }
};

ll solve(ll n) {

  if (vals.count(n) != 0) {
    return vals.at(n);
  }


  ll x = n;
  ll d = x % 10;
  while (x > 0) {
    if (x % 10 != d) {
      return -1;
    }
    x /= 10;
  }
  return n;


}

int main(){FIN;

  ll t;
  cin >> t;
  while (t--) {
    ll n;
    cin >> n;
    cout << solve(n) << '\n';
  }


  //force();

  return 0;
}