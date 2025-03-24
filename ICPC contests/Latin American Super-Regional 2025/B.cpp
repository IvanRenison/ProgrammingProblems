// https://codeforces.com/gym/105789/problem/B
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((ll)x.size())
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define mset(a,v) memset((a),(v),sizeof(a))
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;

const ll lim = 1502;

typedef bitset<lim> B;

bool operator<(const B& a, const B& b) {
  B ab = a ^ b;
  if (ab.count() == 0) {
    return false;
  }
  ll first = ab._Find_first();
  if (a[first] < b[first]) {
    return true;
  } else {
    return false;
  }
}

optional<vi> solve(ll K, vector<B>& As) {
  ll N = As.size();
  fore(i, 0, N) {
    As[i][lim-1] = 1;
  }

  vector<B> base;
  vector<B> cons;

  fore(i, 0, N) {
    B A = As[i];
    B A_cons;
    A_cons[i] = 1;

    fore(j, 0, base.size()) {
      B A2 = A ^ base[j];
      if (A2 < A) {
        A = A2;
        A_cons ^= cons[j];
      }
    }

    if (A.count() == 0) {
      ll count = A_cons.count();
      assert(count % 2 == 0);
      vi ans(N);
      ll counted = 0;
      fore(j, 0, N) {
        if (A_cons[j]) {
          if (counted < count / 2) {
            ans[j] = 1;
          } else {
            ans[j] = 2;
          }
          counted++;
        } else {
          ans[j] = 0;
        }
      }
      return ans;
    }

    base.push_back(A);
    cons.push_back(A_cons);
  }


  return {};
}

int main(){
    ios::sync_with_stdio(0),cin.tie(0);

  ll N, K;
  cin >> N >> K;
  vector<B> As(N);
  fore(i, 0, N) {
    fore(j, 0, K) {
      char c;
      cin >> c;
      if (c == '1') {
        As[i][j] = 1;
      }
    }
  }

  auto ans = solve(K, As);
  if (ans.has_value()) {
    fore(i, 0, N) {
      cout << (*ans)[i];
    }
  } else {
    cout << '*';
  }
  cout << '\n';

}