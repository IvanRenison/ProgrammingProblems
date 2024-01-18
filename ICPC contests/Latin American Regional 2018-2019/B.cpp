// https://matcomgrader.com/problem/9543/building-a-field/

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef vector<ull> vu;
typedef vector<ll> vi;
typedef pair<ull, ull> uu;
typedef pair<ll, ll> ii;
typedef vector<uu> vuu;
typedef vector<ii> vii;
typedef tuple<ull, ull, ull> uuu;
typedef tuple<ll, ll, ll> iii;
typedef vector<uuu> vuuu;
typedef vector<iii> viii;
typedef tuple<ull, ull, ull, ull> uuuu;
typedef tuple<ll, ll, ll, ll> iiii;
typedef vector<uuuu> vuuuu;
typedef vector<iiii> viiii;
typedef tuple<ull, ull, ull, ull, ull> uuuuu;
typedef tuple<ll, ll, ll, ll, ll> iiiii;
typedef vector<uuuuu> vuuuuu;
typedef vector<iiiii> viiiii;
typedef long double ld;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()
#define DBG(x) cerr << #x << " = " << x << endl


bool solve(vu Ls) {
  ull N = Ls.size();

  ull sum = 0;
  for(ull L : Ls) {
    sum += L;
  }

  if (sum % 2 == 1) {
    return false;
  }

  ull i = 0, j = 1;
  ull sep = Ls[0];
  ull count = 0;

  while(j < N) {
    if (sep == sum / 2) {
      count++;
      sep -= Ls[i], sep += Ls[j];
      i++, j++;
    } else if (sep < sum / 2) {
      sep += Ls[j];
      j++;
    } else {
      sep -= Ls[i];
      i++;
    }
  }

  return count >= 2;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N;
  cin >> N;
  vu Ls(N);
  for(ull& L : Ls) {
    cin >> L;
  }

  if (solve(Ls)) {
    cout << "Y\n";
  } else {
    cout << "N\n";
  }

  return EXIT_SUCCESS;
}
