
// 2499. Minimum Total Cost to Make Arrays Unequal
// https://leetcode.com/problems/minimum-total-cost-to-make-arrays-unequal/




class Solution {
public:
    long long minimumTotalCost(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        long long ans = 0LL;
        int cnt[n+1];memset(cnt,0,sizeof cnt);
        int mx_cnt = 0; // cnt of value that occurs most often
        int mx_cnt_val; // val of element that occurs most often
        int swap = 0;   // cnt of elements we need to swap

        for(int i = 0; i < n; ++i) {
            if( nums1[i] == nums2[i] ) {
                // this position needs to be swapped
                ++swap;
                // if we used idx 0 as a parking lot, our swaps cost us i
                ans += i;

                ++cnt[nums1[i]];
                if( cnt[nums1[i]] > mx_cnt ) {
                    mx_cnt = cnt[nums1[i]];
                    mx_cnt_val = nums1[i];
                }
            }
        }

        // if we don't have an element that occurs more than swap/2 times
        // the we can swap all duplicates among themselves and we are done
        if( mx_cnt <= (swap/2) )
            return ans;

        // we have to swap duplicates with elements of the array that
        // don't need swapping per se
        // we can only swap with them if neither nums1[i] nor nums2[i] are
        // our max cnt value
        for(int i = 0; i < n; ++i) {
            if( mx_cnt > (swap/2) && nums1[i] != nums2[i] &&
                nums1[i] != mx_cnt_val && nums2[i] != mx_cnt_val) {

                ans += i;
                ++swap;
            }
        }
        // check if we made enough swaps
        if( mx_cnt > (swap/2) )
           return -1;

        return ans;
    }
};
