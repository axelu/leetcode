
// 154. Find Minimum in Rotated Sorted Array II
// https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/



class Solution {
private:
    // binary search min in rotated sorted array with unique values
    int search(vector<int>& nums, int n, int s, int e) {
        // returns index of min element

        int mid = s+((e-s)/2);

        if( nums[mid] < nums[n-1] ) {
            int l = mid == 0 ? -5001 : nums[mid-1];
            if( l > nums[mid] ) return mid;
            return search(nums,n,s,mid-1);
        }
        return search(nums,n,mid+1,e);
    }
public:
    int findMin(vector<int>& nums) {
        int n = nums.size();

        if( n == 1 ) return nums[0];
        if( n == 2 ) return nums[0] < nums[1] ? nums[0] : nums[1];


        // eliminate dups
        if( nums[0] == nums[n-1] ) {
            while(nums.size() > 1 && nums[0] == nums.back() )
                nums.pop_back();
            if( nums.size() == 1 )
                return nums[0];
        }
        vector<int> v;
        v.push_back(nums[0]);
        for(int i = 1; i < nums.size(); ++i)
            if( nums[i] != nums[i-1] )
                v.push_back(nums[i]);
        n = v.size();


        if( n == 3 ) {
            if( v[0] < v[1] && v[0] < v[2] ) {
                return v[0];
            } else if( v[1] < v[0] && v[1] < v[2] ) {
                return v[1];
            } else {
                return v[2];
            }
        }

        if( v[0]   > v[1]   ) return v[1];   // rotated 1 time
        if( v[0]   < v[n-1] ) return v[0];   // already sorted
        if( v[n-2] > v[n-1] ) return v[n-1]; // rotate n-1 times

        return v[search(v,v.size(),0,v.size()-1)];
    }
};
