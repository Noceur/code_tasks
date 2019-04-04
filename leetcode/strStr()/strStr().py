class Solution:
    def strStr(self, haystack: str, needle: str) -> int:
        if not needle:
            return 0
        if not needle in haystack:
            return -1
        r = haystack.index(needle)
        return r