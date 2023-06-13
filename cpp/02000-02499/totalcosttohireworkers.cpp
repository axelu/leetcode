
// 2462. Total Cost to Hire K Workers
// https://leetcode.com/problems/total-cost-to-hire-k-workers/





class Solution {
public:
    long long totalCost(vector<int>& costs, int k, int candidates) {
        int n = costs.size();

        // array<int,2> = {cost,index}
        auto cmp = [](const array<int,2>& a, const array<int,2>& b) {
            if( a[0] > b[0] ) {
                return true;
            } else if( a[0] == b[0] ) {
                if( a[1] > b[1] ) {
                    return true;
                }
            }
            return false;
        };
        priority_queue<array<int,2>,vector<array<int,2>>,decltype(cmp)> pq_lft(cmp);
        priority_queue<array<int,2>,vector<array<int,2>>,decltype(cmp)> pq_rgt(cmp);

        // fill left and right, don't let indicies cross
        int idx_lft = 0;
        for(; idx_lft < candidates; ++idx_lft) {
            pq_lft.push({costs[idx_lft],idx_lft});
        }
        // all candidates up to and including idx_lft-1 have been added

        int idx_rgt = n-1;
        for(; idx_rgt >= max(idx_lft,n-candidates); --idx_rgt) {
            pq_rgt.push({costs[idx_rgt],idx_rgt});
        }


        long long ans = 0;

        for(int i = 0; i < k; ++i) {

            while( pq_lft.size() < candidates && idx_lft <= idx_rgt ) {
                pq_lft.push({costs[idx_lft],idx_lft});
                ++idx_lft;
            }

            while( pq_rgt.size() < candidates && idx_rgt >= idx_lft ) {
                pq_rgt.push({costs[idx_rgt],idx_rgt});
                --idx_rgt;
            }

            // index in left queue will always be lower than index in right queue

            if( !pq_lft.empty() && !pq_rgt.empty() ) {
                if( pq_lft.top()[0] < pq_rgt.top()[0] ) {
                    ans += pq_lft.top()[0];
                    pq_lft.pop();

                } else if( pq_lft.top()[0] > pq_rgt.top()[0] ) {
                    ans += pq_rgt.top()[0];
                    pq_rgt.pop();

                } else { // pq_lft.top()[0] == pq_rgt.top()[0]
                    ans += pq_lft.top()[0];
                    pq_lft.pop();
                }

            } else if( !pq_lft.empty() ) {
                ans += pq_lft.top()[0];
                pq_lft.pop();

            } else { // !pg_rgt.empty()
                ans += pq_rgt.top()[0];
                pq_rgt.pop();
            }
        }

        return ans;
    }
};
