class Solution {
public:
    int minCost(int n, vector<vector<int>>& edges) {

        vector<vector<pair<int, int>>> graph(n);

        // Build graph
        for (auto &e : edges) {
            int u = e[0], v = e[1], w = e[2];

            // Normal edge
            graph[u].push_back({v, w});

            // Reversed edge using switch (cost = 2 * w)
            graph[v].push_back({u, 2 * w});
        }

        // Dijkstra
        vector<long long> dist(n, LLONG_MAX);
        priority_queue<pair<long long, int>,
                       vector<pair<long long, int>>,
                       greater<pair<long long, int>>> pq;

        dist[0] = 0;
        pq.push({0, 0});

        while (!pq.empty()) {
            auto top = pq.top();
            pq.pop();

            long long cost = top.first;
            int node = top.second;

            if (cost > dist[node]) continue;

            for (auto &edge : graph[node]) {
                int nextNode = edge.first;
                int edgeCost = edge.second;

                if (dist[nextNode] > cost + edgeCost) {
                    dist[nextNode] = cost + edgeCost;
                    pq.push({dist[nextNode], nextNode});
                }
            }
        }

        return dist[n - 1] == LLONG_MAX ? -1 : (int)dist[n - 1];
    }
};
