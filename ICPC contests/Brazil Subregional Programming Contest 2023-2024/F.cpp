// https://codeforces.com/gym/104555/problem/F
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) for (int i = a, gmat = b; i < gmat; ++i)
#define SZ(x) ((int)x.size())
#define ALL(x) x.begin(), x.end()
#define FIN                  \
    ios::sync_with_stdio(0); \
    cin.tie(0), cout.tie(0)
#define mset(a, v) memset((a), (v), sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int main()
{
    FIN;

    ll d, c, r;
    cin >> d >> c >> r;
    vector<ll> a(c);
    fore(i, 0, c) cin >> a[i];
    ll s = d;
    fore(i, 0, r)
    {
        ll si;
        cin >> si;
        s += si;
    }
    ll res = r;
    fore(i, 0, c)
    {
        if (a[i] <= s)
        {
            res++;
            s -= a[i];
        }
        else
            break;
    }

    cout << res << "\n";

    return 0;
}
