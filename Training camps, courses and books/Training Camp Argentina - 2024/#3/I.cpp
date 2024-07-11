// https://codeforces.com/group/5GNF7zti59/contest/535420/problem/I
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;


const string f0 = "What are you doing at the end of the world? Are you busy? Will you save us?";
const ll c0 = f0.size();
const string fl = "What are you doing while sending \"";
const ll cl = fl.size();
const string fm = "\"? Are you busy? Will you send \"";
const ll cm = fm.size();
const string fr = "\"?";
const ll cr = fr.size();

const ll maxn = 1e5;
const ll inf = 1ll << 61;

vi tams(maxn + 1, inf);

void init() {
  tams[0] = c0;
  fore(i, 0, maxn) {
    if (tams[i] >= inf) {
      tams[i] = inf;
      break;
    }
    tams[i + 1] = 2 * tams[i] + cl + cm + cr;
  }
}

char solve(ll n, ll k) {
  if (n == 0) {
    if (k >= c0) {
      return '.';
    } else {
      return f0[k];
    }
  }

  if (k < cl) {
    return fl[k];
  } else if (k < cl + tams[n - 1]) {
    return solve(n - 1, k - cl);
  } else if (k < cl + tams[n - 1] + cm) {
    return fm[k - (cl + tams[n - 1])];
  } else if (k < cl + tams[n - 1] + cm + tams[n - 1]) {
    return solve(n - 1, k - (cl + tams[n - 1] + cm));
  } else if (k < cl + tams[n - 1] + cm + tams[n - 1] + cr) {
    return fr[k - (cl + tams[n - 1] + cm + tams[n - 1])];
  } else {
    return '.';
  }
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

  init();

  ll q;
  cin >> q;
  while (q--) {
    ll n, k;
    cin >> n >> k;
    k--;
    char ans = solve(n, k);
    cout << ans;
  }
  cout << '\n';

}