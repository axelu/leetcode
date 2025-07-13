
// 3576. Transform Array to All Equal Elements
// https://leetcode.com/problems/transform-array-to-all-equal-elements/






class Solution {
private:
    bool solve(vector<int>& nums, int n, int pos, bool flipped, int t, int k) {
        // cout << "solve pos " << pos << " flipped " << flipped << " t " << t << " k " << k << endl;
        if( k < 0 )
            return false;

        if( pos == n )
            return flipped == false;

        int real_value = flipped ? nums[pos] * (-1) : nums[pos];

        bool ret;
        if( real_value == t )
            ret = solve(nums, n, pos+1, false, t, k);
        else
            ret = solve(nums, n, pos+1, true, t, k-1);

        return ret;
    }

public:
    bool canMakeEqual(vector<int>& nums, int k) {
        int n = nums.size();


        if( solve(nums, n, 0, false, 1, k) )
            return true;

        return solve(nums, n, 0, false, -1, k);
    }
};
