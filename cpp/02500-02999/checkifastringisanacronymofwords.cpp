
// 2828. Check if a String Is an Acronym of Words
// https://leetcode.com/problems/check-if-a-string-is-an-acronym-of-words/



class Solution {
public:
    bool isAcronym(vector<string>& words, string s) {
        string str = "";
        for(string& w: words)
            str += w[0];

        return str == s;
    }
};
