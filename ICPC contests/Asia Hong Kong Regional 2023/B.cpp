// https://codeforces.com/gym/104172/problem/B
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(), x.end()
#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; ++i)
#define mset(a, v) memset((a), (v), sizeof(a))
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;

constexpr ll MOD = 998244353;
struct Mod {
    ll x;
    Mod(ll xx) : x(xx) {}
    Mod() : x(0) {}
    Mod operator+(Mod b) { return Mod((x + b.x) % MOD); }
    Mod operator-(Mod b) { return Mod((x - b.x + MOD) % MOD); }
    Mod operator*(Mod b) { return Mod((x * b.x) % MOD); }
};

// typedef long double Mod;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);

    ll n, m;
    cin >> n >> m;

    vector p(n + 1, vector<Mod>(m + 1)), q(n + 1, vector<Mod>(m + 1));
    p[0][m - 1] = 1;
    fore(i, 1, n + 1) fore(j, 1, m + 1) {
        ll x;
        cin >> x;
        p[i][j] = x;
    }
    q[n - 1][0] = 1;
    fore(i, 1, n + 1) fore(j, 1, m + 1) {
        ll x;
        cin >> x;
        q[i][j] = x;
    }
    vector rpre(n + 2, vector<Mod>(m + 2)), cpre(n + 2, vector<Mod>(m + 2));
    fore(i, 0, n + 1) fore(j, 0, m + 1) {
        rpre[i][j + 1] = rpre[i][j] + p[i][j];
    }
    fore(j, 0, m + 1) fore(i, 0, n + 1) {
        cpre[i + 1][j] = cpre[i][j] + q[i][j];
    }
    fore(i, 0, n + 2) {
        rpre[i][m + 1] = 1;
        cpre[i][m + 1] = 1;
    }
    fore(j, 0, m + 2) {
        rpre[n + 1][j] = 1;
        cpre[n + 1][j] = 1;
    }

    // cerr << "rpre" << endl;
    fore(i, 0, n + 2) {
        // fore(j, 0, m + 2) cerr << rpre[i][j] << " ";
        // cerr << endl;
    }
    // cerr << "cpre" << endl;
    fore(i, 0, n + 2) {
        // fore(j, 0, m + 2) cerr << cpre[i][j] << " ";
        // cerr << endl;
    }

    Mod ans(0);
    fore(i, 0, n + 1) fore(j, 0, m + 1) {
        Mod pr = 1;
        pr = pr * (Mod(1) - cpre[i][j + 1]);
        pr = pr * (Mod(1) - rpre[i + 1][j]);
        pr = pr * cpre[i][j] * rpre[i][j];
        // cerr << "pr " << i << " " << j << ": " << pr << endl;
        ans = ans + pr;
    }
    cout << ans.x + 2 << "\n";
}
