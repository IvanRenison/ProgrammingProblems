// https://codeforces.com/gym/101243
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(), x.end()
#define SZ(x) ((int)x.size())
#define fore(i, a, b) for (int i = a, thxMat = b; i < thxMat; ++i)
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const ll MAXN = 1e5 + 10;
const ll MOD = 1e9 + 7;

ll n;
string s;
vector<vector<ll>> dp(MAXN, vector<ll>(2, -1));
ll cnt(ll pos, bool first)
{
    if (pos == n)
        return 1;

    ll &r = dp[pos][first];
    if (r != -1)
        return r;
    if (!first)
        return r = cnt(pos + 1, true);

    if ((s[pos] == 'N' || s[pos] == 'S') && pos < n - 1 && (s[pos + 1] == 'W' || s[pos + 1] == 'E'))
    {
        return r = (cnt(pos + 1, true) + cnt(pos + 1, false)) % MOD;
    }

    return r = cnt(pos + 1, true);
}

int main()
{
    FIN;

#ifdef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    cin >> s;
    n = SZ(s);

    cout << cnt(0, true) << "\n";

    return 0;
}
