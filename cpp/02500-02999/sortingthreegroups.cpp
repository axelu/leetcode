
// 2826. Sorting Three Groups
// https://leetcode.com/problems/sorting-three-groups/




class Solution {
private:
    int count(vector<int>& nums, int n, int s, int e, int grp) {
        if( e < 0 || s >= n )
            return 0;

        int ret = 0;
        for(int i = s; i <= e; ++i)
            if( nums[i] != grp )
                ++ret;

        return ret;
    }

public:
    int minimumOperations(vector<int>& nums) {
        int n = nums.size(); // 1 <= nums.length <= 100

        int ans = INT_MAX;

        // group 1: [0,i)
        // group 2: [i,j)
        // group 3: [j,n)

        for(int i = 0; i <= n; ++i) {
            // group 1: [0,i-1]
            int t1 = count(nums,n,0,i-1,1);

            for(int j = i; j <= n; ++j) {
                // cout << "group 1 " << 0 << " " << i-1 << endl;

                // group 2: [i,j-1]
                // cout << "group 2 " << i << " " << j-1 << endl;
                int t2 = count(nums,n,i,j-1,2);

                // group 3: [j,n-1]
                // cout << "group 3 " << j << " " << n-1 << endl;
                int t3 = count(nums,n,j,n-1,3);

                ans = min(ans, t1 + t2 + t3);
            }
        }

        return ans;
    }
};
