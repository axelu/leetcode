
// 2386. Find the K-Sum of an Array
// https://leetcode.com/problems/find-the-k-sum-of-an-array/






class Solution {
public:
    long long kSum(vector<int>& nums, int k) {
        int n = nums.size();

        long sum = 0; // largest sum by adding all positive values in nums
        for(int& x: nums) {
            if( x > 0 )
                sum += x;
            // make any negative values positive for later processing
            if( x < 0 )
                x = -1 * x;
        }

        long ans = sum;

        sort(nums.begin(),nums.end());

        priority_queue<pair<long,int>> pq; // subsequence sum, index used to reduce sum
        pq.push({sum - nums[0], 0});
        while( k > 1 ) {
            auto p = pq.top();
            pq.pop();
            ans = p.first;
            int i = p.second;
            if( i < n-1 ) {
                // if nums[i] was originally negative, we already subtracted it from sum,
                //     meaning we included it in our subsequence and if we add it to sum,
                //     it means we excluding it from our subsequence
                // if nums[i] was originally positive, we already subtracted it from sum,
                //     meaning we excluded it from our subsequence and if we addit to sum,
                //     it means we including it in our subsequence
                pq.push({ans + nums[i] - nums[i+1], i+1});
                pq.push({ans - nums[i+1], i+1});
            }
            --k;
        }

        return ans;
    }
};
