
// 3540. Minimum Time to Visit All Houses
// https://leetcode.com/problems/minimum-time-to-visit-all-houses/





// at the time of this writing, the problem description is wrong
// it reads:   "... house 0 is connected back to house n - 1 via a road with length backward[n - 1] metres, ..."
// it should read: "... house 0 is connected back to house n - 1 via a road with length backward[0] metres, ..."

class Solution {
public:
    long long minTotalTime(vector<int>& forward, vector<int>& backward, vector<int>& queries) {
        int n = forward.size(); // forward.size() == backward.size(), 2 <= n <= 1e5

        // forward index        0        1        2        3        ...      n-1      n
        // dist house from..to  0..1     1..2     2..3     3..4     ...      n-1..0   ----
        // prefixSum_fw         0        0..1     0..2     0..3     ...      0..n-1   0..0

        // backward index       0        1        2        3        ...      n-1      n
        // dist house from..to  0..n-1   1..0     2..1     3..2     ...      n-1..n-2 ----
        // let us stick index 0 to the end
        // backward index       0        1        2        3        ...      n-1      n
        // dist house from..to  1..0     2..1     3..2     ...      n-1..n-2 0..n-1
        // prefixSum_bw         0        1..0     2..0     3..0     ...      n-1..0   0..0

        long long prefixSum_fw[100001];
        prefixSum_fw[0] = 0LL;
        for(int i = 1; i <= n; ++i)
            prefixSum_fw[i] = prefixSum_fw[i-1] + (long long)forward[i-1];

        long long prefixSum_bw[100001];
        prefixSum_bw[0] = 0LL;
        for(int i = 1; i <= n; ++i) {
            if( i == n )
                prefixSum_bw[i] = prefixSum_bw[i-1] + (long long)backward[0];
            else
                prefixSum_bw[i] = prefixSum_bw[i-1] + (long long)backward[i];
        }

        long long ans = 0;
        int curr = 0; // we are starting at house 0

        int q_sz = queries.size();
        // queries[i] != queries[i + 1]
        // queries[0] is not 0.
        for(int i = 0; i < q_sz; ++i) {
            int dest = queries[i];

            // we are house curr
            // we need to move to dest
            // we either move clockwise aka forward OR
            // we move counter clockwise aka backward

            // clockwise aka forward
            long long a;
            if( curr < dest ) {
                // our dest is right of us
                // going forward we do not cross the end
                a = prefixSum_fw[dest] - prefixSum_fw[curr];
            } else {
                // our dest is left of us
                // going forward we will cross the end
                long long curr_to_zero = prefixSum_fw[n] - prefixSum_fw[curr];
                long long zero_to_dest = prefixSum_fw[dest];
                a = curr_to_zero + zero_to_dest;
            }

            // counter clockwise aka backward
            long long b;
            if( curr < dest ) {
                // our dest is right of us
                // going backward we cross the end
                long long curr_to_zero = prefixSum_bw[curr];
                long long zero_to_dest = prefixSum_bw[n] - prefixSum_bw[dest];
                b = curr_to_zero + zero_to_dest;
            } else {
                // our dest is left of us
                // going backward we do not cross the end
                b = prefixSum_bw[curr] - prefixSum_bw[dest];
            }

            ans += min(a,b);
            curr = dest;
        }

        return ans;
    }
};
