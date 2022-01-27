
// 2120. Execution of All Suffix Instructions Staying in a Grid
// https://leetcode.com/problems/execution-of-all-suffix-instructions-staying-in-a-grid/


class Solution {
public:
    vector<int> executeInstructions(int n, vector<int>& startPos, string s) {
        int m = s.size();
        vector<int> ans(m);


        int r,c,j,step;
        for(int i = 0; i < m; ++i) {
            r = startPos[0];
            c = startPos[1];
            step = 0;
            for(j = i; j < m; ++j) {
                if( s[j] == 'R' )
                    ++c;
                else if( s[j] == 'D' )
                    ++r;
                else if( s[j] == 'L' )
                    --c;
                else
                    --r;

                if( r < 0 || r == n ||
                    c < 0 || c == n )
                    break;
                ++step;
            }
            ans[i] = step;
        }
        return ans;
    }
};
