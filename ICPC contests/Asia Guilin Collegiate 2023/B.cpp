// https://codeforces.com/gym/104768/problem/B
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define fore(i,a,b) for(ll i=a,aei=b;i<aei;++i)
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((ll)x.size())
using namespace std;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll,ll> ii;



vi prosses(const vi& As, const vi& ans) {
    multiset<ll> s(ALL(As));

    for (ll a : ans) {
        auto it = s.lower_bound(a);
        assert(it != s.end());
        if (*it != a) {
            return {};
        }
        s.erase(it);
        s.insert(a + 1);

        auto it2 = s.begin();
        s.erase(it2);
    }

    return vi(ALL(s));
}

optional<vi> force(const vi& As, const vi& Bs) {
    ll n = As.size(), m = Bs.size();

    optional<vi> ans;

    function<void(multiset<ll>, vi)> rec = [&](multiset<ll> as, vi r) {
        if (as == multiset<ll>(ALL(Bs))) {
            ans = r;
        }

        if (as.size() <= Bs.size()) return;

        for (ll a : as) {
            multiset<ll> asn = as;
            vi rn = r;

            auto it = asn.lower_bound(a);
            asn.erase(it);
            rn.push_back(a);
            asn.insert(a+1);

            auto it2 = asn.begin();
            asn.erase(it2);

            rec(asn, rn);
        }
    };

    rec(multiset<ll>(ALL(As)), vi{});

    if (ans.has_value()) {
        vi As_ = prosses(As, *ans);
        assert(multiset<ll>(ALL(As_)) == multiset<ll>(ALL(Bs)));
    }

    return ans;
}

optional<vi> solve(vi& As, vi& Bs) {
    sort(ALL(As));
    sort(ALL(Bs));
    reverse(ALL(As));
    reverse(ALL(Bs));

    ll n = As.size(), m = Bs.size();

    if (n < m) {
        return {};
    }

    if (n == m) {
        if (As == Bs) {
            return {vi(0)};
        } else {
            return {};
        }
    }

    vi ans;

    ll diff = 0;
    multiset<ll> diff_set;
    fore(i, 0, m) {
        ll A = As[i], B = Bs[i];
        if (A > B) {
            return {};
        }
        diff += B - A;
        diff_set.insert(A);
    }

    if (m + diff > n) {
        return {};
    }

    multiset<ll> As_(ALL(As));

    ll now = n - (m + diff);

    for (ll i = 0; i < now; i++) {
        auto it = As_.begin();
        ll a = *it;
        auto it_diff = diff_set.begin();
        ll a_diff = *it_diff;
        As_.erase(it);
        ans.push_back(a);
        if (a + 1 <= a_diff) {
            As_.insert(a + 1);
        } else {
            diff_set.erase(it_diff);
            diff_set.insert(a + 1);
            As_.insert(a + 1);
            now++;
            if (now > n) {
                return {};
            }
        }
        As_.erase(As_.begin());
    }


    vi As__(ALL(As_));
    reverse(ALL(As__));
    fore(i, 0, m) {
        ll A = As__[i], B = Bs[i];
        fore(a, A, B) {
            ans.push_back(a);
        }
    }

    vi Bs_ = prosses(As, ans);
    sort(ALL(Bs_));
    reverse(ALL(Bs_));

    if (Bs_ != Bs) {
        return {};
    }

    return ans;
}

int main(){
    ios::sync_with_stdio(0),cin.tie(0);


    ll t;
    cin >> t;
    while (t--) {
        ll n, m;
        cin >> n >> m;
        vi As(n), Bs(m);
        for (ll& a : As)  {
            cin >> a;
        }
        for (ll& B : Bs) {
            cin >> B;
        }

        auto ans = solve(As, Bs);

        if (!ans.has_value()) {
            cout << "-1\n";
        } else {
            cout << ans->size() << '\n';
            for (ll a : *ans) {
                cout << a << ' ';
            }
            cout << '\n';
        }
    }


/*     fore(_, 0, 10000) {
        ll n = rand() % 5 + 1, m = rand() % 5 + 1;
        vi As(n), Bs(m);
        for (ll& A : As) {
            A = rand() % 5 + 1;
        }
        for (ll& B : Bs) {
            B = rand() % 5 + 1;
        }

        auto ansf = force(As, Bs);
        auto ans = solve(As, Bs);

        if (ansf.has_value() != ans.has_value()) {
            cerr << "ERROR\n";
            cerr << n << ' ' << m << '\n';
            for (ll A : As) {
                cerr << A << ' ';
            }
            cerr << '\n';
            for (ll B : Bs) {
                cerr << B << ' ';
            }
            cerr << '\n';
            cerr << "ansf.has_value() " << ansf.has_value() << '\n';
            return 1;
        }
        if (ans.has_value()) {
            vi As_ = prosses(As, *ans);
            assert(multiset<ll>(ALL(As_)) == multiset<ll>(ALL(Bs)));
        }
    } */


}