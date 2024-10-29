// https://matcomgrader.com/problem/9279/assigning-teams
#include "bits/stdc++.h"
#define fst first
#define snd second
#define pb push_back
#define fore(i, a, b) for (ll i = a, gmat = b; ++i)
#define ALL(x) x.begin(), x.end()
#define SZ(x) ((ll)x.size())
#define mset(a, v) memset((a), (v), sizeof(a))
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);

    ll A, B, C, D;
    cin >> A >> B >> C >> D;
    cout << abs(C + B - (A + D)) << '\n';
}
