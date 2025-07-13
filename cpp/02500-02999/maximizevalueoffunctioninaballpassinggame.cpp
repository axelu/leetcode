
// 2836. Maximize Value of Function in a Ball Passing Game
// https://leetcode.com/problems/maximize-value-of-function-in-a-ball-passing-game/





/* from the hints: binary lifting
 *     https://cp-algorithms.com/graph/lca_binary_lifting.html
 *     https://www.geeksforgeeks.org/binary-lifting-guide-for-competitive-programming/
 *
 *
 */
class Solution {
public:
    long long getMaxFunctionValue(vector<int>& receiver, long long k) {

        // we are basically looking for the kth ancestor
        // from each node, there is only one outgoing edge

        int n = receiver.size();        // 1 <= receiver.length == n <= 1e5
        int i_mx = ceil(log2(k));       // 1 <= k <= 1e10  -> 0 <= i_mx <= 34
        // cout << "i_mx " << i_mx << endl;

        vector<vector<int>> last_receiver(n, vector<int>(i_mx + 1, -1));
        vector<vector<long long>> sum(n, vector<long long>(i_mx + 1, 0LL));

        // init
        // 1 pass
        for(int x = 0; x < n; ++x) { // player
            last_receiver[x][0] = receiver[x];
            sum[x][0] = receiver[x];
        }

        for(int i = 1; i <= i_mx; ++i) { // 2^i passes
            for(int x = 0; x < n; ++x) { // player
                last_receiver[x][i] = last_receiver[last_receiver[x][i - 1]][i - 1];
                sum[x][i] = sum[x][i - 1] + sum[last_receiver[x][i - 1]][i - 1];
            }
        }

        long long ans = 0;

        for(int x = 0; x < n; ++x) { // player
            long long t = x;
            // cout << "starting from player " << x << endl;
            int player = x;
            for(int i = i_mx; i >= 0; --i) { // 2^i passes
                if( k & (1LL << i) ) {
                    t += sum[player][i];
                    player = last_receiver[player][i];
                }
            }
            ans = max(ans, t);
        }

        return ans;
    }
};
