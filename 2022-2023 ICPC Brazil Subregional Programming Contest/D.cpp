// https://codeforces.com/gym/103960/problem/D

#include <iostream>

// using namespace std;

unsigned int solve(unsigned int N, unsigned int x)
{
    unsigned int res = 0;
    while (x != 1 << (N - 1))
    {
        if (x < 1 << (N - 1))
        {
            res++;
            x = x * 2;
        }
        else
        {
            x = (1 << N) - x;
        }
    }
    return res;
}

int main(void)
{
    // Parse N, x, y from stdin
    unsigned int N, x;
    std::cin >> N >> x;

    unsigned int res = solve(N, x);

    std::cout << res;

    return EXIT_SUCCESS;
}
