
// 1782. Count Pairs Of Nodes
// https://leetcode.com/problems/count-pairs-of-nodes/




class Solution {
private:
    // binary search upper bound
    int search(vector<int>& degree, int a, int n, int k) {
        // find the first degree b so that
        // degree[a] + degree[b] > k and a < b
        int s = a + 1;
        int e = n;
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( degree[a] + degree[mid] <= k )
                s = mid + 1;
            else
                e = mid;
        }
        if( s < n && degree[a] + degree[s] <= k )
            ++s;

        return s;
    }

public:
    vector<int> countPairs(int n, vector<vector<int>>& edges, vector<int>& queries) {
        vector<int> degree(n,0);
        unordered_map<int,int> occurence; // <lownodehighnode>,count

        for(auto& edge : edges) {
            ++degree[edge[0]-1];
            ++degree[edge[1]-1];

            int key;
            if( edge[0] < edge[1] ) {
                key = (edge[0]-1) << 15;
                key += edge[1]-1;
            } else {
                key = (edge[1]-1) << 15;
                key += edge[0]-1;
            }
            auto p = occurence.insert({key,1});
            if( !p.second )
                ++p.first->second;
        }

        vector<int> degree_sorted = degree; // for binary search
        sort(degree_sorted.begin(),degree_sorted.end());

        // answer each query
        int q_sz = queries.size();
        vector<int> ans(q_sz,0);
        for(int i = 0; i < q_sz; ++i) {
            int k = queries[i];

            // for each degree of node a get the first node b where
            // degree[a] + degree[b] > k and a < b
            for(int a = 0; a < n; ++a) {
                int t = search(degree_sorted,a,n,k);
                // the number of nodes between [t,n-1] inclusive
                // is the number of nodes meeting the criteria, hence add to our answer
                ans[i] += n - t;
            }
            // new we need to adjust our answer as any degree[a] + degree[b] > k
            // does not consider us doublecounting edges between a and b
            // hence adjust aus answer by occurence a,b if degree[a] + degree[b] > k
            for(auto it = occurence.begin(); it != occurence.end(); ++it) {
                int a = it->first >> 15;
                int b = it->first - (a << 15);
                if( degree[a] + degree[b] > k && degree[a] + degree[b] - it->second <= k)
                    -- ans[i];
            }
        }

        return ans;
    }
};
