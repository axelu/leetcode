
// 1064. Fixed Point
// https://leetcode.com/problems/fixed-point/



class Solution {
private:
    int ans;

    // binary search
    void search(vector<int>& arr, int s, int e) {
        if( s > e ) return;

        int mid = s + ((e - s)/2);
        if( arr[mid] == mid ) ans = mid;
        if( arr[mid] >= mid ) {
            search(arr,s,mid-1);
        } else {
            search(arr,mid+1,e);
        }
    }

public:
    int fixedPoint(vector<int>& arr) {
        int n = arr.size();
        if( n == 1 ) return arr[0] == 0 ? 0 : -1;

        ans = -1;
        search(arr,0,n-1);
        return ans;
    }
};
