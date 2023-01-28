
// 974. Subarray Sums Divisible by K
// https://leetcode.com/problems/subarray-sums-divisible-by-k/



class Solution {
public:
    int subarraysDivByK(vector<int>& nums, int k) {
        int n = nums.size(); // 1 <= nums.length <= 30000

        int ans = 0;

        /*
        // brute force
        for(int i = 0; i < n; ++i) {
            int sum = 0;
            for(int j = i; j < n; ++j) {
                sum += nums[j];
                if( sum % k == 0 )
                    ++ans;
            }
        }
        */

        // idea is to count the same remainders
        // to compensate for negatives, we will shift each nums[i]
        // to the equal or next larger multiple of the smallest element
        // example: nums = {2,-2,2,-4}; k = 6
        int offset = 0;
        int mn = *min_element(nums.begin(),nums.end());
        if( mn < 0 ) {
            if( (mn * (-1)) % k == 0 )
                offset = (mn * (-1));
            else
                offset = (((mn * (-1)) / k) + 1) * k;
        }
        // cout << offset << endl;

        int prefixSum[n+1];
        prefixSum[0] = 0;
        unordered_map<int,int> remCnt; // count of remainders
        remCnt[0]++;
        for(int i = 1; i <= n; ++i) {
            prefixSum[i] = prefixSum[i-1] + nums[i-1] + offset;
            int rem = prefixSum[i] % k;
            remCnt[rem]++;
        }

        for(auto it = remCnt.begin(); it != remCnt.end(); ++it) {
            // cout << it->first << ":" << it->second << " ";
            int cnt = it->second - 1;
            int t = cnt * (cnt+1)/2;
            // cout << t << " ";
            ans += t;
        }
        // cout << endl;

        return ans;
    }
};
