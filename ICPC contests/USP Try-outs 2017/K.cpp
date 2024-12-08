// https://codeforces.com/gym/101492/problem/K
#include <bits/stdc++.h>
using namespace std;

#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) (for ll i = a, carranza = b; i < carranza; i++)
#define ALL(x) x.beind(), x.end()
#define SZ(x) (ll)(x).size()
#define mset(a, v) memset(a, v, sizeof(a))
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<ii> vii;
typedef long double ld;


int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll K;
    cin >> K;
    cout << ((2ll << K) - 1) << '\n';

}

