
// 3804. Number of Centered Subarrays
// https://leetcode.com/problems/number-of-centered-subarrays/



class Solution {
public:
    int centeredSubarrays(vector<int>& nums) {
        int n = nums.size(); // 1 <= n <= 500; -100000 <= nums[i] <= 100000

        // formula number subarrays n * (n+1)/2
        // worst case n = 500 => 125500

        int ans = 0;

        // brute force
        for(int l = 1; l <= n; ++l) {
            int sum = 0;
            unordered_map<int, int> freq;
            int i = 0;                   // left index
            for(int j = 0; j < n; ++j) { // right index
                sum += nums[j];
                ++freq[nums[j]];

                if( j-i+1 == l ) {
                    if( freq[sum] > 0 )
                        ++ans;
                    --freq[nums[i]];
                    sum -= nums[i];
                    ++i;
                }
            }
        }

        return ans;
    }
};
