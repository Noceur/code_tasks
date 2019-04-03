class Solution:
    def removeElement(self, nums: List[int], val: int) -> int:
        for i, x in reversed(list(enumerate(nums))):
            if x == val:
                del nums[i]
        return len(nums)