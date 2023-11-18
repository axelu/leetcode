
// 2936. Number of Equal Numbers Blocks
// https://leetcode.com/problems/number-of-equal-numbers-blocks/





/**
 * Definition for BigArray.
 * class BigArray {
 * public:
 *     BigArray(vector<int> elements);
 *     int at(long long index);
 *     long long size();
 * };
 */
class Solution {
private:
    // binary search
    long long search(BigArray* nums, long long s, long long e, int target) {
        if( s > e )
            return -1LL;

        long long mid = s + ((e-s)/2LL);
        int val = nums->at(mid);
        if( val == target ) {
            // can we do better?
            long long t = search(nums,mid+1LL,e,target);
            return t != -1LL ? t : mid;
        }

        return search(nums,s,mid-1LL,target);
    }

public:
    int countBlocks(BigArray* nums) {
        long long n = nums->size();

        int ans  = 0;

        long long i = 0LL;
        while( true ) {
            ++ans;

            int target = nums->at(i);
            long long e = search(nums,i,n-1,target);
            if( e == n-1 )
                break;
            i = e + 1LL;
        }

        return ans;
    }
};
