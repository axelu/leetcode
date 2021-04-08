
// 852. Peak Index in a Mountain Array
// https://leetcode.com/problems/peak-index-in-a-mountain-array/



class Solution {
private:
    int N;

    // binary search
    int search(vector<int>& arr, int s, int e) {
        // cout << "s " << s << " e " << e << endl;
        if( s > e ) return -1;

        int mid = s + ((e - s)/2);
        if( mid == 0 ) mid = 1;
        else if( mid == N-1 ) mid = N-2;
        // cout << "mid " << mid << endl;

        int l = arr[mid-1];
        int m = arr[mid];
        int r = arr[mid+1];
        if( l < m && m > r ) return mid;

        if( l > m )
            return search(arr,s,mid-1);
        return search(arr,mid+1,e);
    }

public:
    int peakIndexInMountainArray(vector<int>& arr) {
        N = arr.size();
        if( N == 3 ) return 1;

        return search(arr,0,N-1);
    }
};
