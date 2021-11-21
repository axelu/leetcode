
// 1374. Generate a String With Characters That Have Odd Counts
// https://leetcode.com/problems/generate-a-string-with-characters-that-have-odd-counts/

class Solution {
public:
    string generateTheString(int n) {
        int k = ( n % 2 == 0 ) ? n - 1 : n;
        string r = "";
        for(int i = 0; i < k; ++i) r += "a";
        return k != n ? r + "b" : r;
    }
};
