// https://codeforces.com/gym/104736/problem/B
#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef long double ld;
typedef vector<ld> vd;
typedef pair<ld, ld> dd;
typedef vector<dd> vdd;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

bool solve(vi& Bs) {
  ull N = Bs.size() / 3;

  ll sum0 = 0;
  ll sum1 = 0;
  fore(i, 0, N) {
    sum0 += Bs[3*i];
    sum1 += Bs[3*i+1];
  }

  return sum0 != sum1;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N;
  cin >> N;
  vi Bs(3*N);
  for (ll& B : Bs) {
    cin >> B;
  }

  sort(Bs.begin(), Bs.end());

  auto ans = solve(Bs);
  reverse(Bs.begin(), Bs.end());
  ans = ans || solve(Bs);
  if (ans) {
    cout << "Y\n";
  } else {
    cout << "N\n";
  }

  return EXIT_SUCCESS;
}
