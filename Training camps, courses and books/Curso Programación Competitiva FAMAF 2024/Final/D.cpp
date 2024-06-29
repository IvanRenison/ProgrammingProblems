// https://codeforces.com/group/gmV7IkT2pN/contest/531946/problem/D

#include <bits/stdc++.h>
using namespace std;
typedef unsigned int uint;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  uint n, m;
  cin >> n >> m;

  map<string, string> names;
  while (n--) {
    string name, ip;
    cin >> name >> ip;
    names[ip] = name;
  }

  while (m--) {
    string command, ip;
    cin >> command >> ip;
    assert(ip.back() == ';');
    ip.pop_back();
    string& name = names[ip];
    cout << command << ' ' << ip << "; #" << name << '\n';
  }
}
