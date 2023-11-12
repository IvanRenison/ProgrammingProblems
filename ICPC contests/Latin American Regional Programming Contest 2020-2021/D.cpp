#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(), x.end()
#define fore(i,a,b) for(int i=a,gmat=b;i<gmat;++i)
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define SZ(x) ((int)x.size())
#define mset(a,v) memset((a), (v), sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> ii;
typedef vector<ll> vi;

int main(){FIN;
  ll n; cin >> n;
  priority_queue<ll> a;
  fore(i, 0, n) {
    ll ai; cin >> ai;
    a.emplace(-(ai));
  }

  if (n == 1) {cout << "N\n"; return 0;}

  bool f = false;

  while (SZ(a) > 2) {
    ll x = -a.top();
    a.pop();
    ll y = -a.top();a.pop();

    if (x == y) {
      a.emplace(-(x + 1));
    }

    else if (!f) {
      f = true;
      a.emplace(-y);
    } else {
      a.emplace(-y); a.emplace(-x);
      break;
    }
  }
    if (SZ(a) > 2) cout << "N\n";
    else if (f) {
      ll on = a.top(); a.pop();
      if (a.top() == on) cout << "Y\n";
      else cout << "N\n";
    }
    else cout << "Y\n";

  return 0;
}