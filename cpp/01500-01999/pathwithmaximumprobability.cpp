
// 1514. Path with Maximum Probability
// https://leetcode.com/problems/path-with-maximum-probability/



class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {
        // bidirectional weighted graph
        vector<pair<int,double>> g[n];
        for(int i = 0; i < succProb.size(); ++i) {
            g[edges[i][0]].push_back({edges[i][1],succProb[i]});
            g[edges[i][1]].push_back({edges[i][0],succProb[i]});
        }

        double A[n]; // greatest probability seen
        for(int i = 0; i < n; ++i)
            A[i] = 0.0;

        auto cmp = [](const pair<int,double>& a, const pair<int,double>& b){
            return a.second < b.second;
        };
        priority_queue<pair<int,double>,vector<pair<int,double>>,decltype(cmp)> pq(cmp);
        pq.push({start,1.0});
        A[start] = 1.0;

        while( !pq.empty() ) {
            int u = pq.top().first;
            double prob = pq.top().second; // probability to reach u
            pq.pop();

            if( u == end )
                return prob;

            for(auto& p : g[u]) {
                int v = p.first;
                double u_v_prob = p.second; // probability to travers edge u -> v

                double prob_new = prob * u_v_prob;
                if( prob_new > A[v] ) {
                    A[v] = prob_new;
                    pq.push({v,prob_new});
                }
            }
        }

        return 0.0;
    }
};
