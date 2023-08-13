
// 2653. Sliding Subarray Beauty
// https://leetcode.com/problems/sliding-subarray-beauty/



class Solution {
public:
    vector<int> getSubarrayBeauty(vector<int>& nums, int k, int x) {
        int n = nums.size();

        vector<int> ans(n-k+1,0);

        multiset<int> ms;
        auto it = ms.end();

        int i = 0;
        for(int j = 0; j < n; ++j) {
            if( nums[j] < 0 ) {
                ms.insert(nums[j]);
                if( it != ms.end() && nums[j] < *it ) {
                    --it;
                }
                if( it == ms.end() && ms.size() == x )
                   --it;
            }

            if( j-i+1 == k ) {
                if( it != ms.end() )
                    ans[i] = *it;

                if( nums[i] < 0 ) {
                    if( it != ms.end() ) {
                        if( nums[i] <= *it ) {
                            ++it;
                        }
                    }
                    ms.erase(ms.find(nums[i]));
                }
                ++i;
            }
        }

        return ans;
    }
};
