
// 2815. Max Pair Sum in an Array
// https://leetcode.com/problems/max-pair-sum-in-an-array/




class Solution {
private:
    int get_max_digit(int x) {
        int max_digit = 0;
        while( x > 0 ) {
            int rem = x % 10;
            max_digit = max(max_digit, rem);
            x /= 10;
        }
        return max_digit;
    }

public:
    int maxSum(vector<int>& nums) {
        // 2 <= nums.length <= 100 small constraint, brute force

        vector<int> v[10]; // v[k] numbers with max digit k
        for(int x: nums)
            v[get_max_digit(x)].push_back(x);

        int ans = -1;
        for(auto vi: v) {
            int n = vi.size();
            for(int i = 0; i < n-1; ++i) {
                for(int j = i+1; j < n; ++j) {
                    ans = max(ans, vi[i] + vi[j]);
                }
            }
        }

        return ans;
    }
};
