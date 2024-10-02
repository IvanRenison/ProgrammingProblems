// https://codeforces.com/gym/104875
#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(x) x.begin(),x.end()
#define SZ(x) ll(x.size())
#define fore(i,a,b) for(ll i=a, gmat=b;i<gmat;++i)
#define mset(a,v) memset((a),(v),sizeof(a))
#define pb push_back
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;
typedef unsigned int uint;

enum QType { Left, Right, Flip };


bool query(QType t) {
  cout << "? " << vector<string>{"left", "right", "flip"}[t] << endl;

  bool b;
  cin >> b;

  return b;
}

/* // Testing
vector<bool> vals;
ll curr = 0;
ll i = 0;
void init() {
  vals = {};
  i = 0;
  curr = 0;
  ll n = rand() % 500 + 3;
  fore(i, 0, n) {
    vals.push_back(rand() % 2);
  }
}
bool query(QType t) {
  i++;
  assert(i <= 2*vals.size() + 500);
  //cerr << "? " << vector<string>{"left", "right", "flip"}[t] << endl;
  ll n = vals.size();
  if (t == Left) {
    curr = (curr + n - 1) % n;
  } else if (t == Right) {
    curr = (curr + 1) % n;
  } else {
    vals[curr] = !vals[curr];
  }
  //cerr << vals[curr] << endl;
  return vals[curr];
} */


ll solve(bool b) {

  fore(_, 0, 35) {
    if (b) {
      query(Flip);
    }
    b = query(Right);
  }
  if (!b) {
    b = query(Flip);
  }

  fore(i, 0, 35) {
    b = query(Left);
    if (b) {
      return i + 1;
    }
  }

  uint x = 0b11010001101001010011001010000010;
  fore(i, 0, 32) {
    if (x & (1 << i)) {
      query(Flip);
    }
    b = query(Right);
  }

  ll ans = 0;

  uint lasts = ((uint)b) << 31;

  while (lasts != x) {
    b = query(Right);
    lasts >>= 1;
    lasts |= ((uint)b) << 31;
    ans++;
    assert(ans <= 5000);
  }

  return ans + 1;
}

int main(){FIN;

  bool b;
  cin >> b;

  ll ans = solve(b);

  cout << "! " << ans << endl;

/*   fore(i, 0, 100) {
    init();
    bool b = vals[0];

    ll ans = solve(b);
    if (ans != vals.size()) {
      cerr << "ERROR:\n";
      cerr << "ans: " << ans << '\n';
      cerr << "vals.size(): " << vals.size() << '\n';
      return EXIT_FAILURE;
    }

    //cerr << "! " << ans << endl;
  } */

  return 0;
}
