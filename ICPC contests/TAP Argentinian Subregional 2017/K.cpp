// https://codeforces.com/group/YjFmW2O15Q/contest/101811
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define SZ(x) ((ll)x.size())
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;
typedef tuple<ll,ll,ll> iii;
typedef vector<iii> viii;

ll count(ll x) {
  ll ans = 0;
  while (x % 2 == 1) {
    x /= 2;
    ans++;
  }
  return ans;
}

ll solve(vi& Ss) {

  ll N = Ss.size();

  bool mul4 = false;
  for (ll S : Ss) {
    if (S % 4 == 0) {
      mul4 = true;
      break;
    }
  }

  vi counts(N);
  fore(i, 0, N) {
    counts[i] = count(Ss[i]);
  }

  ll mini = 1e18;
  fore(i,0,N){
    if((Ss[i]%4) && !(Ss[i]%2)){
        ll aux = Ss[i]/2;
        ll x = 1;
        while(aux%2!=0){
            aux/=2;
            ++x;
        }
        mini = min(mini,x);
    }
  }
    // cout << mini << "\n";

  sort(ALL(counts));
  reverse(ALL(counts));

  ll count_ones = 0;
  while (!counts.empty()) {
    if (counts.back() == 0) {
      counts.pop_back();
    } else if (counts.back() == 1) {
      counts.pop_back();
      count_ones++;
    } else {
      break;
    }
  }

  ll i = 0;
  ll aux = 0;
  while (counts.size() - i > count_ones) {
    if (counts.size() - i == 1) {
        // cout << aux << " " << mini << "\n";
      return i + 1 + (!mul4&&aux+1<mini);
    }
    ll b = counts.back();
    counts.pop_back();
    b--;aux++;
    if (b > 1) {
      counts.push_back(b);
    } else {
      aux=0;
      count_ones++;
    }
    mini = min(mini,counts[i]+1);
    i++;
  }

  ll ans = (count_ones + counts.size() - i + 1) / 2 + i;

  return ans;
}

ll force(vi Ss, ll prof = 0) {
  ll N = Ss.size();
  if (prof > N) {
    return 1ll << 60;
  }
  bool all_even = true;
  fore(i, 0, N) {
    if (Ss[i] % 2 == 1) {
      all_even = false;
      break;
    }
  }
  if (all_even) {
    return 0;
  }

  ll ans = 1ll << 60;

  fore(i, 0, N) {
    fore(j, 0, N) if (j != i) {
      vi Ss_ = Ss;
      Ss_[i] *= 2;
      Ss_[j] /= 2;

      ll this_ans = 1 + force(Ss_, prof + 1);
      ans = min(ans, this_ans);
    }
  }

  return ans;
}

int main(){
  ios::sync_with_stdio(0),cin.tie(0);

#ifndef TEST
  ll N;
  cin >> N;
  vi Ss(N);
  for (ll& S : Ss) {
    cin >> S;
  }

  cout << solve(Ss) << '\n';
#else
  fore(_, 0, 100000) {
    ll N = 5;
    vi Ss(N);
    for (ll& S : Ss) {
      S = rand() % 20;
    }

    ll ans = solve(Ss);
    ll ansf = force(Ss);
    if (ans != ansf) {
      cout << N << '\n';
      for (ll S : Ss) {
        cout << S << ' ';
      }
      cout << '\n';
      cout << ans << ' ' << ansf << endl;
      return 1;
    }
    cout << _ << " passed" << endl;
  }
#endif
}