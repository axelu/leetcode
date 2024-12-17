
// 3362. Zero Array Transformation III
// https://leetcode.com/problems/zero-array-transformation-iii/





class Solution {
public:
    int maxRemoval(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();

        // we will sort queries by start
        sort(queries.begin(), queries.end(), [](const vector<int>& a, const vector<int>& b){
            if( a[0] < b[0] ) {
                return true;
            } else if( a[0] == b[0] ) {
                if( a[1] > b[1] ) {
                    return true;
                }
            }
            return false;
        });


        vector<int> line(n+1, 0);
        int h = 0;

        auto cmp = [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        };
        priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> pq(cmp);

        int q_idx = 0;
        int q_sz = queries.size();
        int queries_applied = 0;
        for(int i = 0; i < n; ++i) {
            h += line[i];

            // grab all queries starting at the current index
            while( q_idx < q_sz && queries[q_idx][0] == i )
                pq.push(queries[q_idx++]);

            if( nums[i] > h ) {
                // we must apply queries
                // we greedily apply queries that cover the widest range to our right
                while( nums[i] > h && !pq.empty() && pq.top()[1] >= i ) {
                    ++h;
                    --line[pq.top()[1] + 1];
                    pq.pop();
                    ++queries_applied;
                }
                if( nums[i] > h )
                    return -1;
            }
        }

        return q_sz - queries_applied;
    }
};
