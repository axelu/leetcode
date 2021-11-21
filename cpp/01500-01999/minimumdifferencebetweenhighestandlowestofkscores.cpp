
// 1984. Minimum Difference Between Highest and Lowest of K Scores
// https://leetcode.com/problems/minimum-difference-between-highest-and-lowest-of-k-scores/




class Solution {
public:
    int minimumDifference(vector<int>& nums, int k) {
        if( k == 1 )
            return 0;

        int n = nums.size();

        sort(begin(nums),end(nums));

        int ans = 100001;

        map<int,int> m;                 // nums[i],count
        int i = 0;                      // left index
        for(int j = 0; j < n; ++j) {    // right index
            // add nums[j]
            auto p = m.insert({nums[j],1});
            if( !p.second )
                ++p.first->second;

            // sliding window of size k
            if( j-i < k-1 )
                continue;

            ans = min(ans,m.rbegin()->first-m.begin()->first);

            // remove nums[i]
            auto f = m.find(nums[i]);
            if( f->second == 1 )
                m.erase(f);
            else
                --f->second;
            ++i;
        }

        return ans;
    }
};
