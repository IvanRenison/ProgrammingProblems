// https://codeforces.com/gym/104172/problem/H
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

int main() {
    ios::sync_with_stdio(0), cin.tie(0);

    ll l, r, b, k;
    cin >> l >> r >> b >> k;

    ll every = (l + b - 1) / b;

    ll ans = b * k * every;
    cout << ans << "\n";
}