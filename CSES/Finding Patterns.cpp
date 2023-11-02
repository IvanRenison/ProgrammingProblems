// https://cses.fi/problemset/task/2102

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef vector<ull> vu;
typedef vector<ll> vi;
typedef pair<ull, ull> uu;
typedef pair<ll, ll> ii;
typedef vector<uu> vuu;
typedef vector<ii> vii;
typedef tuple<ull, ull, ull> uuu;
typedef tuple<ll, ll, ll> iii;
typedef vector<uuu> vuuu;
typedef vector<iii> viii;
typedef tuple<ull, ull, ull, ull> uuuu;
typedef tuple<ll, ll, ll, ll> iiii;
typedef vector<uuuu> vuuuu;
typedef vector<iiii> viiii;
typedef tuple<ull, ull, ull, ull, ull> uuuuu;
typedef tuple<ll, ll, ll, ll, ll> iiiii;
typedef vector<uuuuu> vuuuuu;
typedef vector<iiiii> viiiii;

#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(x) x.begin(), x.end()
#define DBG(x) cerr << #x << " = " << x << endl

struct SuffixAuto {
	struct state {int len,link;map<char,int> next;}; //clear next!!
	vector<state> st; // You can preallocate 2+MAXN+1
	int last;
	SuffixAuto() {
		st.push_back({0,-1,{}});
    last = 0;
	}
	void extend(char c){
		int k=st.size(),p;
		//st[k].len=st[last].len+1;
		st.push_back({st[last].len+1, 0, {}});
		for(p = last; p != -1 && !st[p].next.count(c); p = st[p].link)
			st[p].next[c]=k;
		//if(p==-1)st[k].link=0;
		if(p!=-1) {
			int q=st[p].next[c];
			if(st[p].len+1==st[q].len)st[k].link=q;
			else {
				int w=st.size();
				//st[w].len=st[p].len+1;
				//st[w].next=st[q].next;
				//st[w].link=st[q].link;
				st.push_back({st[p].len+1,st[q].link,st[q].next});
				for(; p != -1 && st[p].next[c] == q; p = st[p].link)
					st[p].next[c]=w;
				st[q].link=st[k].link=w;
			}
		}
		last=k;
	}
};
//  input: abcbcbc
//  i,link,len,next
//  0 -1 0 (a,1) (b,5) (c,7)
//  1 0 1 (b,2)
//  2 5 2 (c,3)
//  3 7 3 (b,4)
//  4 9 4 (c,6)
//  5 0 1 (c,7)
//  6 11 5 (b,8)
//  7 0 2 (b,9)
//  8 9 6 (c,10)
//  9 5 3 (c,11)
//  10 11 7
//  11 7 4 (b,8)


vector<bool> solve(string s, vector<string> ts) {
  ull k = ts.size();

  SuffixAuto sa;
  for(char c : s) {
    sa.extend(c);
  }

  vector<bool> ans(k, true);
  fore(i, 0, k) {
    ull st = 0;
    for(char c : ts[i]) {
      if(sa.st[st].next.count(c)) {
        st = sa.st[st].next[c];
      } else {
        ans[i] = false;
        break;
      }
    }
  }

  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  string s;
  ull k;
  cin >> s >> k;
  vector<string> ts(k);
  for(string& t : ts) {
    cin >> t;
  }

  auto ans = solve(s, ts);

  for(auto a : ans) {
    cout << (a ? "YES" : "NO") << '\n';
  }

  return EXIT_SUCCESS;
}
