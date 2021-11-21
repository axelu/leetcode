
// 16. 3Sum Closest
// https://leetcode.com/problems/3sum-closest/
// day 27 July 2021 challenge
// https://leetcode.com/explore/challenge/card/july-leetcoding-challenge-2021/611/week-4-july-22nd-july-28th/3828/





class Solution {
private:
    // binary search closest element to target
    int search(vector<int>& arr, int s, int e, int target) {

        if( target <= arr[s] )
            return arr[s];
        if( target >= arr[e] )
            return arr[e];

        int i = s, j = e, mid = s;
        while(i < j) {

            mid = i + ((j-i)/2);

            if( arr[mid] == target ) {
                return arr[mid];

            } else if( arr[mid] > target ) {

                if( mid > 0 && target > arr[mid-1] ) {
                    // arr[mid-1] < target < arr[mid]
                    if( target-arr[mid-1] >= arr[mid]-target)
                            return arr[mid];
                        else
                            return arr[mid-1];

                }

                // go to left
                j = mid-1;

            } else {

                if( mid < e && target < arr[mid+1] ) {
                    // arr[mid] < target < arr[mid+1]
                    if( target-arr[mid] >= arr[mid+1]-target)
                            return arr[mid+1];
                        else
                            return arr[mid];
                }

                // go to right
                i = mid + 1;
            }
        }

        return arr[mid];
    }

public:
    int threeSumClosest(vector<int>& nums, int target) {
        int n = nums.size();

        if( n == 3 )
            return nums[0]+nums[1]+nums[2];


        sort(nums.begin(),nums.end());
        /*
        for(int i : nums)
            cout << i << " ";
        cout << endl;
        */


        int ans = 1000000;

        int t1,t2,x,p;
        for(int i = 0; i < n-2; ++i) {
            for(int j = i+1; j < n-1; ++j) {

                t1 = nums[i]+nums[j];
                x = target - t1;

                p = search(nums,j+1,n-1,x);
                if( p == x )
                    return target;

                t2 = t1+p;

                if( ans > target && t2 > target ) {
                    // current ans and p are to the right of target
                    ans = min(ans,t2);
                } else if( ans < target && t2 > target ) {
                    // current ans to the left and p to the right of target
                    if( target-ans >= t2-target )
                        ans = t2;
                } else if( t2 < target && ans > target ) {
                    // current ans to the right and p to the left of target
                    if( target-t2 <= ans-target )
                        ans = t2;
                } else {
                    // current ans and p are to the left of target
                    ans = max(ans,t2);
                }

            }
        }


        return ans;
    }
};
