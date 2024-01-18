// https://codeforces.com/gym/101889

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
typedef vector<double> vd;

typedef double tc;
struct Line{tc m,h;};
struct CHT { // for minimum (for maximum just change the sign of lines)
	vector<Line> c;
	int pos=0;
  CHT() {}
  CHT(vector<pair<double, double>>& lines) {
    sort(lines.rbegin(), lines.rend());
    for(auto [m, h] : lines) {
      add(m, h);
    }
  }
	tc in(Line a, Line b){
		tc x=b.h-a.h,y=a.m-b.m;
		//return x/y+(x%y?!((x>0)^(y>0)):0); // ==ceil(x/y)
    return ceil(x/y);
	}
	void add(tc m, tc h){ // m's should be non increasing
		Line l=(Line){m,h};
		if(c.size()&&m==c.back().m){
			l.h=min(h,c.back().h);c.pop_back();if(pos)pos--;
		}
		while(c.size()>1&&in(c.back(),l)<=in(c[c.size()-2],c.back())){
			c.pop_back();if(pos)pos--;
		}
		c.push_back(l);
	}
	inline bool fbin(tc x, int m){return in(c[m],c[m+1])>x;}
	tc eval(tc x){
		// O(log n) query:
		int s=0,e=c.size();
		while(e-s>1){int m=(s+e)/2;
			if(fbin(x,m-1))e=m;
			else s=m;
		}
		return c[s].m*x+c[s].h;
		// O(1) query (for ordered x's):
		while(pos>0&&fbin(x,pos-1))pos--;
		while(pos<c.size()-1&&!fbin(x,pos))pos++;
		return c[pos].m*x+c[pos].h;
	}
};

pair<double, double> getLine(ii p0, ii p1) {
  double x0 = (double)p0.first, y0 = (double)p0.second;
  double x1 = (double)p1.first, y1 = (double)p1.second;
  assert(x0 != x1);
  /*
    a x0 + b = y0
    a x1 + b = y1

    a x0 + y1 - a x1 = y0
    a = (y0 - y1)/(x0 - x1)
    b = y1 - x1 (y0 - y1)/(x0 - x1)
  */

  double a = (y0 - y1)/(x0 - x1);
  double b = y1 - x1 * a;

  return {a, b};
}

tuple<CHT, CHT, vii, vii> buildCHTs(const vii& pol) {
  ull K = pol.size();

  vector<pair<double, double>> up_lines, down_lines;
  vii up_points, down_points;

  ull i = 1;
  for(; pol[i].first != pol[i+1].first; i++) {
    up_points.push_back(pol[i]);
    auto [m, h] = getLine(pol[i], pol[i+1]);
    up_lines.push_back({m, h});
  }
  up_points.push_back(pol[i]);

  i++;

  for(; i < K; i++) {
    auto [xi, yi] = pol[i];
    auto [xn, yn] = pol[(i + 1) % K];
    auto [m, h] = getLine({xi, -yi}, {xn, -yn});
    down_lines.push_back({m, h});
    down_points.push_back({xi, yi});
  }
  down_points.push_back(pol[0]);

  CHT up(up_lines), down(down_lines);

  return {up, down, up_points, down_points};
}


double get1Cost(CHT& up, CHT& down, vii& up_points, vii& down_points) {
  double ans = 0.0;

  for(auto [x, y] : up_points) {
    auto y1 = down.eval((double)x);
    double this_ans = (double)y + y1;
    ans = max(ans, this_ans);
  }

  for(auto [x, y] : down_points) {
    auto y1 = up.eval((double)x);
    double this_ans = y1 + (double)(-y);
    ans = max(ans, this_ans);
  }

  return ans;
}


vector<vd> getCosts(const vector<vii>& pols) {
  ull N = pols.size();

  vector<CHT> ups(N), downs(N);
  vector<vii> up_points(N), down_points(N);

  fore(i, 0, N) {
    auto [up, down, up_point, down_point] = buildCHTs(pols[i]);
    ups[i] = up, downs[i] = down;
    up_points[i] = up_point, down_points[i] = down_point;
  }

  vector<vd> adj(N, vd(N, 0.0));

  fore(i, 0, N) {
    fore(j, 0, N) if (i != j) {
      adj[i][j] = get1Cost(ups[i], downs[j], up_points[i], down_points[j]);
    }
  }

  return adj;
}

pair<ll, ll> minMaxY(const vii& pol) {
  ll m = 0, M = 0;

  for(auto [_, y] : pol) {
    m = min(m, y), M = max(M, y);
  }

  return {-m, M};
}

pair<vd, vd> getExtras(const vector<vii>& pols) {
  ull N = pols.size();

  vd min_extras(N), max_extras(N);

  fore(i, 0, N) {
    auto [m, M] = minMaxY(pols[i]);
    min_extras[i] = (double)m, max_extras[i] = (double)M;
  }

  return {min_extras, max_extras};
}

double minHamWackCost(const vector<vd>& adj, const vd& down_extras, const vd& up_extras) {
  ull N = adj.size();

  vector<vd> dp(1 << N, vd(N, 0.0));
  // dp[x][i] = min cost of passing by all bits of x and the going to i

  fore(i, 0, N) {
    dp[0][i] = down_extras[i];
  }

  fore(x, 1, 1 << N) {
    fore(i, 0, N) if ((x & (1 << i)) == 0) {
      double ans = 1e30;

      fore(j, 0, N) if (x & (1 << j)) {
        double this_ans = dp[x ^ (1 << j)][j] + adj[j][i];
        ans = min(ans, this_ans);
      }

      dp[x][i] = ans;
    }
  }

  double ans = 1e30;

  fore(i, 0, N) {
    double this_ans = dp[((1 << N) - 1) ^ (1 << i)][i] + up_extras[i];
    ans = min(ans, this_ans);
  }

  return ans;
}


double solve(const vector<vii>& pols) {
  vector<vd> adj = getCosts(pols);
  auto [down_extras, up_extras] = getExtras(pols);
  double ans = minHamWackCost(adj, down_extras, up_extras);
  return ans;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL), cout.tie(NULL);

  ull N;
  cin >> N;
  vector<vii> pols(N);
  for(vii& pol : pols) {
    ull K;
    cin >> K;
    pol = vii(K);
    for(auto& [x, y] : pol) {
      cin >> y >> x;
    }
  }

  auto ans = solve(pols);
  cout << setprecision(3) << fixed;
  cout << ans << '\n';

  return EXIT_SUCCESS;
}
