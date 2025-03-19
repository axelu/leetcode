
// 3400. Maximum Number of Matching Indices After Right Shifts
// https://leetcode.com/problems/maximum-number-of-matching-indices-after-right-shifts/description/





class Solution {
private:
    int matches(vector<int>& nums1, vector<int>& nums2, int offset) {
        int n = nums1.size(); // nums1.size() == nums2.size()

        int ret = 0;
        for(int i = 0; i < n; ++i) {    // pos in nums1
            int j = (i + offset) % n;   // pos in nums2
            if( nums1[i] == nums2[j] )
                ++ret;
        }

        return ret;
    }

public:
    int maximumMatchingIndices(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(); // nums1.size() == nums2.size()

        // as we can shift any number of times, we can wrap around,
        // which could with that also be a left shift
        // example nums1 = [7,8,1,2,3,4], nums2 = [1,2,3,4,5,6]
        //         ans = 4

        // for each value in nums2, collect the positions
        // iterate through nums1
        // for each value in nums1, find the positions of matching values in nums2
        // calculate the offset and count matches if we would shift nums1 by that offset
        // we can remember if we already investigated a given offset so we don't repeat

        unordered_map<int, vector<int>> um;
        for(int i = 0; i < n; ++i)
            um[nums2[i]].push_back(i);

        int ans = 0;

        vector<bool> seen(n,false);
        for(int i = 0; i < n; ++i) {
            auto f = um.find(nums1[i]);
            if( f != um.end() ) {
                for(auto it = f->second.begin(); it != f->second.end(); ++it) {
                    int j = *it;
                    int offset = j >= i ? j-i : n - (i-j);
                    if( seen[offset] )
                        continue;
                    seen[offset] = true;
                    ans = max(ans, matches(nums1, nums2, offset));
                }
            }
        }

        return ans;
    }
};
