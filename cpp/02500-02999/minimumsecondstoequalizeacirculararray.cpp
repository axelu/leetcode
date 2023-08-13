
// 2808. Minimum Seconds to Equalize a Circular Array
// https://leetcode.com/problems/minimum-seconds-to-equalize-a-circular-array/





/* example: n = 8
 * index( 0-indexed) 	0	1	2	3	4	5	6	7
 * nums[(i-1+n)%n)	    7	0	1	2	3	4	5	6
 * nums[(i+1)%n)	    1	2	3	4	5	6	7	0
 * we basically can leave each value unchanged, or replace it with
 * its 'left' or 'right' neighbor
 */
class Solution {
public:
    int minimumSeconds(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return 0;
        if( n == 2 )
            return nums[0] == nums[1] ? 0 : 1;

        unordered_map<int,vector<int>> cnt; // val, indicies
        for(int i = 0; i < n; ++i)
            cnt[nums[i]].push_back(i);

        int ans = n/2; // worst case each val in nums is unique
        for(auto& p: cnt) {
            int freq = p.second.size();
            if( freq == 1 )
                continue;
            int t = 0;
            for(int i = 0; i < freq; ++i) {
                if( i == freq-1 ) {
                    t = max(t, ((n + p.second[0]) - p.second[i])/2);
                } else {
                    t = max(t, (p.second[i+1] - p.second[i])/2);
                }
            }
            ans = min(ans,t);
        }

        return ans;
    }
};
