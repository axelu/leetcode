
// 3068. Find the Maximum Sum of Node Values
// https://leetcode.com/problems/find-the-maximum-sum-of-node-values/





/* take a tree rooted in node A with three children as an example
 *             A
 *           / | \
 *         B   C   D
 * we observe that if the number of 'flipped' child nodes is odd, the parent is also flipped
 *             A'
 *           / | \
 *         B'  C   D
 * or
 *             A
 *           / | \
 *         B'  C'  D
 * or
 *             A'
 *           / | \
 *         B'  C'  D'
 * or
 *             A'
 *           / | \
 *         B   C'  D
 * and so on
 */
class Solution {
private:
    long long mem[20000][2];

    long long rec(vector<int>& nums, vector<int> t[], int u, int src, int flipped, int k) {
        long long val = flipped ? nums[u] ^ k : nums[u];
        if( u != 0 && t[u].size() == 1 )
            return val;

        if( mem[u][flipped] != LLONG_MIN )
            return mem[u][flipped];

        // let us greedily take the larger configuration of each child
        // keep track of how many we take that are flipped and keep track of the one with the smallest gain
        long long min_gain = LLONG_MAX;
        int min_gain_child_idx;
        int nbr_flipped = 0;
        long long sum = 0LL;

        for(int i = 0; i < t[u].size(); ++i) {
            int v = t[u][i];
            if( v == src )
                continue;

            long long flipped = rec(nums, t, v, u, 1, k);
            long long not_flipped = rec(nums, t, v, u, 0, k);

            if( flipped >= not_flipped ) {
                sum += flipped;
                ++nbr_flipped;
            } else {
                sum += not_flipped;
            }

            long long gain = abs(flipped - not_flipped);
            if( gain < min_gain ) {
                min_gain = gain;
                min_gain_child_idx = i;
            }
        }

        long long a, b;

        if( nbr_flipped % 2 ) {
            // we need to flip u
            a = (val ^ k) + sum;
            // or we forgo the smallest gain
            b = val + sum - min_gain;
        } else {
            a = val + sum;
            b = (val ^ k) + sum - min_gain;
        }

        return mem[u][flipped] = max(a, b);
    }

public:
    long long maximumValueSum(vector<int>& nums, int k, vector<vector<int>>& edges) {
        int n = nums.size();
        vector<int> t[n];
        for(auto& edge: edges) {
            t[edge[0]].push_back(edge[1]);
            t[edge[1]].push_back(edge[0]);
        }

        for(int i = 0; i < n; ++i) {
            mem[i][0] = LLONG_MIN;
            mem[i][1] = LLONG_MIN;
        }

        // arbitrarily root the tree in node 0
        return rec(nums, t, 0, -1, 0, k);
    }
};
