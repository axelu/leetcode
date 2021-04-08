
// 1095. Find in Mountain Array
// https://leetcode.com/problems/find-in-mountain-array/



/**
 * // This is the MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 * class MountainArray {
 *   public:
 *     int get(int index);
 *     int length();
 * };
 */

class Solution {
private:
    MountainArray * pMountainArr;
    int * pA;

    int get(int i) {
        int ret;
        if( pA[i] != -1 ) {
            ret = pA[i];
        } else {
            ret = pMountainArr->get(i);
            pA[i] = ret;
        }
        return ret;
    }

    int lsearch(int s, int e, int& target) {
        // ascending order

        if( s > e ) return -1;
        if( s == e )
            return target == get(s) ? s : -1;

        int i = s + ((e - s)/2);
        int k = get(i);
        if( target == k ) {
            return i;
        } else if( k > target ) {
            return lsearch(s,i-1,target);
        } else {
            return lsearch(i+1,e,target);
        }
    }


    int rsearch(int s, int e, int& target) {
        // descending order

        if( s > e ) return -1;
        if( s == e )
            return target == get(s) ? s : -1;

        int i = s + ((e - s)/2);
        int k = get(i);
        if( target == k ) {
            return i;
        } else if( k < target ) {
            return rsearch(s,i-1,target);
        } else {
            return rsearch(i+1,e,target);
        }
    }

    int findPeak(int s, int e) {
        int i = s + ((e - s)/2);
        // A[i-1] < A[i] < A[i+1] -> we are at the left side of the peak
        // A[i-1] < A[i] > A[i+1] -> we are at the peak
        // A[i-1] > A[i] > A[i+1] -> we are at the right side of the peak
        int l = get(i-1);
        int m = get(i);
        int r = get(i+1);

        if( l < m && m > r ) {
            // peak
            return i;
        } else if( l < m && m < r ) {
            // we are at the left side of the peak -> search to the right
            return findPeak(i+1,e);
        } else {
            // l > m > r
            // we are at the right side of the peak -> search to the left
            return findPeak(s,i-1);
        }
    }
public:
    int findInMountainArray(int target, MountainArray &mountainArr) {
        int n = mountainArr.length();

        // base cases
        int s = mountainArr.get(0);
        if( s == target ) return 0;
        int e = mountainArr.get(n-1);
        if( s > target && e > target ) return -1;
        // s < target and/or e < target
        if( n == 3 ) {
            if( mountainArr.get(1) == target ) {
                return 1;
            } else if( e == target ) {
                return 2;
            } else {
                return -1;
            }
        }

        int a[n];
        for(int i = 0; i < n; ++i) a[i] = -1;
        a[0] = s;
        a[n-1] = e;
        pA = a;

        // observations:
        // if peak < target -> target is not in our mountainArr
        // if s > target -> target can only be on right side of peak
        // if e > target -> target can only be on left side of peak

        pMountainArr = &mountainArr;
        int peakIdx = findPeak(1,n-2); // binary search
        if( a[peakIdx] < target) {
            return -1;
        } else if ( a[peakIdx] == target ) {
            return peakIdx;
        }

        // as we have a limit number of calls to mountainArr.get(i) we want to limit our
        // search range as much as possible beforehand based on the points we gathered so far
        // maybe we actually already stumbled on the target
        int r = -1;
        int si,ei;
        if( s < target ) {
            // looking left of peak first as we are after the minimum idx of target if it exists
            si = 1;
            ei = peakIdx-1;
            for(int i = 1; i < peakIdx; ++i) {
                if( a[i] != -1 ) {
                    if( a[i] == target ) {
                        return i;
                    } else if( a[i] < target ) {
                        si = i;
                    } else {
                        ei = i;
                    }
                }
            }
            // find -> binary search
            r = lsearch(si,ei,target);
            if( r != -1 ) return r;
        }
        if( e == target ) {
            return n-1;
        } else if( e < target ) {
            si = peakIdx+1;
            ei = n-1;
            for(int i = peakIdx+1; i < n; ++i) {
                if( a[i] != -1 ) {
                    if( a[i] == target ) {
                        return i;
                    } else if( a[i] > target ) {
                        si = i;
                    } else {
                        ei = i;
                    }
                }
            }
            // find -> binary search
            return rsearch(si,ei,target);
        }

        return -1;
    }
};
