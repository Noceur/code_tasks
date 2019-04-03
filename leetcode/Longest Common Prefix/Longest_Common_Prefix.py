class Solution:
    def longestCommonPrefix(self, strs: List[str]) -> str:
        if not strs:
            return ""
        a = set()
        r = ""
        for x in zip(*strs):
            for i in x:
                a.add(i)
            if len(a) > 1:
                return r
            else:
                r += list(a)[0]
                a.clear()
        return r
