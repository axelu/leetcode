
// 3275. K-th Nearest Obstacle Queries
// https://leetcode.com/problems/k-th-nearest-obstacle-queries/





class Solution {
public:
    vector<int> resultsArray(vector<vector<int>>& queries, int k) {

        priority_queue<int> pq;

        vector<int> ans;

        for(auto& q: queries) {
            int x = q[0];
            int y = q[1];

            int dist = abs(x) + abs(y);

            if( pq.size() < k - 1 ) {
                pq.push(dist);
                ans.push_back(-1);
                continue;
            }

            if( pq.size() < k ) {
                pq.push(dist);

            } else if( dist < pq.top() ) {
                pq.push(dist);
            }

            if( pq.size() > k )
                pq.pop();

            ans.push_back(pq.top());
        }

        return ans;
    }
};
