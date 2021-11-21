
// 280. Wiggle Sort
// https://leetcode.com/problems/wiggle-sort/




class Solution {
private:
    void swap(vector<int>& nums, int a, int b) {
        int t = nums[a];
        nums[a] = nums[b];
        nums[b] = t;
    }
public:
    void wiggleSort(vector<int>& nums) {
        int n = nums.size();

        // single traversal of every other element
        for(int i = 1; i < n; i += 2) {

            // if current current element is smaller than prev
            if( i > 0 && nums[i-1] > nums[i] )
                swap(nums,i,i-1);

            // if current current element is smaller than next
            if( i < n-1 && nums[i] < nums[i+1] )
                swap(nums,i,i+1);

        }
    }
};
