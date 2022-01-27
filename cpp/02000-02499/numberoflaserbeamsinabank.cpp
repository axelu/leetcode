
// 2125. Number of Laser Beams in a Bank
// https://leetcode.com/problems/number-of-laser-beams-in-a-bank/


class Solution {
public:
    int numberOfBeams(vector<string>& bank) {
        int m = bank.size();
        int n = bank[0].size();

        int ans = 0;
        int pre = 0; // device count of previous row
        int cur;     // device count of current row

        for(int i = 0; i < m; ++i) {
            cur = 0;
            for(int j = 0; j < n; ++j)
                if( bank[i][j] == '1' )
                    ++cur;
            if( cur > 0 ) {
                ans += cur*pre;
                pre = cur;
            }
        }

        return ans;
    }
};
