// https://codeforces.com/gym/102428

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
#define fore(i, a, b) for (ull i = a, gmat = b; i < gmat; i++)
#define all(a) begin(a), end(a)

struct SufixAuto {
	struct state {int len,link;map<char,int> next;}; //clear next!!
	vector<state> st;
	int sz,last;
	SufixAuto(ull n) : st(2*n + 1) {
		last=st[0].len=0;sz=1;
		st[0].link=-1;
	}
	void sa_extend(char c){
		int k=sz++,p;
		st[k].len=st[last].len+1;
		for(p=last;p!=-1&&!st[p].next.count(c);p=st[p].link)st[p].next[c]=k;
		if(p==-1)st[k].link=0;
		else {
			int q=st[p].next[c];
			if(st[p].len+1==st[q].len)st[k].link=q;
			else {
				int w=sz++;
				st[w].len=st[p].len+1;
				st[w].next=st[q].next;st[w].link=st[q].link;
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

vi solve(const string& C, const vector<string>& ss) {
  ull N = ss.size();

	SufixAuto sa(C.size());
	for(char c : C) {
		sa.sa_extend(c);
	}

	vi ans(N);
	fore(i, 0, N) {
		string s = ss[i];
		ll count = 1;

		ull st = 0;
		for(char c : s) {
			if (sa.st[st].next.count(c)) {
				st = sa.st[st].next[c];
			} else if (sa.st[0].next.count(c)){
				st = sa.st[0].next[c];
				count++;
			} else {
				count = -1;
				break;
			}
		}

		ans[i] = count;
	}

	return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  string C;
  cin >> C;

  ull N;
  cin >> N;
  vector<string> ss(N);
  for(string& s : ss) {
    cin >> s;
  }

  auto ans = solve(C, ss);
  for(ll a : ans) {
    cout << a << '\n';
  }

  return EXIT_SUCCESS;
}
