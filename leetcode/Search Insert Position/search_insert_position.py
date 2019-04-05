class Solution:
    def searchInsert(self, nums: List[int], target: int) -> int:
        if target in nums:
            return nums.index(target)
        for x in nums:
            if x > target:
                return nums.index(x)
        return len(nums)