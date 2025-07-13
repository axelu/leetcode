
// 3603. Minimum Cost Path with Alternating Directions II
// https://leetcode.com/problems/minimum-cost-path-with-alternating-directions-ii/


class Solution {
public:
    long long minCost(int m, int n, vector<vector<int>>& waitCost) {

        vector<vector<long long>> A(m, vector<long long>(n, LLONG_MAX));

        // {cost, i, j, odd/even second}
        auto cmp = [](const vector<long long>& a, const vector<long long>& b){
            return a[0] > b[0];
        };
        priority_queue<vector<long long>, vector<vector<long long>>, decltype(cmp)> pq(cmp);
        pq.push({1, 0, 0, 1});
        while( !pq.empty() ) {
            long long cost = pq.top()[0];
            int i = pq.top()[1]; // row
            int j = pq.top()[2]; // col
            int s = pq.top()[3]; // 0 even second, 1 odd second
            pq.pop();

            if( i == m-1 && j == n-1 )
                return cost;

            if( s == 0 ) {
                // we have to incur wait cost
                cost += (long long)waitCost[i][j];
            }
            // really only on cell 0,0 we don't pay wait cost
            int s_new = s == 1 ? 0 : 0;

            // go down if we can
            int i_new = i + 1;
            int j_new = j;
            if( i_new < m ) {
                // entry cost
                long long entry_cost = (long long)(i_new + 1) * (long long)(j_new + 1);
                long long cost_new = cost + entry_cost;
                if( A[i_new][j_new] > cost_new ) {
                    A[i_new][j_new] = cost_new;
                    pq.push({cost_new, i_new, j_new, s_new});
                }
            }
            // go right if we can
            i_new = i;
            j_new = j + 1;
            if( j_new < n ) {
                // entry cost
                long long entry_cost = (long long)(i_new + 1) * (long long)(j_new + 1);
                long long cost_new = cost + entry_cost;
                if( A[i_new][j_new] > cost_new ) {
                    A[i_new][j_new] = cost_new;
                    pq.push({cost_new, i_new, j_new, s_new});
                }
            }
        }

        return -1LL; // satisfy compiler
    }
};
