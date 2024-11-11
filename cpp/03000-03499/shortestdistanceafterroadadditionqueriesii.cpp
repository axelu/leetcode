
// 3244. Shortest Distance After Road Addition Queries II
// https://leetcode.com/problems/shortest-distance-after-road-addition-queries-ii/




class Solution {
public:
    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries) {
        // There are no repeated roads among the queries.
        // There are no two queries such that i != j and queries[i][0] < queries[j][0] < queries[i][1] < queries[j][1].
        //     in other words: there are no roads the interweave, meaning
        //         a new road will eclipse two or more roads OR
        //         a new road is meaningless, meaning it is already eclipsed
        // hence our problem becomes an intervall merge problem

        // map with begin points of roads and their length
        set<int> st;
        for(int i = 0; i < n; ++i)
            st.insert(i);

        int t = n-1;

        int q_sz = queries.size();
        vector<int> ans(q_sz);
        for(int i = 0; i < q_sz; ++i) {
            int s = queries[i][0]; // start of our new road
            int e = queries[i][1]; // end of our new road

            auto it = st.find(s);
            if( it ==  st.end() || *next(it) > e ) {
                // our new road is meaningless, meaning it is already eclipsed
                ans[i] = t;
                continue;
            }

            // our new road is eclipsing two or more existing roads

            int d = 0;

            ++it;
            while( *it < e ) {
                ++d;
                it = st.erase(it);
            }
            ++d;

            ans[i] = t = t - d + 1;
        }

        return ans;
    }
};
