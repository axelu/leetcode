
// 260. Single Number III
// https://leetcode.com/problems/single-number-iii/


class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        size_t n = nums.size();
        if( 2 == n )
            return nums;
        // assume otherwise n >= 4

        unordered_set<int> us;
        us.reserve(n/2 + 2);
        pair<unordered_set<int>::iterator,bool> p;
        for(int i = 0; i < n; ++i) {
            p = us.insert(nums[i]);
            if( !p.second ) us.erase(nums[i]);
        }

        vector<int> ans(2);
        ans[0] = *us.begin();
        ans[1] = *(next(us.begin()));
        return ans;
    }
};



