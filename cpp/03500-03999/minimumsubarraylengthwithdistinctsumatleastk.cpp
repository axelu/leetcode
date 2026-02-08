
// 3795. Minimum Subarray Length With Distinct Sum At Least K
// https://leetcode.com/problems/minimum-subarray-length-with-distinct-sum-at-least-k/


class Solution {
private:
    bool solve(vector<int>& nums, int l, int k) {
        int n = nums.size();
        unordered_map<int,int> um; // key: val value: cnt
        // sliding window
        long long sum = 0LL;
        int i = 0;                   // left index
        for(int j = 0; j < n; ++j) { // right index
            ++um[nums[j]];
            if( um[nums[j]] == 1 ) {
                sum += (long long)nums[j];
                if( sum >= k )
                    return true;
            }

            if( j-i+1 == l ) {
                if( um[nums[i]] == 1 )
                    sum -= (long long)nums[i];
                --um[nums[i]];
                ++i;
            }
        }

        return false;
    }

    // binary search
    int search(int s, int e, vector<int>& nums, int k) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        if( solve(nums, mid, k) ) {
            // can we do better?
            int t = search(s, mid-1, nums, k);
            return t != -1 ? t : mid;
        }
        return search(mid+1, e, nums, k);
    }

public:
    int minLength(vector<int>& nums, int k) {
        int n = nums.size();
        return search(1, n, nums, k);
    }
};
