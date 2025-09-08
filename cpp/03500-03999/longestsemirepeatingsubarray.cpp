
// 3641. Longest Semi-Repeating Subarray
// https://leetcode.com/problems/longest-semi-repeating-subarray/






class Solution {
private:
    bool solve(vector<int>& nums, int l, int k) {
        // returns true if a window of size l
        // can be slid accross nums in which
        // at most k element repeat, false otherwise

        int n = nums.size();
        // int freq[100001];memset(freq,0,sizeof freq);
        vector<int> freq(100001,0);
        int repeats = 0;
        int i = 0;                   // left index
        for(int j = 0; j < n; ++j) { // right index
            int val = nums[j];
            ++freq[val];
            if( freq[val] == 2 )
                ++repeats;

            if( j - i + 1 == l ) {
                if( repeats <= k )
                    return true;

                val = nums[i];
                --freq[val];
                if( freq[val] == 1 )
                    --repeats;
                ++i;
            }
        }

        return false;
    }

    // binary search
    int search(vector<int>& nums, int s, int e, int k) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        bool f = solve(nums, mid, k);
        if( f ) {
            // can we do better?
            int t = search(nums, mid+1, e, k);
            return t != -1 ? t : mid;
        }
        return search(nums, s, mid-1, k);
    }

public:
    int longestSubarray(vector<int>& nums, int k) {
        int n = nums.size();

        return search(nums, 1, n, k);
    }
};
