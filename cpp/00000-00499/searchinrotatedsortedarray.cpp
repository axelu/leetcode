
// 33. Search in Rotated Sorted Array
// https://leetcode.com/problems/search-in-rotated-sorted-array/




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
        // does NOT work when array has dups
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
        // will work if array includes duplicates
        int i = s + ((e - s)/2);

        if( pNums[i] > pNums[i + 1] )
            return i;

        if(pNums[i] < pNums[s]) {
            return findMaxIdx2(s, i - 1);
        } else if(pNums[i] > pNums[e]) {
            return findMaxIdx2(i + 1, e);
        } else {
            // array is rotated -> return last element
            return e;
        }
    }

public:
    int search(vector<int>& nums, int target) {
        size_t n = nums.size();
        if( n == 1 ) return nums[0] == target ? 0 : -1;

        pNums = nums.data();

        // find idx of max element
        int maxIdx = findMaxIdx2(0,n-1);
        /*
        // short cutting the search if desired
        // could be further improved as we could check in which part
        // in case of a rotated array the target could lie, so we only would need to search that part
        if( maxIdx != -1 )
            if( nums[maxIdx] == target ) {
                return maxIdx;
            } else if( nums[maxIdx] < target ) {
                return -1;
            } else {
                if( maxIdx == n-1 ) {
                    if( target < nums[0] ) return -1;
                } else {
                    if( target < nums[maxIdx+1] ) return -1;
                }
            }
        if( maxIdx == n-1 || maxIdx == -1 )
            return search(0,n-1,target);
        */

        // binary search [0,maxidx] and [maxidx,n-1]
        int i = search(0,maxIdx,target);
        return i != -1 ? i : search(maxIdx+1,n-1,target);
    }
};
