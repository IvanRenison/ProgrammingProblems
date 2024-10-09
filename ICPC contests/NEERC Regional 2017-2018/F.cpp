// https://codeforces.com/gym/101630
#include <bits/stdc++.h>
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(ll i=a,gmat=b;i<gmat;++i)
#define SZ(x)  (ll(x.size()))
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;
typedef vector<ii> vii;
typedef tuple<ll,ll,ll> iii;
typedef vector<iii> viii;
typedef tuple<ll,ll,ll,ll> iiii;
typedef vector<iiii> viiii;

#ifndef TEST
#undef assert
#define assert(x) ;
#endif

enum Dir {
    UP, DOWN, LEFT, RIGHT
};

bool isVer(Dir d) {
    return d == UP || d == DOWN;
}

ll n;

struct L {
    ll x, y; // Centro
    Dir ver; // Dirección vertical
    Dir hor; // Dirección horizontal

    void rflVer() {
        y = -y;
        if (ver == UP) ver = DOWN;
        else ver = UP;
    }
    void rflHor() {
        x = -x;
        if (hor == LEFT) hor = RIGHT;
        else hor = LEFT;
    }
    void swapXY() {
        assert(ver == UP && hor == LEFT);
        ll nx = x - n + 1;
        ll ny = y;
        swap(nx, ny);
        ny += n - 1;
        x = nx, y = ny;
        ver = DOWN;
        hor = RIGHT;
    }

    iiii tuTuple() {
        if (ver == UP && hor == LEFT) {
            return {x, y + n - 1, x - n + 1, y};
        } else if (ver == UP && hor == RIGHT) {
            return {x, y + n - 1, x + n - 1, y};
        } else if (ver == DOWN && hor == LEFT) {
            return {x, y - n + 1, x - n + 1, y};
        } else {
            return {x, y - n + 1, x + n - 1, y};
        }
    }
};


vector<L> solveLEN(ll a, ll b) {
    vector<L> ans;
    ans.push_back({a, 0, UP, LEFT});
    return ans;
}

vector<L> solveAbs(ll a, ll b) {

    if (a < n && b < n) {
        return solveLEN(a, b);
    }

    vector<L> ans;

    if (a < n) {
        ll y = 0;
        while (y <= b) {
            ans.push_back({a, y, UP, LEFT});
            y += n;
        }
        return ans;
    }
    if (b < n) {
        ll x = 0;
        while (x <= a) {
            ans.push_back({x, b, DOWN, RIGHT});
            x += n;
        }
        return ans;
    }

    ll x = 0, y = 0;
    while (y <= b || x <= a) {
        if (ans.empty()) {
            ans.push_back({x + n - 1, y, UP, LEFT});
            x += n - 1;
            y += n - 1;
            continue;
        }
        ll dx = a - x, dy = b - y;
        if (dy <= 0) {
            while (x < a) {
                ans.push_back({x + n, y, UP, LEFT});
                x += n;
            }
            break;
        }
        if (dy <= n && dx < n) {
            ans.push_back({a, y + 1, UP, LEFT});
            break;
        }
        if (dy < n && dx == n) {
            ans.push_back({a, y, UP, LEFT});
            break;
        }
        if (dy == n && dx == n) {
            ans.push_back({x + n, y, UP, LEFT});
            ans.push_back({a, b, UP, LEFT});
            break;
        }
        if (dy < n - 1) {
            ans.push_back({x + n, b - n + 1, UP, LEFT});
            x += n;
            y = b;
            continue;
        }
        if (dx < n - 1) {
            ans.push_back({a, y + 1, UP, LEFT});
            x = a;
            y += n;
            continue;
        }
        if (dx < dy) {
            ans.push_back({x + n - 1, y + 1, UP, LEFT});
            x += n - 1;
            y += n;
            continue;
        } else {
            ans.push_back({x + n, y, UP, LEFT});
            x += n;
            y += n - 1;
            continue;
        }
    }

    return ans;
}

viiii solve(ll a, ll b) {
    vector<L> ansL = solveAbs(abs(a), abs(b));
    if (a < 0) {
        for (L& l : ansL) {
            l.rflHor();
        }
    }
    if (b < 0) {
        for (L& l : ansL) {
            l.rflVer();
        }
    }
    viiii ans;
    for (L& l : ansL) {
        ans.push_back(l.tuTuple());
    }
    return ans;
}

set<ii> calSet(viiii ans) {
    set<ii> in;

    for (auto [x0, y0, x1, y1] : ans) {
        assert(abs(x0 - x1) == n - 1);
        assert(abs(y0 - y1) == n - 1);
        if (y0 > y1) {
            fore(y, y1, y0 + 1) {
                assert(!in.count({x0, y}));
                in.insert({x0, y});
            }
        } else {
            fore(y, y0, y1 + 1) {
                assert(!in.count({x0, y}));
                in.insert({x0, y});
            }
        }
        if (x0 > x1) {
            fore(x, x1, x0) {
                assert(!in.count({x, y1}));
                in.insert({x, y1});
            }
        } else {
            fore(x, x0 + 1, x1 + 1) {
                assert(!in.count({x, y1}));
                in.insert({x, y1});
            }
        }
    }

    return in;
}

void dibujar(viiii ans, ll a, ll b) {
    set<ii> in = calSet(ans);

    vector<string> res;
    fore(y, -20, 20) {
        res.push_back("");
        fore(x, -20, 20) {
            if (x == 0 && y == 0) {
                res.back() += '.';
                continue;
            }
            if (x == a && y == b) {
                if (in.count({x, y})) {
                    res.back() += 'e';
                } else {
                    res.back() += '@';
                }
                continue;
            }
            if (in.count({x, y})) {
                res.back() += ' ';
            } else {
                res.back() += '#';
            }
        }
    }

    reverse(ALL(res));
    for (string& s : res) {
        cerr << s << '\n';
    }
}

void check(viiii ans, ll a, ll b) {
    set<ii> in = calSet(ans);

    assert(in.count({0, 0}));
    assert(in.count({a, b}));

    set<ii> vis = {{0, 0}};
    vii s = {{0, 0}};
    while (!s.empty()) {
        auto [x, y] = s.back();
        s.pop_back();

        vii ves = {{x + 1, y}, {x - 1, y}, {x, y + 1}, {x, y - 1}};
        for (auto [nx, ny] : ves) {
            if (in.count({nx, ny}) && !vis.count({nx, ny})) {
                vis.insert({nx, ny});
                s.push_back({nx, ny});
            }
        }
    }

    assert(vis.count({a, b}));
}

int main(){
    ios::sync_with_stdio(0),cin.tie(0);

#ifndef TEST
    ll m;
    cin >> m;
    while (m--) {
        ll a, b;
        cin >> a >> b >> n;
        viiii ans = solve(a, b);
        cout << ans.size() << '\n';
        for (auto [x0, y0, x1, y1] : ans) {
            cout << x0 << ' ' << y0 << ' ' << x1 << ' ' << y1 << '\n';
        }
        //dibujar(ans, a, b);
    }
#else
    fore(_, 0, 50) {
        ll a = rand() % 20 - 4;
        ll b = rand() % 20 - 4;
        n = rand() % 10 + 2;
        cerr << a << ' ' << b << ' ' << n << '\n';
        viiii ans = solve(a, b);
        check(ans, a, b);
        //dibujar(ans, a, b);
    }
#endif
}