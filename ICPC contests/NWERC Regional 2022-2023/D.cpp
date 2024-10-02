// https://codeforces.com/gym/104875
#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(x) x.begin(), x.end()
#define SZ(x) ll(x.size())
#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; ++i)
#define mset(a, v) memset((a), (v), sizeof(a))
#define pb push_back
#define FIN ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
typedef int ll;
typedef double ld;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
const vector<ii> dir{{0, 1}, {1, 0}};
const vector<ii> dirj{{0, 1}};
const vector<ii> diri{{1, 0}};
constexpr ld INF = 1e13;
constexpr ld EPS = 1e-5;

ll h, w;

ll id(ll i, ll j) {
    return i * (w * 2 + 1) + j;
}

const ld Q = numbers::pi * 2.5;

vector<ld> d;
vector<vector<pair<ll, ld>>> g;
void dijkstra(ll s) {
    d[s] = 0;
    priority_queue<pair<ld, ll>, vector<pair<ld, ll>>, greater<pair<ld, ll>>> q;
    q.push({0, s});
    while (!q.empty()) {
        ll v = q.top().second;
        ld d_v = q.top().first;
        q.pop();
        if (abs(d_v - d[v]) > EPS)
            continue;

        for (auto edge : g[v]) {
            ll to = edge.first;
            ld len = edge.second;

            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                q.push({d[to], to});
            }
        }
    }
}

int main() {
    FIN;
    cin >> h >> w;

    vector<vector<bool>> m(h, vector<bool>(w));

    fore(i, 0, h) {
        string row;
        cin >> row;
        fore(j, 0, w) {
            m[i][j] = row[j] == 'O';
        }
    }

    ll sz = (h * 2 + 1) * (w * 2 + 1);
    d.resize(sz, INF);
    g.resize(sz);

    fore(i, 0, h * 2 + 1) fore(j, 0, w * 2 + 1) {
        if (i & 1 && j & 1) continue;
        vector<ii> v = (i & 1) ? diri : ((j & 1) ? dirj : dir);
        for (auto [di, dj] : v) {
            ll ni = i + di, nj = j + dj;
            if (0 <= ni && ni < h * 2 + 1 && 0 <= nj && nj < w * 2 + 1)
                g[id(i, j)].pb({id(ni, nj), 5});
        }
        if (i & 1 && j / 2 < w && m[i / 2][j / 2]) {
            // g[id(i, j)].pb({id(i - 1, j + 1), Q});
            g[id(i, j)].pb({id(i + 1, j + 1), Q});
        }
        if (j & 1 && i / 2 < h && m[i / 2][j / 2]) {
            // g[id(i, j)].pb({id(i + 1, j - 1), Q});
            g[id(i, j)].pb({id(i + 1, j + 1), Q});
        }
        // if (i & 1 && j / 2 - 1 >= 0 && m[i / 2][j / 2 - 1]) {
        //     g[id(i, j)].pb({id(i + 1, j - 1), Q});
        //     g[id(i, j)].pb({id(i - 1, j - 1), Q});
        // }
        // if (j & 1 && i / 2 - 1 >= 0 && m[i / 2 - 1][j / 2]) {
        //     g[id(i, j)].pb({id(i - 1, j + 1), Q});
        //     g[id(i, j)].pb({id(i - 1, j - 1), Q});
        // }
    }

    dijkstra(0);

    cout << fixed << setprecision(16) << d[sz - 1] << "\n";

    return 0;
}
