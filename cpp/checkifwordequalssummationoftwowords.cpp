
// 1880. Check if Word Equals Summation of Two Words
// https://leetcode.com/problems/check-if-word-equals-summation-of-two-words/




class Solution {
private:
    int wordValue(string& s) {
        int ret = 0;
        int f = 1;
        for(int i = s.size()-1; i >= 0; --i) {
            ret += (s[i]-'a')*f;
            f *= 10;
        }
        return ret;
    }
public:
    bool isSumEqual(string firstWord, string secondWord, string targetWord) {
        return wordValue(firstWord) + wordValue(secondWord) == wordValue(targetWord);
    }
};
