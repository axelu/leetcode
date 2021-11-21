
// 1663. Smallest String With A Given Numeric Value
// https://leetcode.com/problems/smallest-string-with-a-given-numeric-value/
// day 28 January 2021 challenge
// https://leetcode.com/explore/challenge/card/january-leetcoding-challenge-2021/582/week-4-january-22nd-january-28th/3619/



class Solution {
public:
    string getSmallestString(int n, int k) {
        // constraints: 1 <= n <= 105
        //              n <= k <= 26 * n

        string ans = string(n,'a');
        int i = n-1;
        int c;
        while( k > 0 ) {
            // there are i positions, not counting the current position, left
            // and our need is k
            c = k - i;
            // put the largest possible letter on the current index
            if( c >= 26 ) {
                ans[i] = 'z';
                k -= 26;
            } else {
                ans[i] = 96+c;
                k -= c;
            }
            --i;
        }
        return ans;
    }
};
