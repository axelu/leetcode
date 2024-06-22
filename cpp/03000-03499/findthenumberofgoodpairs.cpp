
// 3162. Find the Number of Good Pairs I
// https://leetcode.com/problems/find-the-number-of-good-pairs-i/





class Solution {
public:
    int numberOfPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        int m = nums1.size(); // 1 <= m <= 50
        int n = nums2.size(); // 1 <= n <= 50

        int ans = 0;

        // brute force
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                if( nums1[i] % (nums2[j] * k) == 0 )
                    ++ans;

        return ans;
    }
};
