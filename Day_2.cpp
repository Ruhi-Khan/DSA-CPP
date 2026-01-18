#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int largestMagicSquare(vector<vector<int>>& g) {
        int m = g.size(), n = g[0].size();
        int ans = 1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 2; i + k <= m && j + k <= n; k++) {

                    int sum = 0;
                    for (int c = j; c < j + k; c++)
                        sum += g[i][c];

                    bool ok = true;

                    for (int r = i; r < i + k && ok; r++) {
                        int s = 0;
                        for (int c = j; c < j + k; c++)
                            s += g[r][c];
                        if (s != sum) ok = false;
                    }

                    for (int c = j; c < j + k && ok; c++) {
                        int s = 0;
                        for (int r = i; r < i + k; r++)
                            s += g[r][c];
                        if (s != sum) ok = false;
                    }

                    int d1 = 0, d2 = 0;
                    for (int t = 0; t < k; t++) {
                        d1 += g[i + t][j + t];
                        d2 += g[i + t][j + k - t - 1];
                    }

                    if (d1 != sum || d2 != sum) ok = false;

                    if (ok) ans = max(ans, k);
                }
            }
        }
        return ans;
    }
};
