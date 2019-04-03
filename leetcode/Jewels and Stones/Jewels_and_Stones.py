class Solution:
    def numJewelsInStones(self, J: str, S: str) -> int:
        c = 0
        for letter in J:
            c += S.count(letter)
        return c
