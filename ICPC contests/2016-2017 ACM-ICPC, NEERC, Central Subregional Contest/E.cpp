// https://codeforces.com/gym/101243
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((int) x.size())
#define fore(i,a,b) for(int i=a,thxMat=b;i<thxMat;++i)
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

bool solve(ull K, vector<ull>& as) {
  ull N = as.size();

  ull max_index = 0;
  fore(i, 1, N) {
    if (as[i] > as[max_index]) {
      max_index = i;
    }
  }

  ull min_before = max_index;
  ull max_before = 0;
  fore(i, 0, max_index) {
    max_before += as[i];
  }

  ull min_after = N - max_index - 1;
  ull max_after = 0;
  fore(i, max_index + 1, N) {
    max_after += as[i];
  }


  ull current_min = min_before, current_max = max_before;
  while(current_min <= K) {
    if (current_max >= K) {
      return true;
    }

    current_min += as[max_index] + min_after + min_before;
    current_max += as[max_index] + max_after + max_before;
  }

  return false;
}

int main(){FIN;
#ifdef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif

  ull N, K;
  cin >> N >> K;
  vector<ull> as(N);
  for(ull& a : as) {
    cin >> a;
  }

  if (solve(K, as)) {
    cout << "YES\n";
  } else {
    cout << "KEK\n";
  }

  return 0;
}
