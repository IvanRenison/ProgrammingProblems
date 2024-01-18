// https://codeforces.com/gym/101889
#include<bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define fore(i,a,b) for(int i=a,gmat=b;i<gmat;i++)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(),x.end()
#define mset(a,v) memset((a),(v),sizeof(a))
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ull> vu;

string s;
ll n;

vector<short> mem;
short test(ll id, ll targ, ll k, bool fl)
{
  if (mem[id] != -1) return mem[id];
  if (s[id] == 'P')
    return mem[id] = 0;

  if (id == targ && !fl)
    return mem[id] = 1;

  return mem[id] = test((id + k) % n, targ, k, false);
}

int main(){FIN;

  cin >> s;
  n = SZ(s);
  mem.resize(n, -1);

  vector<bool> can(n);
  vector<ll> rs;
  fore(i, 0, n) if (s[i] == 'R') rs.pb(i);

  fore(k, 1, n) {
    if (can[k]) continue;

    if (n % k != 0)
      {
        can[k] = can[gcd(k, n)];
        continue;
      }

    fill(ALL(mem), -1);
    for (ll id : rs) {
      if (test(id, id, k, true)) {
        for(ll i = k; i < n; i += k) {
          can[i] = true;
        }
        break;
      }
    }
  }

  ll ans = 0;
  fore(i, 0, n) if (can[i]) ans++;

  cout << ans << "\n";

  return 0;
}