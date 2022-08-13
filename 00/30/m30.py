from collections import Counter, defaultdict
from typing import List


class Solution:
    def findSubstring(self, s: str, words: List[str]) -> List[int]:
        res = []
        word_count = len(words)
        word_size = len(words[0])
        word_dict = Counter(words)

        for i in range(0, word_size):
            start_idx = -1
            wd_copy = word_dict.copy()
            wcnt = word_count
            j = i

            while j <= len(s) - word_size:
                word = s[j: j + word_size]
                if start_idx < 0:
                    start_idx = j

                if wd_copy[word] > 0:
                    wd_copy[word] -= 1
                    wcnt -= 1
                else:
                    j = start_idx
                    start_idx = -1
                    if wcnt != word_count:
                        wd_copy = word_dict.copy()
                        wcnt = word_count

                if wcnt == 0:
                    res.append(start_idx)
                    j = start_idx

                j += word_size

        return res


x = Solution()
print(x.findSubstring("barfoothefoobarman", words = ["foo","bar"]))
print(x.findSubstring("wordgoodgoodgoodbestword", ["word","good","best","word"]))
print(x.findSubstring("barfoofoobarthefoobarman", words = ["bar","foo","the"]))
print(x.findSubstring("lingmindraboofooowingdingbarrwingmonkeypoundcake", ["fooo","barr","wing","ding","wing"]))
print(x.findSubstring("wordgoodgoodgoodbestword", ["word","good","best","good"]))
