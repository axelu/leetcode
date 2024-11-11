
// 3231. Minimum Number of Increasing Subsequence to Be Removed
// https://leetcode.com/problems/minimum-number-of-increasing-subsequence-to-be-removed/




/* example [3,4,1,2,7,8,6,7]

 */
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();

        // go from right to left
        // connect current node to smallest possible node on the right

        map<int,vector<int>> mp; // value, {indicies}
        int p[n]; memset(p,-1,sizeof p);
        for(int i = n-1; i >= 0; --i) {

            auto ub = mp.upper_bound(nums[i]);
            if( ub != mp.end() ) {
                p[ub->second.back()] = i;
                ub->second.pop_back();

                if( ub->second.empty() )
                    mp.erase(ub);
            }
            auto f = mp.insert({nums[i],{i}});
            if( !f.second )
                f.first->second.push_back(i);
        }

        int cnt = 0;
        for(int i = 0; i < n; ++i)
            if( p[i] == -1 )
                ++cnt;

        return cnt;
    }
};
