#include <cmath>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

long long alfabeticamente(const vector<long long>& costs, const vector<string>& strings) {
    int n = strings.size();
    long long INF = numeric_limits<long long>::max() / 2;

    vector<string> rStrings = strings;
    for (size_t i = 0; i < rStrings.size(); ++i) {
        reverse(rStrings[i].begin(), rStrings[i].end());
    }

    long long prevNotInvert = 0;
    long long prevInvert = costs[0];

    for (int i = 1; i < n; ++i) {
        long long currNotInvert = INF;
        long long currInvert = INF;

        if (prevNotInvert != INF && strings[i - 1] <= strings[i]) {
            currNotInvert = min(currNotInvert, prevNotInvert);
        };

        if (prevInvert != INF && rStrings[i - 1] <= strings[i]) {
            currNotInvert = min(currNotInvert, prevInvert);
        };

        if (prevNotInvert != INF && strings[i - 1] <= rStrings[i]) {
            currInvert = min(currInvert, prevNotInvert + costs[i]);
        };
        if (prevInvert != INF && rStrings[i - 1] <= rStrings[i]) {
            currInvert = min(currInvert, prevInvert + costs[i]);
        }

        prevNotInvert = currNotInvert;
        prevInvert = currInvert;
    }

    long long ans = min(prevNotInvert, prevInvert);
    if (ans >= INF) {
        return -1;
    } else {
        return ans;
    }
}

int main() {
    int n;
    if (!(cin >> n)) return 0;

    vector<long long> costs(n);
    for (int i = 0; i < n; ++i) cin >> costs[i];

    vector<string> strings(n);
    for (int i = 0; i < n; ++i) cin >> strings[i];

    long long ans = alfabeticamente(costs, strings);
    cout << ans << '\n';
    return 0;
}

