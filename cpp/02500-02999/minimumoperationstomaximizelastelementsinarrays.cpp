
// 2934. Minimum Operations to Maximize Last Elements in Arrays
// https://leetcode.com/problems/minimum-operations-to-maximize-last-elements-in-arrays/




class Solution {
private:
    pair<int,bool> solve(int n, vector<int>& nums1, vector<int>& nums2) {
        bool f = true;
        int cnt = 0; // nbr swaps
        int mx1 = nums1[n-1];
        int mx2 = nums2[n-1];
        for(int i = n-2; i >= 0; --i) {
            int val1 = nums1[i];
            int val2 = nums2[i];

            bool swapped = false;
            if( val1 > mx1 ) {
                // we have to swap
                // let's see if we can
                if( val1 > mx2 || val2 > mx1 ) {
                    f = false;
                    break;
                }
                ++cnt;
                swapped = true;
            }
            if( !swapped && val2 > mx2 ) {
                // we have to swap
                // let's see if we can
                if( val2 > mx1 || val1 > mx2 ) {
                    f = false;
                    break;
                }
                ++cnt;
            }
        }

        return {cnt,f};
    }

public:
    int minOperations(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(); // nums1.size() == nums2.size()
        if( n == 1 )
            return 0;

        // pass 1 - leave n-1 as is
        auto p1 = solve(n,nums1,nums2);
        // cout << "n-1 as-is   possible " << p1.second << " swaps " << p1.first << endl;

        // pass 2 - swap n-1
        int t = nums2[n-1];
        nums2[n-1] = nums1[n-1];
        nums1[n-1] = t;
        auto p2 = solve(n,nums1,nums2);
        // cout << "n-1 swapped possible " << p2.second << " swaps " << p2.first << endl;

        if( !p1.second && !p2.second )
            return -1;

        if( !p1.second )
            return p2.first + 1;            // +1 as we swapped element n-1
        if( !p2.second )
            return p1.first;

        return min(p1.first,p2.first + 1);  // +1 as we swapped element n-1
    }
};
