
// 3555. Smallest Subarray to Sort in Every Sliding Window
// https://leetcode.com/problems/smallest-subarray-to-sort-in-every-sliding-window/



class Solution {
public:
    vector<int> minSubarraySort(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> ans(n-k+1,0);

        if( k == 1 )
            return ans;

        multiset<int> ms;
        ms.insert(nums[0]);

        int i = 0;
        for(int j = 1; j < n; ++j) {
            int val = nums[j];
            ms.insert(val);

            if( j - i + 1 == k ) {

                // find the left most difference
                // between sorted and nums for the
                // current window
                auto it = ms.begin();
                int l = i;
                for(; l < j; ++l) {
                    if( *it != nums[l] )
                        break;
                    ++it;
                }
                if( l < j ) {
                    // find the right mode difference
                    auto itr = ms.rbegin();
                    int r = j;
                    for(; r > i; --r) {
                        if( *itr != nums[r] )
                            break;
                        ++itr;
                    }

                    ans[i] = r-l+1; // should never be one
                }

                auto f = ms.find(nums[i]);
                ms.erase(f);
                ++i;
            }
        }

        return ans;
    }
};
