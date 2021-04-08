
// 81. Search in Rotated Sorted Array II
// https://leetcode.com/problems/search-in-rotated-sorted-array-ii/
// day 20 November 2020 challenge
// https://leetcode.com/explore/challenge/card/november-leetcoding-challenge/566/week-3-november-15th-november-21st/3537/


class Solution {
private:
    int * pNums;

    int search(int s, int e, int& target) {
        // ascending order

        if( s > e ) return -1;
        if( s == e )
            return target == pNums[s] ? s : -1;

        int i = s + ((e - s)/2);
        int k = pNums[i];
        if( target == k ) {
            return i;
        } else if( k > target ) {
            return search(s,i-1,target);
        } else {
            return search(i+1,e,target);
        }
    }

    int findMaxIdx(int s, int e) {
        // depending on length of array
        // will return EITHER -1 OR n-1 if array is sorted
        if( s > e ) return -1;
        if( s == e )
            return s;

        int i = s + ((e - s)/2);
        if( i < e && pNums[i] > pNums[i+1] )
            return i;

        if( i > s && pNums[i] < pNums[i-1] )
            return i - 1;

        if( pNums[s] >= pNums[i] )
            return findMaxIdx(s, i - 1);

        return findMaxIdx(i + 1, e);
    }

    int findMaxIdx2(int s, int e) {
        // will return n-1 if array is not rotated
        int i = s + ((e - s)/2);

        if( i < e && pNums[i] > pNums[i + 1] )
            return i;
        if( i > s && pNums[i] < pNums[i - 1] )
            return i-1;

        if( pNums[i] < pNums[s] ) {
            return findMaxIdx2(s, i - 1);
        } else if( pNums[i] > pNums[e] ) {
            return findMaxIdx2(i + 1, e);
        } else {
            // array is rotated -> return last element
            return e;
        }
    }

public:
    bool search(vector<int>& nums, int target) {
        // different than https://leetcode.com/problems/search-in-rotated-sorted-array/
        // we can destroy the array as we don't care about the index of the target
        // we only care if it is there or not

        // remove dups from nums
        set<int> dups;
        nums.erase(remove_if(begin(nums), end(nums), [&dups](int i) {
            return !dups.insert(i).second;
        }),end(nums));

        size_t n = nums.size();
        if( n == 0 ) return false;
        if( n == 1 ) return nums[0] == target;

        pNums = nums.data();

        // find idx of max element
        // int maxIdx = findMaxIdx(0,n-1);
        int maxIdx = findMaxIdx2(0,n-1);

        // binary search [0,maxidx] and [maxidx,n-1]
        if( search(0,maxIdx,target) != -1 || search(maxIdx+1,n-1,target) != -1 ) return true;

        return false;
    }
};
