class Solution {
public:
    int minimumPairRemoval(vector<int>& nums) {
        int ops = 0;

        while (true) {
            // check if array is non-decreasing
            bool sorted = true;
            for (int i = 1; i < nums.size(); i++) {
                if (nums[i] < nums[i - 1]) {
                    sorted = false;
                    break;
                }
            }
            if (sorted) break;

            // find leftmost pair with minimum sum
            int idx = 0;
            int minSum = nums[0] + nums[1];

            for (int i = 1; i < nums.size() - 1; i++) {
                int s = nums[i] + nums[i + 1];
                if (s < minSum) {
                    minSum = s;
                    idx = i;
                }
            }

            // replace the pair with their sum
            nums[idx] = minSum;
            nums.erase(nums.begin() + idx + 1);

            ops++;
        }

        return ops;
    }
};
