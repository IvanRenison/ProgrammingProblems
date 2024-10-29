// https://matcomgrader.com/problem/9285/game-of-matchings
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

typedef uint64_t ull;
struct H {
    ull x; H(ull x = 0) : x(x) {}
    H operator+(H o) { return x + o.x + (x + o.x < x);}
    H operator-(H o) { return *this + ~o.x; }
    H operator*(H o) { auto m = (__uint128_t)x * o.x;
        return H((ull)m) + (ull)(m >> 64); }
    ull get() const {return x + !~x;}
    bool operator==(H o) { return get() == o.get(); }
};
static const H C = (ll)1e11+3;

struct HashInterval {
    vector<H> ha, pw;
    HashInterval(string& str) : ha(SZ(str)+1), pw(ha) {
        pw[0] = 1;
        fore(i,0,SZ(str)) {
            ha[i+1] = ha[i] * C + str[i];
            pw[i+1] = pw[i] * C;
        }
    }
    H hashInterval(ll a, ll b) {
        return ha[b] - ha[a] * pw[b - a];
    }
};

ll solve(string& S, vi& Ps) {
    ll M = S.size(), N = Ps.size();

    vector<HashInterval> S_hashes, Ps_hashes;
    fore(i, 0, 26) {
        string t;
        for (char c : S) {
            if (c - 'a' == i) {
                t += '1';
            } else {
                t += '0';
            }
        }
        S_hashes.push_back(HashInterval(t));
    }
    fore(i, 0, 26) {
        string t;
        for (ll P : Ps) {
            if (P == i) {
                t += '1';
            } else {
                t += '0';
            }
        }
        Ps_hashes.push_back(HashInterval(t));
    }

    vi first(26, -1);
    fore(i, 0, N) {
        if (first[Ps[i]] == -1) {
            first[Ps[i]] = i;
        }
    }

    ll ans = 0;
    fore(l, 0, M - N + 1) {
        vi mp(26, -1);
        fore(c, 0, 26) {
            ll i = first[c];
            if (i != -1) {
                mp[c] = S[l + i] - 'a';
            }
        }

        bool valid = true;
        fore(c, 0, 26) {
            if (mp[c] != -1) {
                ll c2 = mp[c];
                H hP = Ps_hashes[c].hashInterval(0, N);
                H hS = S_hashes[c2].hashInterval(l, l + N);
                if (!(hP == hS)) {
                    valid = false;
                    break;
                }
            }
        }

        ans += valid;
    }

    return ans;
}


int main() {
    ios::sync_with_stdio(0), cin.tie(0);


    string S;
    cin >> S;
    ll N;
    cin >> N;
    vi Ps(N);
    for (ll& P : Ps) {
        cin >> P;
        P--;
    }
    cout << solve(S, Ps) << '\n';

}
