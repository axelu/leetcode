
// 2602. Minimum Operations to Make All Array Elements Equal
// https://leetcode.com/problems/minimum-operations-to-make-all-array-elements-equal/






/* example nums = [3,1,6,8], queries = [1,5]
 * query 1: we have 3 elements > 1 with a sum of 17, there sum should be 3
 *          answer: 17 - 3 = 14
 * query 2: we have 2 elements > 5 with a sum of 14, there sum should be 10
 *          we have 2 elements < 5 with a sum of  4, there sum should be 10
 *          answer: (14 - 10) + (10 - 4) = 10
 * so we need to sort numbers and have a prefixSum of the sorted array
 * then we do binary search
 */
class Solution {
private:
    int search1(vector<int>& nums, int target) {
        int n = nums.size();
        // binary search greatest element less than target
        // returns n-1 if nums[n-1] < target
        // returns  -1 if nums[0] > target
        int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( nums[mid] < target )
                s = mid+1;
            else
                e = mid;
        }
        if( (s < n && nums[s] >= target) || s == n )
            --s;

        return s;
    }

    int search2(vector<int>& nums, int target) {
        int n = nums.size();
        // returns 'n' if nums[n-1] <= target
        // returns  0  if nums[0] > target
        // binary search upper bound while loop
        // upper bound -> greater than target
        int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( target >= nums[mid] )
                s = mid + 1;
            else
                e = mid;
        }
        if( s < n && nums[s] <= target )
            ++s;

        return s;
    }

public:
    vector<long long> minOperations(vector<int>& nums, vector<int>& queries) {
        int n = nums.size();

        sort(nums.begin(),nums.end());

        long long prefixSum[n+1];
        prefixSum[0] = 0;
        for(int i = 1; i <= n; ++i)
            prefixSum[i] = prefixSum[i-1] + nums[i-1];

        int q_sz = queries.size();
        vector<long long> ans(q_sz);
        for(int i = 0; i < q_sz; ++i) {
            long long t = 0;
            long long target = queries[i];

            // less than
            int idx = search1(nums,target);
            if( idx > -1 )
                t += ((idx + 1) * target) - prefixSum[idx+1];

            // greater than
            idx = search2(nums,target);
            if( idx < n )
                t +=  (prefixSum[n] - prefixSum[idx]) - ((n - idx) * target);

            ans[i] = t;
        }

        return ans;
    }
};
