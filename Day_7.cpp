import heapq
from typing import List

class Solution:
    def minimumPairRemoval(self, nums: List[int]) -> int:
        n = len(nums)
        if n <= 1:
            return 0

        val = nums[:]
        left = [-1] * n
        right = [-1] * n
        alive = [True] * n

        for i in range(n):
            if i > 0:
                left[i] = i - 1
            if i < n - 1:
                right[i] = i + 1

        # count decreasing pairs
        bad = 0
        for i in range(n - 1):
            if val[i] > val[i + 1]:
                bad += 1

        heap = []
        for i in range(n - 1):
            heapq.heappush(heap, (val[i] + val[i + 1], i))

        ops = 0

        while bad > 0:
            # Find valid minimum pair
            while heap:
                s, i = heapq.heappop(heap)
                j = right[i]

                if j == -1 or not alive[i] or not alive[j]:
                    continue
                
                # Verify sum is still correct
                if val[i] + val[j] != s:
                    continue
                
                # Valid pair found
                break
            else:
                # No valid pair found
                break

            # remove old bad edges
            if left[i] != -1 and val[left[i]] > val[i]:
                bad -= 1
            if val[i] > val[j]:
                bad -= 1
            if right[j] != -1 and val[j] > val[right[j]]:
                bad -= 1

            # merge
            val[i] += val[j]
            alive[j] = False
            right[i] = right[j]
            if right[j] != -1:
                left[right[j]] = i

            # add new bad edges
            if left[i] != -1 and val[left[i]] > val[i]:
                bad += 1
            if right[i] != -1 and val[i] > val[right[i]]:
                bad += 1

            # push new sums
            if left[i] != -1:
                heapq.heappush(heap, (val[left[i]] + val[i], left[i]))
            if right[i] != -1:
                heapq.heappush(heap, (val[i] + val[right[i]], i))

            ops += 1

        return ops


# Test cases
if __name__ == "__main__":
    sol = Solution()
    
    print(f"Input: [5,2,3,1]")
    print(f"Output: {sol.minimumPairRemoval([5,2,3,1])}")
    print(f"Expected: 2\n")
    
    print(f"Input: [1,2,2]")
    print(f"Output: {sol.minimumPairRemoval([1,2,2])}")
    print(f"Expected: 0\n")
    
    print(f"Input: [3,4,1,1,-3,2,4,3]")
    print(f"Output: {sol.minimumPairRemoval([3,4,1,1,-3,2,4,3])}")
    print(f"Expected: 5")