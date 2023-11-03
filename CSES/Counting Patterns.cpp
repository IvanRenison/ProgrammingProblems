// https://cses.fi/problemset/task/2103

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
#define sz(v) (v.size())

struct SuffixAuto {
	struct state {int len,link;map<char,int> next;};
	vector<state> st; // You can preallocate 2*MAXN+1
	int last;
	SuffixAuto() {
		st.push_back({0,-1,{}});
		last=0;
	}
	void extend(char c){
		int k=st.size(),p;
		st.push_back({st[last].len+1,0,{}});
		for(p=last;p!=-1&&!st[p].next.count(c);p=st[p].link)st[p].next[c]=k;
		if(p!=-1){
			int q=st[p].next[c];
			if(st[p].len+1==st[q].len)st[k].link=q;
			else {
				int w=st.size();
				st.push_back({st[p].len+1,st[q].link,st[q].next});
				for(;p!=-1&&st[p].next[c]==q;p=st[p].link)st[p].next[c]=w;
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

vector<vi> getGraph(const SuffixAuto& sa) {
  ull n = sa.st.size();

  vector<vi> adj(n);

  fore(u, 0, n) {
    for(auto [_, v] : sa.st[u].next) {
      adj[u].push_back(v);
    }
  }

  return adj;
}

vi topoSort(const vector<vi>& gr) {
	vi indeg(sz(gr)), ret;
	for (auto& li : gr) for (int x : li) indeg[x]++;
	queue<int> q; // use priority_queue for lexic. largest ans.
	fore(i,0,sz(gr)) if (indeg[i] == 0) q.push(i);
	while (!q.empty()) {
		int i = q.front(); // top() for priority queue
		ret.push_back(i);
		q.pop();
		for (int x : gr[i])
			if (--indeg[x] == 0) q.push(x);
	}
	return ret;
}

vu solve(string s, vector<string> ts) {
  ull k = ts.size();

  SuffixAuto sa;
  for(char c : s) {
    sa.extend(c);
  }

  vector<vi> g = getGraph(sa);
  ull n = g.size();

  vi ord = topoSort(g);
  reverse(all(ord));

  vu dp(n);
  for(int st = sa.last; st != -1; st = sa.st[st].link) {
    dp[st] = 1;
  }


  for(ull i : ord) {
    for(ull j : g[i]) {
      dp[i] += dp[j];
    }
  }

  vu ans(k);

  fore(i, 0, k) {
    ull st = 0;
    for(char c : ts[i]) {
      if(sa.st[st].next.count(c)) {
        st = sa.st[st].next[c];
      } else {
        st = -1;
        break;
      }
    }

    if (st != -1) {
      ans[i] = dp[st];
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
    cout << a << '\n';
  }

  return EXIT_SUCCESS;
}
