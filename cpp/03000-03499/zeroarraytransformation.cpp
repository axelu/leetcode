
// 3489. Zero Array Transformation IV
// https://leetcode.com/problems/zero-array-transformation-iv/




class Solution {
private:

    int mem[1000][1001];

    int solve(vector<vector<int>>& queries, int q_idx, int val_idx, int val) {
        if( val == 0 )
            return q_idx;

        int q_sz = queries.size();
        if( q_idx == q_sz )
            return 2000; // max q_sz = 1000

        if( mem[q_idx][val] != -1 )
            return mem[q_idx][val];

        int l = queries[q_idx][0];
        int r = queries[q_idx][1];
        int d = queries[q_idx][2];

        // we have a choice
        //    skip current query OR
        //    decrement val by d if we can
        int a = solve(queries, q_idx + 1, val_idx, val);
        int b = 2000;
        if( l <= val_idx && val_idx <= r && val >= d )
            b = solve(queries, q_idx + 1, val_idx, val - d);

        return mem[q_idx][val] = min(a,b);

    }

public:
    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size(); // 1 <= n <= 10; 0 <= nums[i] <= 1000

        // queries[i] = [li, ri, vali]

        // there are only up to 10 pos in nums, what if we solve
        // for each position independently
        // if for one of the positions there is no solution, then
        // there is no solution to the problem -> return -1
        // otherwise max queryindex+1 is our ans

        int ans = -1;
        for(int i = 0; i < n; ++i) {
            memset(mem,-1,sizeof mem);
            int t = solve(queries, 0, i, nums[i]);
            // cout << "i " << i << " nums[i] " << nums[i] << " solve " << t << endl;
            if( t == 2000 )
                return -1;
            ans = max(ans, t);
        }

        return ans;
    }
};
