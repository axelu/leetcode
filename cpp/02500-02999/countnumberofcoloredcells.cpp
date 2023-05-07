
// 2579. Count Total Number of Colored Cells
// https://leetcode.com/problems/count-total-number-of-colored-cells/



class Solution {
public:
    long long coloredCells(int n) {
        // 1       1
        // 2       5    4 +  1
        // 3      13    8 +  5
        // 4      25   12 + 13
        // 5      41   16 + 25
        // 6      61   20 + 41
        // ...

        long long ans = 1LL;
        long long s = 4LL;
        for(int i = 2; i <= n; ++i) {
            ans = s + ans;
            s = s + 4LL;
        }

        return ans;
    }
};
