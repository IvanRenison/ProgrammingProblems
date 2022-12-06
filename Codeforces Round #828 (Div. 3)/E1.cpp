// https://codeforces.com/contest/1744/problem/E1

#include <iostream>
// attemps
using namespace std;

pair<int, int> solve1(int a, int b, int c, int d) {
    for (int x = a + 1; x <= c; x++) {
        for (int y = b + 1; y <= d; y++) {
            int rem = (x * y) % (a * b);
            if (rem == 0) {
                return {x, y};
            }
            else if (rem / x > 0) {
                y += rem / x - 1;
            }
        }
    }
    return {-1, -1};
}

int main(void) {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        pair<int, int> res = solve1(a, b, c, d);
        cout << res.first << " " << res.second << "\n";
    }

    return EXIT_SUCCESS;
}
