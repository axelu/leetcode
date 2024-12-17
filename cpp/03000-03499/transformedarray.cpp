
// 3379. Transformed Array
// https://leetcode.com/problems/transformed-array/





class Solution {
public:
    vector<int> constructTransformedArray(vector<int>& nums) {
        int n = nums.size();

        vector<int> ans(n);
        for(int i = 0; i < n; ++i) {
            int pos = i + nums[i];
            if( pos >= n ) {
                pos = pos % n;
            } else if( pos < 0 ) {
                pos *= -1;
                int rem = pos % n;
                if( rem == 0 )
                    pos = 0;
                else
                    pos = n - rem;
            }
            // cout << "i " << i << " pos " << pos << endl;
            ans[i] = nums[pos];
        }

        return ans;
    }
};
