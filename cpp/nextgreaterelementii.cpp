
// 503. Next Greater Element II
// https://leetcode.com/problems/next-greater-element-ii/


class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        size_t n = nums.size();
        if( n == 0 ) return {};
        if( n == 1 ) return {-1};

        vector<int> ans(n);
        // brute force
        int k;
        bool f;
        for(int i = 0; i < n; ++i) {
            k = nums[i];
            ans[i] = -1;
            if( i == 0 ) {
                for(int j = 1; j < n; ++j)
                    if( nums[j] > k ) {
                        ans[i] = nums[j];
                        break;
                    }
            } else if( i == n-1 ) {
                for(int j = 0; j < n-1; ++j)
                    if( nums[j] > k ) {
                        ans[i] = nums[j];
                        break;
                    }
            } else {
                f = false;
                for(int j = i+1; j < n; ++j)
                    if( nums[j] > k ) {
                        ans[i] = nums[j];
                        f = true;
                        break;
                    }
                if( !f ) {
                    for(int j = 0; j < i; ++j)
                        if( nums[j] > k ) {
                            ans[i] = nums[j];
                            break;
                        }
                }
            }
        }

        /*
        for(int i = 0; i < n; ++i) {
            ans[i] = -1;
            for(int j = 1; j < n; ++j) {
                if( nums[(i + j) % n] > nums[i] ) {
                    ans[i] = nums[(i + j) % n];
                    break;
                }
            }
        }*/

        return ans;
    }
};
