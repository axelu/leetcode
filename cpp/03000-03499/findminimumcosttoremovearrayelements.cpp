
// 3469. Find Minimum Cost to Remove Array Elements
// https://leetcode.com/problems/find-minimum-cost-to-remove-array-elements/





class Solution {
private:
    int mem[1000][1000];

    int rec(vector<int>& nums, int n, int i, int survivor) {
        // cout << "rec i " << i << " survivor " << survivor << endl;
        // survivor val[i] = nums[survivor]
        int val = nums[survivor];

        if( i == n-1 )
            return val;
        if( i == n-2 )
            return val > nums[n-1] ? val : nums[n-1];
        if( i == n-3 ) {
            vector<int> v{val, nums[n-2], nums[n-1]};
            sort(begin(v), end(v));
            return v[0] + v[2];
        }

        if( mem[i][survivor] != -1 )
            return mem[i][survivor];

        // i   i+1 i+2
        // x   x
        // x       x
        //     x   x

        int a = max(val, nums[i+1]) + rec(nums, n, i+2, i+2);
        int b = max(val, nums[i+2]) + rec(nums, n, i+2, i+1);
        int c = max(nums[i+1], nums[i+2]) + rec(nums, n, i+2, survivor);

        return mem[i][survivor] = min({a,b,c});
    }

public:
    int minCost(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return nums[0];
        if( n == 2 )
            return nums[0] > nums[1] ? nums[0] : nums[1];
        if( n == 3 ) {
            sort(begin(nums), end(nums));
            return nums[0] + nums[2];
        }

        memset(mem,-1,sizeof mem);
        return rec(nums, n, 0, 0);
    }
};
