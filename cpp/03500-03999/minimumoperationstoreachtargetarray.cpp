
// 3810. Minimum Operations to Reach Target Array
// https://leetcode.com/problems/minimum-operations-to-reach-target-array/




class Solution {
public:
    int minOperations(vector<int>& nums, vector<int>& target) {
        int n = nums.size(); // 1 <= n <= 1e5; nums.size() == target.size()
        if( n == 1 )
            return nums[0] != target[0];

        // segments in nums by x
        unordered_map<int,vector<pair<int,int>>> um;
        int s = 0;
        for(int i = 1; i < n; ++i) {
            if( nums[i-1] != nums[i] ) {
                // the segment that started at s is ending at i-1;
                um[nums[i-1]].push_back({s,i-1});
                s = i;
            }
        }
        // finish up
        um[nums[n-1]].push_back({s,n-1});

        // go by each x
        // if all segments of a given x can be eliminated
        // then we do not need to operate for the given x
        // a segment can be elminated, if for all i in that segment
        // nums[i] == target[i] already
        int ans = 0;
        for(auto& p: um) {
            int segs = p.second.size();
            int elim = 0;
            for(auto& se: p.second) {
                int s = se.first;
                int e = se.second;
                bool can_be_eliminated = true;
                for(int i = s; i <= e; ++i) {
                    if( nums[i] != target[i] ) {
                        can_be_eliminated = false;
                        break;
                    }
                }
                if( can_be_eliminated )
                    ++elim;
            }
            if( segs != elim )
                ++ans;
        }

        return ans;
    }
};
