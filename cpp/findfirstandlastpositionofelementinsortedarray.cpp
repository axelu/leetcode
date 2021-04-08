
// 34. Find First and Last Position of Element in Sorted Array
// https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/




class Solution {
private:
    int N;
    int startStart;
    int startEnd;

    // binary search
    // largest index i with A[i] = target
    int searchEnd(vector<int>& v, int s, int e, int target) {
        if( s > e ) return -1;

        int mid = s + ((e - s)/2);
        if( v[mid] == target ) {
            if( startEnd == -2 ) startEnd = mid == 0 ? 0 : mid-1;
            // can we do better?
            int ans = searchEnd(v,mid+1,e,target);
            return ans != -1 ? ans : mid;
        } else if( v[mid] < target ) {
            if( mid+1 > startStart ) startStart = mid+1;
            return searchEnd(v,mid+1,e,target);
        } else {
            // v[mid] > target
            return searchEnd(v,s,mid-1,target);
        }
    }

    // binary search
    // smallest index i with A[i] = target
    int searchStart(vector<int>& v, int s, int e, int target) {
        if( s == -1 || e == N || s > e ) return -1;

        int mid = s + ((e - s)/2);
        if( v[mid] == target ) {
            // can we do better?
            int ans = searchStart(v,s,mid-1,target);
            return ans != -1 ? ans : mid;
        } else if( v[mid] < target ) {
            return searchStart(v,mid+1,e,target);
        } else {
            // v[mid] > target
            return searchStart(v,s,mid-1,target);
        }
    }

public:
    vector<int> searchRange(vector<int>& nums, int target) {
        N = nums.size();
        startStart = 0;
        startEnd = -2;
        int end = searchEnd(nums,0,N-1,target);
        if( end == -1 ) return {-1,-1};
        int start = searchStart(nums,startStart,startEnd,target);
        if( start == -1 ) return {startEnd+1,end};
        return {start,end};
    }
};
