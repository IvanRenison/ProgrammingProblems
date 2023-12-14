// https://codeforces.com/gym/100861
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define fore(i,a,b) for(int i=a,gmat=b;i<gmat;++i)
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define mset(a,v) memset((a),(v),sizeof(a))
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;

vi solve(ll F1, ll A, ll B, ll C, const vector<vi>& zss) {
  ll M = zss.size(), N = zss[0].size();

  map<ll, ll> comps;
  fore(i, 0, M) {
    fore(j, 0, N) {
      comps[zss[i][j]]++;
    }
  }

  ll days = comps.size();
  vii comps_c_z(days);
  ll i = 0;
  for (auto it = comps.begin(); it != comps.end(); it++, i++){
    comps_c_z[i] = {it->second, it->first};
  }

/*   fore(i, 0, days) {
    //cerr << "comps_c_z " << i << ' '<< comps_c_z[i].first << ' ' << comps_c_z[i].second << '\n';
  } */

  vii Fs_i(days);
  Fs_i[0].first = F1;
  fore(i, 1, days) {
    Fs_i[i].first = ((A * Fs_i[i - 1].first + B) % C) + 1;
    Fs_i[i].second = i;
  }
  //cerr << "hkl ";

/*   fore(i, 0, days) {
    //cerr << Fs_i[i].first << ' ';
  } */

  sort(ALL(comps_c_z));
  sort(ALL(Fs_i));
  reverse(ALL(comps_c_z));
  reverse(ALL(Fs_i));

  vi ans(days);
  fore(j, 0, days) {
    auto [F, i] = Fs_i[j];

    ans[i] = comps_c_z[j].second;
  }



  return ans;
}

int main(){FIN;

  ll F1, A, B, C, N, M;
  cin >> F1 >> A >> B >> C >> N >> M;
  vector<vi> zss(M, vi(N));
  for(vi& zs : zss) {
    for(ll& z : zs) {
      cin >> z;
    }
  }

  vi ans = solve(F1, A, B, C, zss);
  cout << ans.size() << '\n';
  for(ll a : ans) {
    cout << a << ' ';
  }
  cout << '\n';

	return 0;
}