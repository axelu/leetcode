
// 1906. Minimum Absolute Difference Queries
// https://leetcode.com/problems/minimum-absolute-difference-queries/





class Solution {
public:
    vector<int> minDifference(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();

        int m[101][n];
        for(int i = 1; i < 101; ++i)
            m[i][0] = -1;
        m[nums[0]][0] = 0;
        for(int i = 1; i < n; ++i) {
            m[nums[i]][i] = i;
            for(int j = 1; j < 101; ++j) {
                if( j == nums[i] )
                    continue;
                m[j][i] = m[j][i-1];
            }
        }
        /*
        for(int i = 1; i < 101; ++i) {
            cout << i << ": ";
            for(int j = 0; j < n; ++j)
                cout << m[i][j] << " ";
            cout << endl;
        }
        */


        int qsz = queries.size();
        vector<int> ans(qsz,-1);
        int s,e,d,pre;
        for(int i = 0; i < qsz; ++i) {
            s = queries[i][0];
            e = queries[i][1];
            d = INT_MAX;
            pre = -1;
            for(int j = 1; j < 101; ++j) {
                if( m[j][e] >= s ) {
                    if( pre != -1 )
                        d = min(d,j-pre);
                    pre = j;
                }
            }
            if( d == INT_MAX )
                continue;
            ans[i] = d;
        }

        return ans;
    }
};
