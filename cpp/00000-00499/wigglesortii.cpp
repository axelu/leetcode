
// 324. Wiggle Sort II
// https://leetcode.com/problems/wiggle-sort-ii/



class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return;

        sort(nums.begin(),nums.end());
        vector<int> t(n); // temp

        int j = n-1;

        // distribute from right to left
        // to every second position starting at idx 1
        int i = 1;
        while(i < n) {
            t[i] = nums[j];
            i += 2;
            --j;
        }

        // continue to distribute from right to left
        // to every second position starting at idx 0
        i = 0;
        while(i < n) {
            t[i] = nums[j];
            i += 2;
            --j;
        }

        // copy
        for(i = 0; i < n; ++i)
            nums[i] = t[i];
    }
};
