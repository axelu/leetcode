
// 848. Shifting Letters
// https://leetcode.com/problems/shifting-letters/




class Solution {
public:
    string shiftingLetters(string& s, vector<int>& shifts) {
        // 1 <= s.length = shifts.length <= 20000
        int t = 0;
        for(int i = shifts.size()-1; i >= 0; --i) {
            t += shifts[i] % 26;
            s[i] = ((s[i]-'a'+t) % 26)+'a';
        }
        return s;
    }
};
