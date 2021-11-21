
// 1389. Create Target Array in the Given Order
// https://leetcode.com/problems/create-target-array-in-the-given-order/


class Solution {
public:
    vector<int> createTargetArray(vector<int>& nums, vector<int>& index) {
        vector<int> r;
        auto n = nums.size();
        vector<int>::iterator it;
        for(int i = 0; i < n; ++i) {
            it = begin(r)+index[i];
            r.insert(it,nums[i]);
        }

        return r;
    }
};
