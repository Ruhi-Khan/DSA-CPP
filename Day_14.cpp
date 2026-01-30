class Solution {
public:
    static constexpr long long INF = 1e18;

    struct Trie {
        int nxt[26];
        int id;
        Trie() {
            memset(nxt, -1, sizeof(nxt));
            id = -1;
        }
    };

    long long minimumCost(
        string source, string target,
        vector<string>& original,
        vector<string>& changed,
        vector<int>& cost
    ) {
        int n = source.size();

        // ---- Map strings to ids ----
        unordered_map<string,int> mp;
        vector<string> all;

        auto getId = [&](const string& s) {
            if (!mp.count(s)) {
                mp[s] = all.size();
                all.push_back(s);
            }
            return mp[s];
        };

        for (int i = 0; i < original.size(); i++) {
            getId(original[i]);
            getId(changed[i]);
        }

        int m = all.size();
        vector<vector<long long>> dist(m, vector<long long>(m, INF));

        for (int i = 0; i < m; i++) dist[i][i] = 0;

        for (int i = 0; i < original.size(); i++) {
            int u = getId(original[i]);
            int v = getId(changed[i]);
            dist[u][v] = min(dist[u][v], (long long)cost[i]);
        }

        // ---- Floyd–Warshall ----
        for (int k = 0; k < m; k++)
            for (int i = 0; i < m; i++)
                for (int j = 0; j < m; j++)
                    if (dist[i][k] < INF && dist[k][j] < INF)
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

        // ---- Build Trie for original strings ----
        vector<Trie> trie(1);

        auto insert = [&](const string& s) {
            int node = 0;
            for (char c : s) {
                int x = c - 'a';
                if (trie[node].nxt[x] == -1) {
                    trie[node].nxt[x] = trie.size();
                    trie.emplace_back();
                }
                node = trie[node].nxt[x];
            }
            trie[node].id = mp[s];
        };

        for (auto &s : original) insert(s);

        // ---- DP ----
        vector<long long> dp(n + 1, INF);
        dp[n] = 0;

        for (int i = n - 1; i >= 0; i--) {
            // normal move
            if (source[i] == target[i]) {
                dp[i] = dp[i + 1];
            }

            // trie-based substring match
            int node = 0;
            for (int j = i; j < n; j++) {
                int c = source[j] - 'a';
                if (trie[node].nxt[c] == -1) break;
                node = trie[node].nxt[c];

                if (trie[node].id != -1) {
                    int len = j - i + 1;
                    string tgt = target.substr(i, len);
                    if (mp.count(tgt)) {
                        long long cst = dist[trie[node].id][mp[tgt]];
                        if (cst < INF) {
                            dp[i] = min(dp[i], cst + dp[j + 1]);
                        }
                    }
                }
            }
        }

        return dp[0] >= INF ? -1 : dp[0];
    }
};
