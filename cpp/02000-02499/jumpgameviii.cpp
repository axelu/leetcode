
// 2297. Jump Game VIII
// https://leetcode.com/problems/jump-game-viii/
// using Dijkstra



class Solution {
public:
    long long minCost(vector<int>& nums, vector<int>& costs) {
        int n = nums.size(); //  nums.length == costs.length
        if( n == 1 )
            return 0;

        // condition 1:
        //     nums[i] <= nums[j] and nums[k] < nums[i] for all indexes k in the range i < k < j
        // condition 2:
        //     nums[i] > nums[j] and nums[k] >= nums[i] for all indexes k in the range i < k < j

        unordered_set<int> g[n]; // directed graph TODO directed weighted graph

        stack<int> cond1; // monotonic increasing stack
        stack<int> cond2; // monotonic strictly decreasing stack
        for(int i = n-1; i >= 0; --i) {

            // cond 1
            while( !cond1.empty() && nums[cond1.top()] < nums[i] )
                cond1.pop();
            // what is left in cond1 are indexes j that we can jump to from i
            if( !cond1.empty() )
                g[i].insert(cond1.top());
            cond1.push(i);

            // cond 2
            while( !cond2.empty() && nums[cond2.top()] >= nums[i] )
                cond2.pop();
            // what is left in cond2 are indexes j that we can jump to from i
            if( !cond2.empty() )
                g[i].insert(cond2.top());
            cond2.push(i);
        }

        // min heap cost,vertex
        priority_queue<array<long,2>,vector<array<long,2>>,greater<array<long,2>>> pq;

        // distances
        long A[n+1];
        for(int i = 0; i < n+1; ++i)
            A[i] = 10000000001;

        // push our source vertex into priority queue
        pq.push({0,0});
        costs[0] = 0;
        // set distance to our source vertex itself to 0
        A[0] = 0;

        int u,v;
        long weight;
        while(!pq.empty()) {

            u = pq.top()[1];
            pq.pop();

            unordered_set<int>::iterator it;
            for(it = g[u].begin(); it != g[u].end(); ++it) {
                v = *it;
                weight = costs[v];

                //  If there is shorter path to v through u.
                if( A[v] > A[u] + weight ) {
                    // Updating distance of v
                    A[v] = A[u] + weight;
                    pq.push({A[v], v});
                }
            }
        }

        return A[n-1];
    }
};
