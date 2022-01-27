
// 1963. Minimum Number of Swaps to Make the String Balanced
// https://leetcode.com/problems/minimum-number-of-swaps-to-make-the-string-balanced/




class Solution {
public:
    int minSwaps(string& s) {
        int n = s.size();

        int fo = 0; // left  to right (forward) count open  brackets
        int fc = 0; // left  to right (forward) count close brackets
        int ro = 0; // right to left  (reverse) count open  brackets
        int rc = 0; // right to left  (reverse) count close brackets

        int ans = 0;

        int j = n;
        for(int i = 0; i < n; ++i) {
            if( i == j )
                break;

            if( s[i] == '[' )
                ++fo;
            else
                ++fc;

            if( fc > fo ) {
                // we have found an unbalaced closing bracket at i
                // let's find the 1st unbalanced open bracket from right
                --j;
                for(;;--j) {
                    if( s[j] == '[' )
                        ++ro;
                    else
                        ++rc;
                    if( ro > rc )
                        break;
                }
                // record the swap;
                ++ans;
                --fc;++fo;
                --ro;++rc;
            }
        }

        return ans;
    }
};
