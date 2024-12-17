
// 3371. Identify the Largest Outlier in an Array
// https://leetcode.com/problems/identify-the-largest-outlier-in-an-array/




class Solution {
public:
    int getLargestOutlier(vector<int>& nums) {
        int n = nums.size(); // 3 <= nums.length <= 1e5

        sort(nums.begin(), nums.end());

        int sum = 0;
        unordered_map<int, vector<int>> val_positions;
        for(int i = 0; i < n; ++i) {
            val_positions[nums[i]].push_back(i);
            sum += nums[i];
        }


        for(int i = n-1; i >= 0; --i) {     // outlier candidate
            int sum_minus_outlier = sum - nums[i];

            /*
            // brute force
            for(int j = n-1; j >= 0; --j) { // sum candidate
                if( j == i )
                    continue;

                if( sum_minus_outlier - nums[j] == nums[j] ) // sum_minus_outlier == 2 * nums[j]
                    return nums[i];
            }
            */

            if( sum_minus_outlier % 2 == 0 ) {
                auto f = val_positions.find(sum_minus_outlier/2);
                if( f != val_positions.end() && (f->second.size() > 1 || f->second[0] != i) )
                    return nums[i];
            }
        }

        return -9999; // we should never get here
    }
};
