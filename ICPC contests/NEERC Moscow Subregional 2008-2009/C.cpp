// https://codeforces.com/gym/100861
#include <bits/stdc++.h>
#define fore(i,a,b) for(int i=a,gmat=b;i<gmat;++i)
#define ALL(x) x.begin(),x.end()
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;

ll count1(const vi& Hs) {
  ll N = Hs.size();
  ll ans = 0;

  ans += Hs[0];
  fore(i, 0, N) {
    ans += Hs[i] * 2;
  }
  ans += Hs[N - 1];
  fore(i, 1, N) {
    ans += abs(Hs[i] - Hs[i - 1]);
  }

  return ans;
}

ll count(ll N, ll M, const vi& Hs) {
  if (N == 1 || M == 1) {
    return count1(Hs);
  }
  ll ans = 0;

  ans += Hs[0] * 2;
  //cerr << Hs[0] << ' ';
  //cerr << Hs[0] << ' ';
  fore(i, 1, M - 1) {
    ans += Hs[i] + abs(Hs[i] - Hs[i - 1]);
    //cerr << Hs[i] << ' ';
    //cerr << abs(Hs[i] - Hs[i - 1]) << ' ';
  }
  ans += Hs[M - 1] * 2 + abs(Hs[M - 1] - Hs[M - 2]);
  //cerr << Hs[M - 1] << ' ';
  //cerr << Hs[M - 1] << ' ';
  //cerr << abs(Hs[M - 1] - Hs[M - 2]) << ' ';

  fore(j, 1, N - 1) {
    ans += Hs[j * M] + abs(Hs[j * M] - Hs[(j - 1) * M]);
    //cerr << Hs[j * M] << ' ';
    //cerr << abs(Hs[j * M] - Hs[(j - 1) * M]) << ' ';
    fore(i, 1, M - 1) {
      ans += abs(Hs[j * M + i] - Hs[(j - 1) * M + i]) + abs(Hs[j * M + i] - Hs[j * M + i - 1]);
      //cerr << abs(Hs[j * M + i] - Hs[(j - 1) * M + i]) << ' ';
      //cerr << abs(Hs[j * M + i] - Hs[j * M + i - 1]) << ' ';
    }
    ans += Hs[j * M + M - 1] + abs(Hs[j * M + M - 1] - Hs[(j - 1) * M + M - 1]) + abs(Hs[j * M + M - 1] - Hs[j * M + M - 2]);
    //cerr << Hs[j * M + M - 1] << ' ';
    //cerr << abs(Hs[j * M + M - 1] - Hs[(j - 1) * M + M - 1]) << ' ';
    //cerr << abs(Hs[j * M + M - 1] - Hs[j * M + M - 2]) << ' ';
  }

  ans += Hs[(N - 1) * M] * 2 + abs(Hs[(N - 1) * M] - Hs[(N - 2) * M]);
  //cerr << Hs[(N - 1) * M] << ' ';
  //cerr << Hs[(N - 1) * M] << ' ';
  //cerr << abs(Hs[(N - 1) * M] - Hs[(N - 2) * M]) << ' ';
  fore(i, 1, M - 1) {
    ans += Hs[(N - 1) * M + i] + abs(Hs[(N - 1) * M + i] - Hs[(N - 1) * M + i - 1]) + abs(Hs[(N - 1) * M + i] - Hs[(N - 2) * M + i]);
    //cerr << Hs[(N - 1) * M + i] << ' ';
    //cerr << abs(Hs[(N - 1) * M + i] - Hs[(N - 1) * M + i - 1]) << ' ';
    //cerr << abs(Hs[(N - 1) * M + i] - Hs[(N - 2) * M + i]) << ' ';
  }
  ans += Hs[(N - 1) * M + M - 1] * 2 + abs(Hs[(N - 1) * M + M - 1] - Hs[(N - 1) * M + M - 2]) + abs(Hs[(N - 1) * M + M - 1] - Hs[(N - 2) * M + M - 1]);
  //cerr << Hs[(N - 1) * M + M - 1] << ' ';
  //cerr << Hs[(N - 1) * M + M - 1] << ' ';
  //cerr << abs(Hs[(N - 1) * M + M - 1] - Hs[(N - 1) * M + M - 2]) << ' ';
  //cerr << abs(Hs[(N - 1) * M + M - 1] - Hs[(N - 2) * M + M - 1]) << '\n';


  return ans;
}

pair<ll, vi> force(ll N, ll M, vi Hs) {

  ll ans = 1ll << 60;
  vi ans_val;

  do {
    ll this_ans = count(N, M, Hs);
    if (this_ans < ans) {
      ans_val = Hs;
    }
    ans = min(ans, this_ans);
  } while(next_permutation(ALL(Hs)));

  return {ans, ans_val};
}


ll solve(ll N, ll M, vi Hs) {
  if (M < N) {
    swap(N, M);
  }

  reverse(ALL(Hs));

  vector<vi> pos(N, vi(M, -1));
  ll k = 0;
  fore(i, 0, N) {
    fore(j, 0, i) {
      pos[i][j] = Hs[k];
      k++;
    }
    fore(j, 0, i + 1) {
      pos[j][i] = Hs[k];
      k++;
    }
  }
  fore(i, N, M) {
    fore(j, 0, N) {
      pos[j][i] = Hs[k];
      k++;
    }
  }

  vi hs_(N * M);
  fore(i, 0, N) {
    fore(j, 0, M) {
      hs_[i * M + j] = pos[i][j];
    }
  }

  return count(N, M, hs_);
}

int main(){FIN;

  ll N, M;
  cin >> N >> M;
  vi Hs(N * M);
  for (ll& H : Hs) {
    cin >> H;
  }

  ll ans = solve(N, M, Hs);
  cout << ans << '\n';

	return 0;
}
