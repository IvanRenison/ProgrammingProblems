// https://codeforces.com/contest/1744/problem/E1

#include <iostream>

using namespace std;

pair<int, int> solve1(int a, int b, int c, int d) {
    int ab = a * b;
    for (int x = a + 1; x <= c; x++) {
        for (int y = b + 1; y <= d;) {
            int rem = (x * y) % ab;
            if (rem == 0) {
                return {x, y};
            }
            int y_sum = (ab - rem) / x;
            y += y_sum > 0 ? y_sum : 1;
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
