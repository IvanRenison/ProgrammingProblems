// https://codeforces.com/gym/103960/problem/F

#include <bits/stdc++.h>
#include <iostream>
#include <vector>

using namespace std;

typedef unsigned int uint;

// Function that returns a vector of string

static vector<string> parse(void) {
    uint N, C;
    cin >> N >> C;
    vector<string> words(N);
    for (uint i = 0; i < N; i++) {
        cin >> words[i];
    }

    return words;
}

// Comparator Function
static bool string_ord(string s1, string s2) {
    return s1 < s2;
}

static pair<string, uint> solve(vector<string> words) {
    uint N = words.size();
    uint C = words[0].size();

    vector<uint> indexes(N);
    for (uint i = 0; i < N; i++) {
        // Find the first '*' in the string
        for (uint j = 0; j < C; j++) {
            if (words[i][j] == '*') {
                indexes[i] = j;
                break;
            }
        }
    }

    vector<string> candidates(N * 26);
    for (uint i = 0; i < N; i++) {
        for (uint k = 0; k < 26; k++) {
            char c = 'a' + k;
            candidates[i * 26 + k] = words[i];
            candidates[i * 26 + k][indexes[i]] = c;
        }
    }

    vector<uint> compatibilities(N * 26, 0);
    for (uint k = 0; k < N * 26; k++) {
        string candidate = candidates[k];
        for (uint i = 0; i < N; i++) {
            string word = words[i];
            bool compatible = true;
            for (uint j = 0; j < C; j++) {
                if (word[j] != '*' && word[j] != candidate[j]) {
                    compatible = false;
                    break;
                }
            }
            if (compatible) {
                compatibilities[k]++;
            }
        }
    }

    uint max_compatibilities = 0;
    vector<uint> max_indexes = {};
    for (uint k = 0; k < N * 26; k++) {
        if (compatibilities[k] > max_compatibilities) {
            max_compatibilities = compatibilities[k];
            max_indexes = {k};
        } else if (compatibilities[k] == max_compatibilities) {
            max_indexes.push_back(k);
        }
    }

    vector<string> best_candidates = {};
    for (uint k : max_indexes) {
        best_candidates.push_back(candidates[k]);
    }

    sort(best_candidates.begin(), best_candidates.end(), string_ord);

    return {best_candidates[0], max_compatibilities};
}

int main(void) {
    vector<string> words = parse();
    pair<string, uint> result = solve(words);
    cout << result.first << ' ' << result.second;
    return EXIT_SUCCESS;
}
