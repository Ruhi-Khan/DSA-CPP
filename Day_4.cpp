#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> minBitwiseArray(vector<int>& nums) {
        vector<int> ans;

        for(int x : nums) {
            int found = -1;
            for(int a = 0; a < x; a++) {
                if((a | (a + 1)) == x) {
                    found = a;
                    break;
                }
            }
            ans.push_back(found);
        }
        return ans;
    }
};
