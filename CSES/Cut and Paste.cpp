// https://cses.fi/problemset/task/2072

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef vector<ull> vu;
typedef pair<ull, ull> uu;
typedef vector<uu> vuu;


#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)


// Like treap but for an array (the elements are ordered by list position)
// example that supports range reverse and addition updates, and range sum query
// (commented parts are specific to this  problem)
typedef struct item *pitem;
struct item {
  int pr,cnt;
  char val;
//	int sum; // (paramters for range query)
//	bool rev;int add; // (parameters for lazy prop)
  pitem l,r;
  item(char val): pr(rand()),cnt(1),val(val),l(0),r(0)/*,sum(val),rev(0),add(0)*/ {}
};
void push(pitem it){
  if(it){
    /*if(it->rev){
      swap(it->l,it->r);
      if(it->l)it->l->rev^=true;
      if(it->r)it->r->rev^=true;
      it->rev=false;
    }
    it->val+=it->add;it->sum+=it->cnt*it->add;
    if(it->l)it->l->add+=it->add;
    if(it->r)it->r->add+=it->add;
    it->add=0;*/
  }
}
int cnt(pitem t){return t?t->cnt:0;}
// int sum(pitem t){return t?push(t),t->sum:0;}
void upd_cnt(pitem t){
  if(t){
    t->cnt=cnt(t->l)+cnt(t->r)+1;
    // t->sum=t->val+sum(t->l)+sum(t->r);
  }
}
pitem merge(pitem l, pitem r){
  pitem t;
  push(l);push(r);
  if(!l||!r)t=l?l:r;
  else if(l->pr>r->pr)l->r=merge(l->r,r),t=l;
  else r->l=merge(l,r->l),t=r;
  upd_cnt(t);
  return t;
}
pair<pitem, pitem> split(pitem t, int sz){ // sz:desired size of l
  pitem l, r;
  if(!t){l=r=0;return {l, r};}
  push(t);
  if(sz<=cnt(t->l)) {
    auto lr = split(t->l,sz);
    l = lr.first, t->l = lr.second;
    r=t;
  }
  else {
    auto lr = split(t->r,sz-1-cnt(t->l));
    t->r = lr.first, r = lr.second;
    l=t;
  }
  upd_cnt(t);
  return {l, r};
}
// use merge and split for range updates and queries


string solve(string s, vuu ops) {
  ull n = s.size();

  pitem t = new item(s[0]);
  fore(i, 1, n) {
    t = merge(t, new item(s[i]));
  }

  for (auto [a, b] : ops) {
    auto [t1, t2] = split(t, a);
    auto [t3, t4] = split(t2, b - a + 1);
    t = merge(t1, merge(t4, t3));
  }

  string ans(n, ' ');
  fore(i, 0, n) {
    auto [t1, t2] = split(t, 1);
    ans[i] = t1->val;
    t = t2;
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
  vuu ops(m);
  for(auto& [a, b] : ops) {
    cin >> a >> b;
    a--, b--;
  }

  auto ans = solve(s, ops);
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
