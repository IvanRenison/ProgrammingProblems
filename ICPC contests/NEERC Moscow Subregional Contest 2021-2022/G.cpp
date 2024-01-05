// https://codeforces.com/gym/104848/problem/G
#include <bits/stdtr1c++.h>
#define fst first
#define snd second
#define pb push_back
#define SZ(x) ((ll)x.size())
#define ALL(x) x.begin(),x.end()
#define fore(i,a,b) for(int i=a,gmat=b;i<gmat;i++)
#define mset(a,v) memset((a),(v),sizeof(a))
#define FIN ios::sync_with_stdio(0);cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;

int main(){FIN;
  map<ll,string> names;
  queue<pair<ll,string>> winners, losers;
  fore(i,0,16){
    string s, matches;cin>>s>>matches;
    names[i]=s;
    reverse(ALL(matches));
    if(matches.back()=='0'){
      matches.pop_back();
      losers.push({i,matches});
    } else {
      matches.pop_back();
      winners.push({i,matches});
    }
  }
  vector<vector<ll>> posis;
  while(SZ(winners)>1 && SZ(losers)>1){
    vector<ll> aux;
    queue<pair<ll,string>> winners_aux,losers_aux,losers_aux2;
    while(SZ(losers)){
      ll cual = losers.front().fst;string partidos = losers.front().snd;
      losers.pop();
      assert(SZ(partidos)>=1);
      if(partidos.back()=='0'){
        aux.pb(cual);
      } else {
        partidos.pop_back();
        losers_aux.push({cual,partidos});
      }
    }
    posis.pb(aux);
    aux.clear();losers = losers_aux;
    while(SZ(winners)){
      ll cual = winners.front().fst;string partidos = winners.front().snd;
      winners.pop();
      assert(SZ(partidos)>=1);
      if(partidos.back()=='0'){
        partidos.pop_back();
        losers.push({cual,partidos});
      } else {
        partidos.pop_back();
        winners_aux.push({cual,partidos});
      }
    }
    winners = winners_aux;
    while(SZ(losers)){
      ll cual = losers.front().fst;string partidos = losers.front().snd;
      losers.pop();
      // cout << names[cual] << " ";
      assert(SZ(partidos)>=1);
      if(partidos.back()=='0'){
        aux.pb(cual);
      } else {
        partidos.pop_back();
        losers_aux2.push({cual,partidos});
      }
    }
    // cout << "\n";
    losers=losers_aux2;
    posis.pb(aux);
  }
  ll cual_loser = losers.front().fst;string partidos_loser = losers.front().snd;
  ll cual_winner = winners.front().fst;
  if(partidos_loser.back()=='0'){
    posis.pb({cual_loser});
    posis.pb({cual_winner});
  } else {
    posis.pb({cual_winner});
    posis.pb({cual_loser});
  }
  reverse(ALL(posis));
  vector<vector<string>> posis_final(SZ(posis));
  fore(i,0,SZ(posis)){
    fore(j,0,SZ(posis[i])){
      posis_final[i].pb(names[posis[i][j]]);
    }
    sort(ALL(posis_final[i]));
  }
  fore(i,0,SZ(posis)){
    if(i<4){
      cout << i+1 << " " << posis_final[i][0] << "\n";
    } else if(i==4) {
      fore(j,0,2){
        cout << "5-6 " << posis_final[i][j] << "\n";
      }
    } else if(i==5) {
      fore(j,0,2){
        cout << "7-8 " << posis_final[i][j] << "\n";
      }
    } else if(i==6){
      fore(j,0,4){
        cout << "9-12 " << posis_final[i][j] << "\n";
      }
    } else {
      fore(j,0,4){
        cout << "13-16 " << posis_final[i][j] << "\n";
      }
    }
  }
  return 0;
}