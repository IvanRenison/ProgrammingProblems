// https://codeforces.com/gym/104847/problem/D
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((ll)x.size())
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define mset(a,v) memset((a),(v),sizeof(a))
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;

const vi monthDays {
  31,
  28,
  31,
  30,
  31,
  30,
  31,
  31,
  30,
  31,
  30,
  31
};

bool esBisiestio(ll y) {
  return y % 400 == 0 || (y % 100 != 0 && y % 4 == 0);
}

bool validDate(ll d, ll m, ll y) {
  if (esBisiestio(y) && m == 2) {
    return d <= 29;
  } else {
    return d <= monthDays[m - 1];
  }
}

const vi ttt = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
ll DayOfWeek(ll d, ll m, ll y) {
  y -= m < 3;
  return (y + y/4 - y/100 + y/400 + ttt[m - 1] + d) % 7;
}

void solve1(ll d0, ll m0, ll y0, ll d1, ll m1, ll y1) {
  if (!validDate(d1, m1, y1)) {
    cout << "Unspecified Server Error\n";
  } else {
    if (y1 > y0) {
      cout << "d:" << y1 - y0 << ' ';
    } else if (y1 < y0) {
      cout << "u:" << y0 - y1 << ' ';
    }

    if (m1 > m0) {
      cout << "r:" << m1 - m0 << ' ';
    } else if (m1 < m0) {
      cout << "l:" << m0 - m1 << ' ';
    }

    ll md = DayOfWeek(d1, m1, y1) + 1;
    ll dd0 = DayOfWeek(1, m1, y1) + 1;

    //cerr << md << ' ' << dd0 << '\n';

    cout << "[" << (d1 - 1) / 7 + 1 + (md < dd0) << "][" << md << "]\n";
  }
}

int main(){FIN;

  ll t;
  cin >> t;
  fore(i, 0, t) {
    ll d0, m0, y0, d1, m1, y1;
    cin >> d0 >> m0 >> y0 >> d1 >> m1 >> y1;
    solve1(d0, m0, y0, d1, m1, y1);
  }

  return 0;
}