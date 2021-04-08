
// 1150. Check If a Number Is Majority Element in a Sorted Array
// https://leetcode.com/problems/check-if-a-number-is-majority-element-in-a-sorted-array/



class Solution {
private:
    size_t N;

    // binary search
    pair<int,int> search(vector<int>& nums, int& target, int s, int e) {
        if( s > e ) return make_pair(-1,-1);

        int mid = s + ((e - s)/2);
        if( nums[mid] == target ) {
            // determine low and high idx could also be done via binary search
            // but constraint 1 <= nums.length <= 1000, doing it this way is good enough
            // determine low idx
            int l = mid;
            for(; l >=0; --l)
                if( nums[l] != target ) break;
            ++l;
            // determine high idx
            int r = mid;
            for(; r < N; ++r)
                if( nums[r] != target ) break;
            --r;
            return make_pair(l,r);
        } else if( nums[mid] > target ) {
            return search(nums,target,s,mid-1);
        } else {
            // nums[mid] < target
            return search(nums,target,mid+1,e);
        }
    }
public:
    bool isMajorityElement(vector<int>& nums, int target) {
        N = nums.size();
        if( 1 == N ) return nums[0] == target;

        pair<int,int> p = search(nums,target,0,N-1);
        return p.second-p.first+1 > N/2;
    }
};
