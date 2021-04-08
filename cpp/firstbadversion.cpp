
// 278. First Bad Version
// https://leetcode.com/problems/first-bad-version/



// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        if( n == 1 ) return isBadVersion(1);

        // binary search
        int s = 1;
        int e = n;
        int ans = e;
        while( s <= e ) {
            int mid = s + ((e - s)/2);
            bool isBad = isBadVersion(mid);
            if( isBad ) {
                ans = mid;
                e = mid-1;
            } else {
                s = mid+1;
            }
        }
        return ans;
    }
};
