// https://codeforces.com/gym/102299/problem/H
#include <bits/stdc++.h>
#define fst first
#define snd second
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((int)x.size())
#define fore(i,a,b) for(int i=a,thxmat=b;i<thxmat;i++)
#define pb push_back
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

constexpr ull INF = 1ull << 60;

vector<optional<ull>> solve(ull M, vector<vector<pair<ull, ull>>> cgss) {
    ull N = cgss.size();

    vector<vector<optional<ull>>> grades(N, vector<optional<ull>>(M));

    fore(i, 0, N) {
    for(auto [c, g] : cgss[i]) {
        grades[i][c] = g;
    }
    }

    vector<vector<ull>> dists(N, vector<ull>(N));

    fore(i, 0, N) {
    fore(j, i+1, N) {
        ull dist = 0;
        bool valid = false;
        fore(k, 0, M) {
        auto gi = grades[i][k], gj = grades[j][k];
        if (gi.has_value() && gj.has_value()) {
            dist += (*gi - *gj)*(*gi - *gj);
            valid = true;
        }
        }

        if (valid) {
        dists[i][j] = dists[j][i] = dist;
        } else {
        dists[i][j] = dists[j][i] = INF;
        }
    }
    }

    vector<optional<ull>> ans(N);

    fore(i, 0, N) {
    ull closest_d = INF;
    ull closest_i = 0;

    fore(j, 0, N) {
        if (i != j) {
        if (dists[i][j] < closest_d) {
            closest_d = dists[i][j];
            closest_i = j;
        }
        }
    }

    ull rec_grade, rec_k;
    ull rec_valid = false;
    fore(k, 0, M) {
        if (grades[closest_i][k].has_value() && !grades[i][k].has_value()) {
        ull g = grades[closest_i][k].value();
        if (!rec_valid || rec_grade < g) {
            rec_valid = true;
            rec_grade = g, rec_k = k;
        }
        }
    }

    if (rec_valid) {
        ans[i] = rec_k;
    }
    }

    return ans;
}

int main(){FIN;

    ull N, M;
    cin >> N >> M;
    vector<vector<pair<ull, ull>>> cgss(N);
    fore(i, 0, N) {
    ull Q;
    cin >> Q;
    cgss[i] = vector<pair<ull, ull>>(Q);
    for(auto& cg : cgss[i]) {
        ull c, g;
        cin >> c >> g;
        c--;
        cg.first = c, cg.second = g;
    }

    }

    auto ans = solve(M, cgss);
    for(auto x : ans) {
    if (x.has_value()) {
        cout << *x + 1 << '\n';
    } else {
        cout << "-1\n";
    }
    }

    return 0;
}