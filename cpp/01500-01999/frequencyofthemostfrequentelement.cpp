
// 1838. Frequency of the Most Frequent Element
// https://leetcode.com/problems/frequency-of-the-most-frequent-element/


class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        int n = nums.size();

        sort(nums.begin(),nums.end());

        long ans = 0;

        // sliding window

        int i = 0;  // right index;
        long l;     // lenfth of window
        long s = 0; // sum of elements in the window
        long p = 0; // l * nums[j]
        for(int j = 0; j < n; ++j) {
            l = j - i + 1;
            s += nums[j];
            p = l * nums[j];
            if( p - s <= k ) {
                ans = max(ans,l);
            } else {
                while( p - s > k ) {
                    s -= nums[i];
                    ++i;
                    p -= nums[j];
                }
            }
        }

        return ans;
    }
};
