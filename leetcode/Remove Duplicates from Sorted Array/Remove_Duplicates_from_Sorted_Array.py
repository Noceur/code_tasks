class Solution:
    def removeDuplicates(self, nums: List[int]) -> int:
        x = list(set(nums))
        x.sort()
        for i, y in enumerate(x):
            nums[i] = x[i]
        return len(x)
