
// 162. Find Peak Element
// https://leetcode.com/problems/find-peak-element/




class Solution {
private:
    // binary search
    int search(vector<int>& nums, int n, int s, int e) {
        // cout << "s " << s << " e " << e << endl;

        int mid = s + ((e-s)/2);
        // cout << "mid " << mid << endl;

        long l = mid == 0 ? -2147483649 : nums[mid-1];
        long m = nums[mid];
        long r = mid == n-1 ? -2147483649 : nums[mid+1];

        if( m > l && m > r ) {          // peak
            return mid;
        } else if( l < m && m < r ) {   // ascending  -> go to right
            return search(nums,n,mid+1,e);
        } else if( l > m && m > r ) {   // descending -> go to left
            return search(nums,n,s,mid-1);
        } else {                        // valey -> go to either left of right
            if( mid-s < e-mid ) {
                return search(nums,n,s,mid-1);
            } else {
                return search(nums,n,mid+1,e);
            }
        }
    }
public:
    int findPeakElement(vector<int>& nums) {
        int n = nums.size();

        if( n == 1 ) return 0;

        if( n == 2 ) return nums[0] > nums[1] ? 0 : 1;

        if( n == 3 ) {
            if( nums[1] > nums[0] && nums[1] > nums[2] ) {
                return 1;
            } else {
                return nums[0] > nums[2] ? 0 : 2;
            }
        }

        if(   nums[0] > nums[1]   ) return 0;
        if( nums[n-1] > nums[n-2] ) return n-1;

        return search(nums,n,0,n-1);
    }
};
