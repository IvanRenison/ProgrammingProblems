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


optional<pair<optional<ull>, optional<ull>>> solve(ull K, vu Ss) {

  vector<ii> counts(K);
  fore(i, 0, K) {
    counts[i].second = i;
  }

  for(ull S : Ss) {
    counts[S].first++;
  }



  sort(ALL(counts));
  ull n = counts.size();

  if (counts.size() > 2) {
    ull b = counts[1].first;
    for(ull i = 2; i + 1 < n; i++) {
      if (b != counts[i].first) {
        return {};
      }
    }

    if (counts[0].first == b) {
      if (b + 1 == counts[n-1].first) {
        return {{{}, counts[n-1].second}};
      } else {
        return {};
      }
    } else if (counts[n-1].first == b) {
      if (counts[0].first + 1 == b) {
        return {{counts[0].second, {}}};
      } else {
        return {};
      }
    } else {
      if (counts[0].first + 1 == b && counts[n-1].first == b + 1) {
        return {{counts[0].second, counts[n-1].second}};
      } else {
        return {};
      }
    }
  } else {
    if (counts[0].first + 1 == counts[n-1].first) {
      return {{counts[0].second, {}}};
    } else if (counts[0].first + 2 == counts[n-1].first) {
      return {{counts[0].second, counts[n-1].second}};
    } else {
      return {};
    }
  }


}


int main(){FIN;
  ull N, K;
  cin >> K >> N;
  vu Ss(N);
  for(ull& S : Ss) {
    cin >> S;
    S--;
  }

  auto ans = solve(K, Ss);

  if (!ans.has_value()) {
    cout << "*\n";
  } else {
    if ((*ans).second.has_value()) {
      cout << "-" << *(*ans).second + 1;
      if ((*ans).first.has_value()) {
        cout << ' ';
      }
    }
    if ((*ans).first.has_value()) {
      cout << "+" << *(*ans).first + 1;
    }
    cout << '\n';
  }

  return 0;
}
