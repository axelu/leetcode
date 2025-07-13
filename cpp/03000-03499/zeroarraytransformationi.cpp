
// 3355. Zero Array Transformation I
// https://leetcode.com/problems/zero-array-transformation-i/





class Solution {
public:
    bool isZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();

        // let ti be the number of times a given index i is covered by a query
        // if ti >= nums[i] then we can bring nums[i] to 0

        int line[100001];memset(line,0,sizeof line);

        for(int i = 0; i < queries.size(); ++i) {
            int l = queries[i][0];
            int r = queries[i][1];

            ++line[l];
            --line[r+1];
        }

        int t = 0;
        for(int i = 0; i < n; ++i) {
            t += line[i];
            if( t < nums[i] )
                return false;
        }

        return true;
    }
};
