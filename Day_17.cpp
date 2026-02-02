#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long minimumCost(vector<int>& nums, int k, int dist) {
        int n = nums.size();
        long long base = nums[0];

        multiset<long long> small, large;
        long long sumSmall = 0;

        auto rebalance = [&]() {
            while ((int)small.size() > k - 1) {
                auto it = prev(small.end());
                large.insert(*it);
                sumSmall -= *it;
                small.erase(it);
            }
            while ((int)small.size() < k - 1 && !large.empty()) {
                auto it = large.begin();
                sumSmall += *it;
                small.insert(*it);
                large.erase(it);
            }
        };

        auto add = [&](long long x) {
            if ((int)small.size() < k - 1) {
                small.insert(x);
                sumSmall += x;
            } else {
                auto it = prev(small.end());
                if (x < *it) {
                    sumSmall += x - *it;
                    large.insert(*it);
                    small.erase(it);
                    small.insert(x);
                } else {
                    large.insert(x);
                }
            }
            rebalance();
        };

        auto remove = [&](long long x) {
            auto it = small.find(x);
            if (it != small.end()) {
                sumSmall -= x;
                small.erase(it);
            } else {
                large.erase(large.find(x));
            }
            rebalance();
        };

        // Initial window [1 .. dist+1]
        for (int i = 1; i <= dist + 1; i++) {
            add(nums[i]);
        }

        long long ans = sumSmall;

        // Slide window
        for (int i = dist + 2; i < n; i++) {
            add(nums[i]);
            remove(nums[i - (dist + 1)]);
            ans = min(ans, sumSmall);
        }

        return base + ans;
    }
};
