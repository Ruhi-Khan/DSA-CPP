class Solution {
public:
    int countMonobit(int n) {
        int count = 0;

        // 0 is monobit
        count++;

        int val = 1;  // 1, 3, 7, 15, ...
        while (val <= n) {
            count++;
            val = (val << 1) | 1;
        }

        return count;
    }
};
