
// 2592. Maximize Greatness of an Array
// https://leetcode.com/problems/maximize-greatness-of-an-array/



class Solution {
public:
    int maximizeGreatness(vector<int>& nums) {
        int n = nums.size();

        multiset<int> mst(nums.begin(),nums.end());

        int ans = 0;
        for(int i = 0; i < n; ++i) {

            // greedy
            // find the smallest element greater than nums[i];
            //    if found, place it and delete from mst
            //    if not found, please the smallest number in mst and delete from mst

            auto f = mst.upper_bound(nums[i]);
            if( f != mst.end() ) {
                ++ans;
                mst.erase(f);
            } else {
                mst.erase(mst.begin());
            }
        }

        return ans;
    }
};
