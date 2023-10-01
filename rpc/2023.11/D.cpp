// https://redprogramacioncompetitiva.com/contests/2023/11

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef vector<ull> vu;
typedef vector<ll> vi;
typedef pair<ull, ull> uu;
typedef pair<ll, ll> ii;
typedef vector<uu> vuu;
typedef vector<ii> vii;
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)

ll fth(ll a)
{
    return a * a * a * a;
}

ll sq(ll a)
{
    return a * a;
}

ll b, a, r;
ld eval(ld x)
{
    return (ld)(b) - ((ld)(b) / (ld)(a)) * x;
}

ld angle(ld x, ld y)
{
    return atan2(y, x);
}

ll sgn(ld x)
{
    return (x > 0) - (x < 0);
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    cin >> b >> a >> r;

    ll cont = -sq(b) * fth(a) + fth(a) * sq(r) + sq(a) * sq(b) * sq(r);

    if (cont < 0)
    {
        cout << -1 << "\n";
        return 0;
    }

    ll ind = a * sq(b);
    ll den = sq(a) + sq(b);

    ld x1 = ((ld)(ind)-sqrtl(cont)) / (ld)(den);
    // if (sgn(a) != sgn(x1))
    // x1 *= -1;
    ld y1 = eval(x1);

    ld x2 = (sqrtl(cont) + (ld)(ind)) / (ld)(den);
    // if (sgn(a) != sgn(x2))
    // x2 *= -1;
    ld y2 = eval(x2);

    ld rad = (y1 < y2 ? angle(x1, y1) : angle(x2, y2));
    ld ang = (rad * 180) / acosl(-1);

    ang = min(ang, (ld)(180) - ang);
    cout << setprecision(16) << ang << "\n";

    return EXIT_SUCCESS;
}
