
// 1818. Minimum Absolute Sum Difference
// https://leetcode.com/problems/minimum-absolute-sum-difference/




class Solution {
private:
    // binary search equal or largest less than target
    int search(vector<int>& v, int s, int e, int target) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        if( v[mid] == target ) {
            return mid;
        } else if( v[mid] < target ) {
            // can we do better?
            int t = search(v,mid+1,e,target);
            return t == -1 ? mid : t;
        } else {
            // v[mid] > target
            return search(v,s,mid-1,target);
        }
    }

public:
    int minAbsoluteSumDiff(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(); // n == nums1.length == nums2.length
        if( n == 1 )
            return abs(nums1[0] - nums2[0]);

        // worst case AbsoluteSumDiff
        // n = 100000, each nums1[i] == 1 and each nums2[i] == 100000
        // abs(nums1[i]-nums2[i]) = abs(1-100000) = 99999
        // 99999 * 100000 -> 9999900000
        // INT_MAX           2147483647

        vector<int> nums1sorted(n);
        long absoluteSumDiff = 0;
        for(int i = 0; i < n; ++i) {
            absoluteSumDiff += (long)abs(nums1[i] - nums2[i]);
            nums1sorted[i] = nums1[i];
        }

        if( absoluteSumDiff == 0 )
            return 0;

        sort(nums1sorted.begin(),nums1sorted.end());
        // remove dups
        /*
        unordered_set<int> us;
        for(auto it = nums1sorted.begin(); it != nums1sorted.end(); ) {
            if ( us.find(*it) != us.end() ) {
                it = nums1sorted.erase(it);
            } else {
                us.insert(*it);
                ++it;
            }
        }
        */


        long ans = absoluteSumDiff,d,d_new;
        for(int i = 0; i < n; ++i) {
            // what does the current pair contribute to absoluteSumDiff?
            d = (long)abs(nums1[i] - nums2[i]);
            if( d == 0L )
                continue;

            // lets reduce that
            int t = search(nums1sorted,0,n-1,nums2[i]);
            if( t == -1 ) {
                d_new = (long)abs(nums1sorted[0] - nums2[i]);
                ans = min(ans,absoluteSumDiff-d+d_new);
            } else {
                if( nums1sorted[t] == nums2[i] ) {
                    ans = min(ans,absoluteSumDiff-d);
                } else {
                    d_new = (long)abs(nums1sorted[t] - nums2[i]);
                    ans = min(ans,absoluteSumDiff-d+d_new);
                    if( t != n-1) {
                        d_new = (long)abs(nums1sorted[t+1] - nums2[i]);
                        ans = min(ans,absoluteSumDiff-d+d_new);
                    }
                }
            }
        }

        return ans % 1000000007;
    }
};
