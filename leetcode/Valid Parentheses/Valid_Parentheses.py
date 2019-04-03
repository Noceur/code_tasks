class Solution:
    def isValid(self, s: str) -> bool:
        if not s:
            return True
        p_type = {
            "(": {
                "kind": "round",
                "type": "open"
            },
            "[": {
                "kind": "square",
                "type": "open"
            },
            "{": {
                "kind": "curly",
                "type": "open"
            },
            ")": {
                "kind": "round",
                "type": "close"
            },
            "]": {
                "kind": "square",
                "type": "close"
            },
            "}": {
                "kind": "curly",
                "type": "close"
            }
        }
        r = ""
        if (not len(s) % 2 == 0) or not p_type[s[0]]['type'] == "open":
            return False
        for i, letter in enumerate(s):

            if p_type[letter]['type'] == "open":
                r += letter
                continue
            elif p_type[letter]['type'] == "close" and p_type[letter]['kind'] == p_type[r[-1]]['kind']:
                r = r[:-1]
                continue
            return False
        if not r:
            return True
        return False
