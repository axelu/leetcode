
// 1546. Maximum Number of Non-Overlapping Subarrays With Sum Equals Target
// https://leetcode.com/problems/maximum-number-of-non-overlapping-subarrays-with-sum-equals-target/




class Solution {
public:
    int maxNonOverlapping(vector<int>& nums, int target) {
        int n = nums.size();

        unordered_map<int,vector<int>> um; // prefixSum, indicies

        int prefixSum[n+1];
        prefixSum[0] = 0;
        for(int i = 1; i <= n; ++i) {
            prefixSum[i] = prefixSum[i-1] + nums[i-1];
            um[prefixSum[i]].push_back(i);
        }

        int ans = 0;

        int last = n;
        for(int i = n-1; i >= 0; --i) {
            int t = prefixSum[i] + target;

            // find the 1st index greater than i at which t exists
            auto f = um.find(t);
            if( f != um.end() ) {
                auto idx = upper_bound(f->second.begin(), f->second.end(), i);
                if( idx != f->second.end() ) {

                    // there is a subarray [u,*idx-1] with sum = target

                    if( *idx - 1 < last ) {
                        ++ans;
                        last = i;
                    }
                }
            }
        }

        return ans;
    }
};
