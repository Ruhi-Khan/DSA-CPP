#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxSideLength(vector<vector<int>>& a, int th) {
        int m = a.size(), n = a[0].size();
        int ps[301][301] = {0};

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                ps[i+1][j+1] = a[i][j] + ps[i][j+1] + ps[i+1][j] - ps[i][j];
            }
        }

        int ans = 0;

        for (int len = 1; len <= min(m, n); len++) {
            bool ok = false;

            for (int i = 0; i + len <= m; i++) {
                for (int j = 0; j + len <= n; j++) {
                    int s = ps[i+len][j+len] - ps[i][j+len]
                          - ps[i+len][j] + ps[i][j];
                    if (s <= th) {
                        ok = true;
                        break;
                    }
                }
                if (ok) break;
            }

            if (ok) ans = len;
            else break;
        }

        return ans;
    }
};
