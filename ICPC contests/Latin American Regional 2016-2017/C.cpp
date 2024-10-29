// https://matcomgrader.com/problem/9281/counting-self-rotating-subsets
#include "bits/stdc++.h"
#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) for (ll i = a, gmat = b; i < gmat; ++i)
#define ALL(x) x.begin(), x.end()
#define SZ(x) ((ll)x.size())
#define mset(a, v) memset((a), (v), sizeof(a))
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;


const ll mod = 1e9 + 7;

struct Mod {
    ll x;
    Mod(ll x = 0) : x(x) {}
    Mod operator+(Mod o) { return (x + o.x) % mod; }
    Mod operator-(Mod o) { return (x + mod - o.x) % mod; }
    Mod operator*(Mod o) { return (x * o.x) % mod; }
    Mod invert() {
        return pow(mod - 2);
    }
    Mod pow(ll e) {
        Mod ans(1);
        for (Mod b = *this; e; b = b * b, e >>= 1)
            if (e & 1) ans = ans * b;
        return ans;
    }
};

const ll N_lim = 1001;
vector<Mod> facts(N_lim), inv_facts(N_lim);

void init() {
    facts[0] = inv_facts[0] = Mod(1);
    fore(i, 1, N_lim) {
        facts[i] = facts[i - 1] * Mod(i);
        inv_facts[i] = facts[i].invert();
    }
}

Mod comb(ll a, ll b) {
    return facts[a] * inv_facts[b] * inv_facts[a - b];
}

ii operator+(ii a, ii b) {
    return {a.fst + b.fst, a.snd + b.snd};
}

vector<Mod> solve(vii& points) {
    ll N = points.size();

    map<ii, ll> centers;
    fore(i, 0, N) fore(j, 0, i) {
        centers[points[i] + points[j]]++;
    }
    set<ii> singles(ALL(points));

    vector<Mod> ans(N);

    ans[0] = N;

    for (auto it : centers) {
        ii p = it.fst;
        ll c = it.snd;
        bool single = false;
        if (abs(p.fst) % 2 == 0 && abs(p.snd) % 2 == 0) {
            single = singles.count({p.fst / 2, p.snd / 2});
        }
        //cerr << p.fst << ' ' << p.snd << ' ' << c << ' ' << single << endl;
        fore(i, 1, c + 1) {
            Mod val = comb(c, i);
            ans[2 * i - 1] = ans[2 * i - 1] + val;
            if (single) {
                ans[2 * i] = ans[2 * i] + val;
            }
        }
    }

    return ans;
}


int main() {
    ios::sync_with_stdio(0), cin.tie(0);

    init();

    ll N;
    cin >> N;
    vii points(N);
    fore(i, 0, N) {
        cin >> points[i].fst >> points[i].second;
    }

    vector<Mod> ans = solve(points);
    fore(i, 0, N) {
        cout << ans[i].x << ' ';
    }
    cout << "\n";

}
