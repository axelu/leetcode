

// 2263. Make Array Non-decreasing or Non-increasing
// https://leetcode.com/problems/make-array-non-decreasing-or-non-increasing/




class Solution {
private:
    int mn(vector<int>& nums) {

        int ret = 0;

        priority_queue<int,vector<int>,greater<int>> pq; // min heap

        pq.push(nums[0]);
        for(int i = 1; i < nums.size(); ++i) {
            int x = nums[i];
            pq.push(x);
            ret += x - pq.top();
            pq.pop();
            pq.push(x);
        }

        return ret;
    }
public:
    int convertArray(vector<int>& nums) {
        if( nums.size() == 1 )
            return 0;

        int a = mn(nums);
        transform(nums.begin(),nums.end(),nums.begin(),
                  [](int& x) { return x * -1; });

        return min(a,mn(nums));
    }
};
