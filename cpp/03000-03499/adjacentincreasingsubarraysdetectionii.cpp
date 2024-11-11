
// 3350. Adjacent Increasing Subarrays Detection II
// https://leetcode.com/problems/adjacent-increasing-subarrays-detection-ii/






class Solution {
public:
    int maxIncreasingSubarrays(vector<int>& nums) {
        int n = nums.size(); // 2 <= nums.length <= 2 * 1e5
        if( n == 2 )
            return 1;

        // get start and end indicies
        vector<array<int,2>> v; // {{s0,e0},...}
        int s = -1;
        int e = -1;
        for(int i = 0; i < n; ++i) {

            if( i == 0 ) {
                if( nums[0] < nums[1] ) {
                    s = 0;
                }
                continue;
            }

            if( i == n-1 ) {
                if( s != -1 && nums[i-1] < nums[i] )
                    e = i;
                // do we have a start and an end?
                if( s != -1 && e != -1 ) {
                    v.push_back({s,e});
                    s = -1;
                    e = -1;
                }
                continue;
            }

            if( s == -1 ) {
                // we are looking for a start
                if( nums[i-1] >= nums[i] && nums[i] < nums[i+1] )
                    s = i;
            } else if( e == -1 ) {
                // we are looking for an end
                if( nums[i-1] < nums[i] && nums[i] >= nums[i+1] )
                    e = i;
            }

            // do we have a start and an end?
            if( s != -1 && e != -1 ) {
                v.push_back({s,e});
                s = -1;
                e = -1;
            }
        }

        if( v.empty() )
            return 1;

        int v_sz = v.size();

        if( v_sz == 1 ) {
            int lft = v[0][0];
            int rgt = v[0][1];
            int k = rgt - lft + 1;
            return k / 2;
        }

        int k_mx = 1;

        for(int i = 0; i < v_sz; ++i) {

            int lft = v[i][0];
            int rgt = v[i][1];
            int k = rgt - lft + 1;
            k_mx = max(k_mx, k / 2);

            if( i < v_sz - 1 && v[i+1][0] == rgt + 1) {
                int lft_nxt = v[i+1][0];
                int rgt_nxt = v[i+1][1];
                int k_nxt = rgt_nxt - lft_nxt + 1;
                k_mx = max(k_mx, min(k, k_nxt));
            }
        }

        return k_mx;
    }
};


/* test cases

[2,5,7,8,9,2,3,4,3,1]
[1,2,3,4,4,4,4,5,6,7]
[1,1]
[1,2]
[2,1]
[1,2,1]
[2,2,1]
[3,2,1]
[1,2,2]
[2,2,2]
[3,2,2]
[1,2,3]
[2,2,3]
[3,2,3]
[-3,-19,-8,-16]
[5,8,-2,-1]

*/
