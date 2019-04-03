class Solution:
    def romanToInt(self, s: str) -> int:
        r = 0
        T = {
            'I': 1,
            'V': 5,
            'X': 10,
            'L': 50,
            'C': 100,
            'D': 500,
            'M': 1000
        }
        for i, letter in enumerate(s):
            try:
                if T[s[i]] < T[s[i+1]]:
                    r -= T[s[i]]
                    continue
            except:
                pass
            r += T[s[i]]
        return r
