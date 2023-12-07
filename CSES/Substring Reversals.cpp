//

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;
typedef tuple<ull, ull, ull> uuu;
typedef vector<uuu> vuuu;
typedef tuple<ull, ull, ull, ull> uuuu;
typedef vector<uuuu> vuuuu;
typedef tuple<ull, ull, ull, ull, ull> uuuuu;
typedef vector<uuuuu> vuuuuu;
typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;
typedef tuple<ll, ll, ll> iii;
typedef vector<iii> viii;
typedef tuple<ll, ll, ll, ll> iiii;
typedef vector<iiii> viiii;
typedef tuple<ll, ll, ll, ll, ll> iiiii;
typedef vector<iiiii> viiiii;
typedef long double ld;
typedef vector<ld> vd;
typedef pair<ld, ld> dd;
typedef vector<dd> vdd;
typedef tuple<ld, ld, ld> ddd;
typedef vector<ddd> vddd;
typedef tuple<ld, ld, ld, ld> dddd;
typedef vector<dddd> vdddd;
typedef vector<bool> vb;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()
#define DBG(x) cerr << #x << " = " << x << endl

// Like treap but for an array (the elements are ordered by list position)
typedef struct item* pitem;
struct item {
  int pr, cnt;
  char val;
  bool rev;
  pitem l, r;
  item(char val) : pr(rand()), cnt(1), val(val), rev(false), l(NULL), r(NULL) {}
};
void push(pitem it) {
  if (it) {
    if (it->rev) {
      swap(it->l, it->r);
      if (it->l)
        it->l->rev ^= true;
      if (it->r)
        it->r->rev ^= true;
      it->rev = false;
    }
  }
}
int cnt(pitem t) {
  return t ? t->cnt : 0;
}
void upd_cnt(pitem t) {
  if (t) {
    t->cnt = cnt(t->l) + cnt(t->r) + 1;
  }
}
pitem merge(pitem l, pitem r) {
  pitem t;
  push(l);
  push(r);
  if (!l || !r)
    t = l ? l : r;
  else if (l->pr > r->pr)
    l->r = merge(l->r, r), t = l;
  else
    r->l = merge(l, r->l), t = r;
  upd_cnt(t);
  return t;
}
pair<pitem, pitem> split(pitem t, int sz) { // sz:desired size of l
  pitem l, r;
  if (!t) {
    l = r = 0;
    return {l, r};
  }
  push(t);
  if (sz <= cnt(t->l)) {
    auto lr = split(t->l, sz);
    l = lr.first, t->l = lr.second;
    r = t;
  } else {
    auto lr = split(t->r, sz - 1 - cnt(t->l));
    t->r = lr.first, r = lr.second;
    l = t;
  }
  upd_cnt(t);
  return {l, r};
}
// use merge and split for range updates and queries

string solve(const string& s, const vuu& querys) {
  ull n = s.size();

  pitem root = NULL;
  for (char c : s) {
    root = merge(root, new item(c));
  }

  for (auto [a, b] : querys) {
    auto [l, r_] = split(root, a);
    auto [m, r] = split(r_, b - a + 1);
    m->rev ^= true;
    root = merge(l, merge(m, r));
  }

  string ans;
  fore(i, 0, n) {
    auto [h, t] = split(root, 1);
    ans += h->val;
    root = t;
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull n, m;
  cin >> n >> m;
  string s;
  cin >> s;
  vuu querys(m);
  for (auto& [a, b] : querys) {
    cin >> a >> b;
    a--, b--;
  }

  auto ans = solve(s, querys);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
