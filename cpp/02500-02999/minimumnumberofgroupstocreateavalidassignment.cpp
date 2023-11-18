
// 2910. Minimum Number of Groups to Create a Valid Assignment
// https://leetcode.com/problems/minimum-number-of-groups-to-create-a-valid-assignment/





class Solution {
public:
    int minGroupsForValidAssignment(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return 1;

        unordered_map<int,int> cnt; // val, cnt
        for(int val: nums)
            ++cnt[val];

        int cnt_sz = cnt.size();
        if( cnt_sz == 1 )
            return 1;

        // the minimum occurence of any given value dictates the max group size (grp_sz + 1) we could ever have
        // the minimum group size we could ever have is 1
        // each number of occurence f of a given value
        // we need to be able to split as follows
        //     ((grp_sz + 1) * a) + (grp_sz * b) = f
        // we are looking for the max grp_sz in order to minimize the number of groups

        int mn_cnt = INT_MAX;
        for(auto p: cnt)
            mn_cnt = min(mn_cnt,p.second);

        int ans = INT_MAX;

        // brute force
        for(int grp_sz = 1; grp_sz <= mn_cnt; ++grp_sz) {

            int groups = 0;
            for(auto p: cnt) {
                int f   = p.second;
                int a   = f / (grp_sz + 1);
                int rem = f % (grp_sz + 1);
                if( rem == 0 ) {
                    groups += a;

                } else if( grp_sz - rem <= a ) {
                    // we can have a - (grp_sz - rem) groups of size grp_sz + 1 and grp_sz - b + 1 groups of size grp_sz
                    groups += a + 1;

                } else {
                    // we cannot split f
                    groups = INT_MAX;
                    break;
                }
            }
            ans = min(ans,groups);
        }

        return ans;
    }
};
