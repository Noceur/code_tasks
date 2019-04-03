class Solution:
    def rec_comp(self, w, l):
        if len(w) > 1:
            if w[:-1] in l:
                if self.rec_comp(w[:-1], l):
                    return True
            return False
        return True

    def longestWord(self, words: List[str]) -> str:
        words.sort()
        words.sort(key=len, reverse=True)

        for word in words:
            if self.rec_comp(word, words):
                return word
