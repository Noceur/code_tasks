class Solution:
    def reverse(self, x: int) -> int:
        x = str(x)
        o = ""
        neg = False
        if x[0] == "-":
            neg = True
            x = x[1:]
        for i in x:
            o = i + o
        if int(o) > 2147483647:
            return 0
        if neg:
            o = "-" + o
        return int(o)
