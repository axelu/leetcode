
// Merge Sorted Array
// https://leetcode.com/problems/merge-sorted-array/


class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {

        if ( nums2.empty() || n == 0 ) return;

        // brute force: add and sort
        auto it1 = nums1.begin() + m;
        for(auto it2 = nums2.begin(); it2 != nums2.begin() + n; ++it2) {
            *it1 = *it2;
            ++it1;
        }
        sort(nums1.begin(),nums1.end(),[](int a, int b){
            return a<b;
        });
    }
};
