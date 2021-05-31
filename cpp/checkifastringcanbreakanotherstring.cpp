
// 1433. Check If a String Can Break Another String
// https://leetcode.com/problems/check-if-a-string-can-break-another-string/



class Solution {
public:
    bool checkIfCanBreak(string s1, string s2) {
        sort(s1.begin(),s1.end());
        sort(s2.begin(),s2.end());

        int n = s1.size(); // s1.length == s2.length == n
        int i;

        // can s1 break s2?
        for(i = 0; i < n; ++i)
            if( s1[i] < s2[i] ) break;
        if( i == n ) return true;
        // can s2 break s1?
        for(i = 0; i < n; ++i)
            if( s2[i] < s1[i] ) break;
        if( i == n ) return true;
        return false;
    }
};
