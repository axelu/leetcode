
// 1785. Minimum Elements to Add to Form a Given Sum
// https://leetcode.com/problems/minimum-elements-to-add-to-form-a-given-sum/




class Solution {
public:
    int minElements(vector<int>& nums, int limit, int goal) {
        int n = nums.size();

        long sum = 0L;
        for(int i = 0; i < n; ++i)
            sum += (long)nums[i];

        long diff = abs((long)goal-sum);
        int ans = 0;
        if( diff != 0 ) {
            long q = diff/(long)limit;
            ans += q;
            if( diff % (long)limit != 0 )
                ++ans;
        }

        return ans;
    }
};
