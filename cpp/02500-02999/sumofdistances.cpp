
// 2615. Sum of Distances
// https://leetcode.com/problems/sum-of-distances/



class Solution {
public:
    vector<long long> distance(vector<int>& nums) {
        int n = nums.size();

        vector<long long> ans(n,0LL);

        unordered_map<int,vector<int>> um; // value, list of indicies
        for(int i = 0; i < n; ++i)
            um[nums[i]].push_back(i);

        for(auto it = um.begin(); it != um.end(); ++it) {
            // create a prefixSum of the indicies at which the value exists
            int indicies_sz = it->second.size();
            long long prefixSum[indicies_sz+1];
            prefixSum[0] = 0LL;
            for(int i = 1; i <= indicies_sz; ++i)
                prefixSum[i] = prefixSum[i-1] + it->second[i-1];

            // we know that for all the indicies in the list, the value is the same
            // example where value == 1 respectively indices 0, 2, 3
            //          0 1 2 3 4
            // nums     1 3 1 1 2
            // so, for the indicies where value == 1
            //            0 1 2 3
            // indicies   0 2 3
            // prefixSum  0 0 2 5
            // index 0 -> ans[0] = |0 - 2| + |0 - 3| = 5
            //   which is equivalent to
            //   prefixSum to the right of i - (number of indicies to the right of i times i)
            //   Note: the same will apply to the left of i

            for(int i = 0; i < indicies_sz; ++i) {
                long long prefixSum_lft    = prefixSum[i];
                long long nbr_indicies_lft = i;

                long long prefixSum_rgt    = prefixSum[indicies_sz] - prefixSum[i+1];
                long long nbr_indicies_rgt = indicies_sz - i - 1;

                ans[it->second[i]] = abs((prefixSum_lft - nbr_indicies_lft * it->second[i])) +
                                     abs((prefixSum_rgt - nbr_indicies_rgt * it->second[i]));
            }
        }

        return ans;
    }
};
