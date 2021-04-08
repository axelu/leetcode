
// 1437. Check If All 1's Are at Least Length K Places Away
// https://leetcode.com/problems/check-if-all-1s-are-at-least-length-k-places-away/



class Solution {
public:
    bool kLengthApart(vector<int>& nums, int k) {
        size_t n = nums.size();
        if( n == 1 ) return true;
        if( k == 0 ) return true;

        int prev = -1; // idx of the prior 1
        int dist;
        for(int i = 0; i < n; ++i) {
            if( nums[i] == 1 ) {
                if( prev == -1 ) {
                    prev = i;
                    continue;
                }
                dist = i - prev;
                if( dist - 1 < k ) return false;
                prev = i;
            }
        }
        return true;
    }
};
