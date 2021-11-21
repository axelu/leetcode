
// 1165. Single-Row Keyboard
// https://leetcode.com/problems/single-row-keyboard/




class Solution {
public:
    int calculateTime(string keyboard, string word) {
        unordered_map<char,int> um;
        for(int i = 0; i < 26; ++i)
            um.insert({keyboard[i],i});

        int ans = 0;
        int currIdx = 0;
        int t;
        for(int i = 0; i < word.size(); ++i) {
            t = um.find(word[i])->second;
            ans += abs(currIdx - t);
            currIdx = t;
        }
        return ans;
    }
};
