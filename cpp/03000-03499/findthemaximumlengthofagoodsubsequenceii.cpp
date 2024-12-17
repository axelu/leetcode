
// 3177. Find the Maximum Length of a Good Subsequence II
// https://leetcode.com/problems/find-the-maximum-length-of-a-good-subsequence-ii/





class Solution {
private:
    void maintain_mx(array<int,4> mx[], int k, int l, int x) {
        // array<int,4> mx[k]; // mx ,val, 2ndmx, 2nd val
        // cout << "maintain_mx k " << k << " l " << l << " x " << x << endl;

        if( l > mx[k][0] && mx[k][1] == x ) {
            mx[k][0] = l;
            return;
        }

        if( l > mx[k][0] && mx[k][1] != x ) {

            mx[k][2] = mx[k][0];
            mx[k][3] = mx[k][1];

            mx[k][0] = l;
            mx[k][1] = x;

            return;
        }

        if( l > mx[k][2] ) {
            mx[k][2] = l;
            mx[k][3] = x;
            return;
        }

        return;
    }

public:
    int maximumLength(vector<int>& nums, int k) {
        // 1 <= nums.length <= 5000
        // 0 <= k <= min(nums.length, 50)

        int n = nums.size();

        if( k == n )
            return k;

        if( k == 0 ) {
            unordered_map<int,int> freq; // val, count
            int mx_freq = 0;
            for(int x: nums)
                mx_freq = max(mx_freq, ++freq[x]);
            return mx_freq;
        }

        // the values of nums[i] don't matter in regards to their value
        // it only matters to identify if same value or not at given positions
        // at each index we have a choice:
        //    continue from an index with the same value not incurring cost (aka k) OR
        //    continue from an index with a different value incurring cost
        // so we can go through nums from left to right and from 0...k
        // we either continue from the same value adding 1 to our length OR
        // we invest 1 (aka k-1) and continue from longest length so far from a different value

        // remap values in nums
        unordered_map<int,int> um;
        int idx = 0;
        for(int i = 0; i < n; ++i) {
            int x = nums[i];
            auto p = um.insert({x,idx});
            if( p.second ) {
                nums[i] = idx;
                ++idx;
            } else {
                nums[i] = p.first->second;
            }
        }

        // debug
        /*
        for(int i = 0; i < n; ++i)
            cout << nums[i] << " ";
        cout << endl;
        */

        int dp[idx][k+1];memset(dp,0,sizeof dp);

        // maintain max and 2nd max length for different for 2 different values
        // as we need to have max for a value different than at the current value at the current index
        // we will always find that by maintaining only two
        array<int,4> mx[k+1]; // mx ,val, 2ndmx, 2nd val
        // init with 0,-1,0,-1
        for(int j = 0; j <= k; ++j)
            mx[j] = {0,-1,0,-1};

        for(int i = 0; i < n; ++i) {
            int x = nums[i];

            // k = 0
            ++dp[x][0];

            // maintain max
            maintain_mx(mx, 0, dp[x][0], x);

            for(int j = 1; j <= k; ++j) {

                // continue from an index with the same value for no cost
                int a = dp[x][j] + 1;

                // continue from an index with a different value for cost of 1 aka k-1
                // we continue from different value with max length
                /*
                int b = 1;
                for(int val = 0; val < idx; ++val) {
                    if( val == x )
                        continue;
                    b = max(b, dp[val][j-1] + 1);
                }
                */
                int b = mx[j-1][1] != x ? mx[j-1][0] + 1: mx[j-1][2] + 1;


                dp[x][j] = max(a, b);

                // maintain mx
                maintain_mx(mx, j, dp[x][j], x);
            }

        }

        // ans max dp[x][k] for 0 <= x < idx
        int ans = 0;
        for(int x = 0; x < idx; ++x)
            ans = max(ans, dp[x][k]);

        return ans;

    }
};
