// https://codeforces.com/gym/103960/problem/F

#include <bits/stdc++.h>
#include <iostream>
#include <vector>

using namespace std;

typedef unsigned int uint;

// Function that returns a vector of string

vector<string> parse(void)
{
    uint N, C;
    cin >> N >> C;
    vector<string> words(N);
    for (uint i = 0; i < N; i++)
    {
        cin >> words[i];
    }

    return words;
}

// Comparator Function
bool string_ord(string s1, string s2)
{
    return s1 < s2;
}

pair<string, uint> solve(vector<string> words)
{
    uint N = words.size();
    uint C = words[0].size();
    vector<uint> indexes(N);
    for (uint j = 0; j < N; j++)
    {
        // Find the first '*' in the string
        for (uint i = 0; i < C; i++)
        {
            if (words[j][i] == '*')
            {
                indexes[j] = i;
                break;
            }
        }
    }

    vector<string> valid_words(N * 26);
    for (uint j = 0; j < N; j++)
    {
        for (uint i = 0; i < 26; i++)
        {
            valid_words[j * 26 + i] = words[j];
            valid_words[j * 26 + i][indexes[j]] = 'a' + i;
        }
    }

    sort(valid_words.begin(), valid_words.end(), string_ord);

    uint max_compatibilities = 0;
    uint max_compatibilities_index = 0;
    for (uint k = 0; k < N * 26; k++)
    {
        uint compatibilities = 0;
        for (uint j = 0; j < N; j++)
        {
            bool compatible = true;
            for (uint i = 0; i < C; i++)
            {
                if (i != indexes[j] && valid_words[k][i] != words[j][i])
                {
                    compatible = false;
                    break;
                }
            }
            if (compatible)
            {
                compatibilities++;
            }
        }
        if (compatibilities > max_compatibilities)
        {
            max_compatibilities = compatibilities;
            max_compatibilities_index = k;
        }
    }

    return make_pair(valid_words[max_compatibilities_index], max_compatibilities);
}

int main(void)
{
    vector<string> words = parse();
    pair<string, uint> result = solve(words);
    cout << result.first << ' ' << result.second;
    return EXIT_SUCCESS;
}
