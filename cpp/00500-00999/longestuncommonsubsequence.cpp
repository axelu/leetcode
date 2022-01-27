
// 521. Longest Uncommon Subsequence I
// https://leetcode.com/problems/longest-uncommon-subsequence-i/



class Solution {
public:
    int findLUSlength(string a, string b) {
        int an = a.size();
        int bn = b.size();
        return a == b ? -1 : max(an,bn);
    }
};
