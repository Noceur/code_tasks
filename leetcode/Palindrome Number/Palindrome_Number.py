class Solution:
    def isPalindrome(self, x: int) -> bool:
        if x < 0:
            return False
        else:
            y = list(str(x))
            y.reverse()
            y = ''.join(y)
            y = int(y)
            if x == y:
                return True
            return False
