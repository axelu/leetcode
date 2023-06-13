
// 2453. Destroy Sequential Targets
// https://leetcode.com/problems/destroy-sequential-targets/




class Solution {
public:
    int destroyTargets(vector<int>& nums, int space) {
        int n = nums.size();

        // we are looking for the most common remainder
        // the smallest nums[i] that produces said remainder

        unordered_map<int,array<int,2>> um; // remainder, {count,smallest nums[i] that produced that remainder}
        for(int x: nums) {
            int rem = x % space;
            auto p = um.insert({rem,{1,x}});
            if( !p.second ) {
                ++p.first->second[0];
                p.first->second[1] = min(p.first->second[1],x);
            }
        }

        int mx_cnt = 0;
        int mn_numsi;
        for(auto p: um) {

            if( p.second[0] > mx_cnt ) {
                mx_cnt = p.second[0];
                mn_numsi = p.second[1];
            } else if( p.second[0] == mx_cnt ) {
                mn_numsi = min(mn_numsi,p.second[1]);
            }
        }

        return mn_numsi;
    }
};
