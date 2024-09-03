// https://codeforces.com/gym/105321/problem/D
#include <bits/stdc++.h>
#define ALL(x) x.begin(), x.end()
using namespace std;
typedef long long ll;
typedef vector<ll> vi;

int main() {
  ios::sync_with_stdio(0), cin.tie(0);

  vi ABC(3);
  cin >> ABC[0] >> ABC[1] >> ABC[2];
  sort(ALL(ABC));
  bool ans = ABC[2] >= ABC[1] + ABC[0];
  cout << (ans ? 'S' : 'N') << '\n';

}
