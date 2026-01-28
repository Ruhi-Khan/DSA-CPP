class Solution {
public:
    int minCost(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();
        const long long INF = 1e18;

        vector<vector<vector<long long>>> dp(
            k + 1, vector<vector<long long>>(m, vector<long long>(n, INF))
        );

        dp[0][0][0] = 0;

        // group cells by value
        map<int, vector<pair<int,int>>, greater<int>> mp;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                mp[grid[i][j]].push_back({i, j});

        for (int t = 0; t <= k; t++) {

            // normal moves
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (i > 0)
                        dp[t][i][j] = min(dp[t][i][j],
                                          dp[t][i-1][j] + grid[i][j]);
                    if (j > 0)
                        dp[t][i][j] = min(dp[t][i][j],
                                          dp[t][i][j-1] + grid[i][j]);
                }
            }

            if (t == k) continue;

            // teleport sweep (FIXED)
            long long best = INF;
            for (auto &entry : mp) {
                auto &cells = entry.second;

                // first collect best from dp[t]
                for (auto &p : cells) {
                    best = min(best, dp[t][p.first][p.second]);
                }

                // then assign dp[t+1]
                for (auto &p : cells) {
                    dp[t+1][p.first][p.second] =
                        min(dp[t+1][p.first][p.second], best);
                }
            }
        }

        long long ans = INF;
        for (int t = 0; t <= k; t++)
            ans = min(ans, dp[t][m-1][n-1]);

        return (int)ans;
    }
};
