
// 2956. Find Common Elements Between Two Arrays
// https://leetcode.com/problems/find-common-elements-between-two-arrays/





class Solution {
private:

    int search(vector<int>& haystack, vector<int>& needles) {
        // searching for needles in haystack
        // values in haystack and needles: 1 <= val <= 100

        int found = 0;
        int seen[101];memset(seen,-1,sizeof seen);
        for(const auto needle : needles) {
            if( seen[needle] == -1 )
                seen[needle] = binary_search(haystack.begin(),haystack.end(),needle) ? 1 : 0;
            found += seen[needle];
        }

        return found;
    }

public:
    vector<int> findIntersectionValues(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(),nums1.end());
        sort(nums2.begin(),nums2.end());

        int a = search(nums2,nums1);
        int b = search(nums1,nums2);

        return {a,b};
    }
};
