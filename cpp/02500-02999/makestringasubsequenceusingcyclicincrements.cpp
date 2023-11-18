
// 2825. Make String a Subsequence Using Cyclic Increments
// https://leetcode.com/problems/make-string-a-subsequence-using-cyclic-increments/




class Solution {
public:
    bool canMakeSubsequence(string str1, string str2) {
        int n1 = str1.size();
        int n2 = str2.size();

        if( n2 > n1 )
            return false;

        int i = 0;
        int j = 0;

        while( i < n1 && j < n2 ) {

            if( (str1[i] == str2[j]) ||
                (str1[i] == 'z' && str2[j] == 'a') ||
                (str1[i] + 1 == str2[j]) ) {
                ++i;
                ++j;
                continue;
            }

            ++i;
        }

        return j == n2;
    }
};
