
// 1300. Sum of Mutated Array Closest to Target
// https://leetcode.com/problems/sum-of-mutated-array-closest-to-target/



class Solution {

    int solve(vector<int>& arr, int prefixSum[], int n, int value) {
        // arr is sorted

        // returns 'n' if nums[n-1] <= target
        // returns  0  if nums[0] > target
        // binary search upper bound while loop
        // upper bound -> greater than target
        int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( value >= arr[mid] )
                s = mid + 1;
            else
                e = mid;
        }
        if( s < n && arr[s] <= value )
            ++s;

        return prefixSum[s] + (n-s) * value;
    }

public:
    int findBestValue(vector<int>& arr, int target) {
        int n = arr.size();

        sort(arr.begin(),arr.end());
        int prefixSum[n+1];
        prefixSum[0] = 0;
        for(int i = 0; i < n; ++i)
            prefixSum[i+1] = prefixSum[i] + arr[i];

        if( prefixSum[n] <= target )
            return arr.back();

        // our ans is between 0 and mx inclusive
        // binary search closest to target
        int s = 0;
        int e = arr.back();
        int mid,t,tl,tr;
        while(s <= e) {

            mid = s + ((e-s)/2);
            t = solve(arr,prefixSum,n,mid);

            if( t == target ) {
                return mid;

            } else if( t > target ) {

                if( mid > 0 ) {
                    tl = solve(arr,prefixSum,n,mid-1);
                    if( target > tl ) {
                        if( target-tl > t-target)
                                return mid;
                            else
                                return mid-1;
                    }
                }

                // go to left
                e = mid-1;

            } else {

                if( mid < e ) {
                    tr = solve(arr,prefixSum,n,mid+1);
                    if( target < tr ) {
                        if( target-t > tr-target)
                                return mid+1;
                            else
                                return mid;
                    }
                }

                // go to right
                s = mid + 1;
            }
        }

        return mid;
    }
};
