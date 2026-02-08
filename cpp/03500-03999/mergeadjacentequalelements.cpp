
// 3834. Merge Adjacent Equal Elements
// https://leetcode.com/problems/merge-adjacent-equal-elements/




class Solution {
public:
    vector<long long> mergeAdjacent(vector<int>& nums) {
        if( nums.size() == 1 )
            return {(long long)nums[0]};

        deque<long long> dq;
        for(auto it = nums.begin(); it != nums.end(); ++it) {
            long long num = *it;
            while( !dq.empty() && dq.back() == num ) {
                num *= 2LL;
                dq.pop_back();
            }
            dq.push_back(num);
        }

        vector<long long> ans;
        while( !dq.empty() ) {
            ans.push_back(dq.front());
            dq.pop_front();
        }

        return ans;
    }
};
