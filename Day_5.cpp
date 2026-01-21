class Solution {
public:
    vector<int> minBitwiseArray(vector<int>& nums) {
        vector<int> ans;
        
        for (int num : nums) {
            // If num is even, impossible to achieve
            if (num % 2 == 0) {
                ans.push_back(-1);
                continue;
            }
            
            // For num = 3 (11): ans should be 1 (01), so clear bit 1
            // For num = 5 (101): ans should be 4 (100), so clear bit 0  
            // For num = 7 (111): ans should be 3 (011), so clear bit 2
            
            // Find the rightmost 0 bit in num
            // The answer has a 0 at the position right before this 0 bit
            
            // Find position of rightmost 0 bit
            int pos = 0;
            while ((num >> pos) & 1) {
                pos++;
            }
            
            // The bit at position (pos-1) should be cleared in the answer
            int result = num ^ (1 << (pos - 1));
            
            ans.push_back(result);
        }
        
        return ans;
    }
};