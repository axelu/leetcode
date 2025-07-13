
// 3530. Maximum Profit from Valid Topological Order in DAG
// https://leetcode.com/problems/maximum-profit-from-valid-topological-order-in-dag/





class Solution {
private:
    vector<int> * pNums;
    vector<vector<int>> * pR;

    void permute(int n) {
        if( n == 1 ) {
            pR->push_back(*pNums);
            return;
        }

        int t;
        for(int i = 0; i < n; ++i) {
            permute(n-1);

            if( n % 2 == 1 ) {
                // size is odd,: swap first and size-1 element
                t = (*pNums)[0];
                (*pNums)[0] = (*pNums)[n-1];
                (*pNums)[n-1] = t;
            } else {
                // size is even: swap ith and size-1 element
                t = (*pNums)[i];
                (*pNums)[i] = (*pNums)[n-1];
                (*pNums)[n-1] = t;
            }
        }
    }

    unordered_map<vector<bool>,int> mem;

    int rec(vector<vector<int>>& g, vector<int>& score,
            vector<int>& candidates, vector<int>& indegree, int f,
            vector<bool>& mask)
    {
        int c_sz = candidates.size();
        if( c_sz == 0 )
            return 0;

        /*
        cout << "rec ";
        cout << "candidates ";
        for(int i = 0; i < c_sz; ++i)
            cout << candidates[i] << " ";
        cout << endl;
        cout << "    indegree ";
        for(int i = 0; i < indegree.size(); ++i)
            cout << indegree[i] << " ";
        cout << endl;
        */

        auto fd = mem.find(mask);
        if( fd != mem.end() )
            return fd->second;

        int ret = 0;

        // process candidates
        for(int i = 0; i < c_sz; ++i) {
            int u = candidates[0];
            // remove the candidate from front of list
            candidates.erase(candidates.begin());
            mask[u] = true;

            int lscore = score[u] * f;

            for(int j = 0; j < g[u].size(); ++j) {
                int v = g[u][j];
                --indegree[v];
                if( indegree[v] == 0 )
                    candidates.push_back(v);
            }
            ret = max(ret, lscore + rec(g, score, candidates, indegree, f+1, mask));

            // backtrack
             for(int j = g[u].size()-1; j >= 0; --j) {
                int v = g[u][j];
                ++indegree[v];
                if( indegree[v] == 1 )
                    candidates.pop_back();
            }
            // add candidate back to end of list as part of backtrack
            candidates.push_back(u);
            mask[u] = false;
        }

        return mem[mask] = ret;
    }


public:
    int maxProfit(int n, vector<vector<int>>& edges, vector<int>& score) {

        /*
        // example
        // n = 5 edges = [[1,2],[0,3],[1,4],[2,3],[1,3]] score = [50913,47946,97391,27488,69147]
        // correct processing order 1, 0, 2, 3, 4
        // example
        // n = 3 edges = [[0,2]] score = [60084,34608,25733]
        // correct processing order 1, 0, 2

        pNums = &score;

        vector<vector<int>> r;
        pR = &r;
        permute(n);
        for(int i = 0; i < r.size(); ++i) {
            int factor = 1;
            int pscore = 0;
            for(int j = 0; j < n; ++j) {
                cout << r[i][j] << " ";
                pscore += r[i][j] * factor++;
            }
            cout << " pscore " << pscore << endl;
        }
        */

        /* assumption: multiply larger scores with larger factors
         * idea:
         * 1 get all leaves with outgoing edges
         * 2 put all those into a queue
         * 3 process from queue by value smallest to greatest * incrementing factor
         * 4 put next nodes into a queue
         * repeat 2-4
         * that will NOT work, because it maybe better to process a spine
         * in its entirety instead of all of them in parallel
         * idea:
         *  process by indegree
         *  does not work
         * idea:
         *  reverse the edges and process in opposite direction
         *  does not work
         * so a greedy approach does not work, hence DP
         */


        // edge case -> no edges
        if( edges.size() == 0 ) {
            sort(score.begin(),score.end());
            int ans = 0;
            for(int i = 0; i < n; ++i)
                ans += score[i] * (i+1);
            return ans;
        }

        // Directed Acyclic Graph (DAG) with n nodes labeled from 0 to n - 1
        vector<vector<int>> g(n,vector<int>());
        vector<int> indegree(n,0);
        for(auto& edge: edges) {
            int u = edge[0];
            int v = edge[1];
            g[u].push_back(v);
            ++indegree[v];
        }

        vector<int> candidates; // nodes with indegree of 0
        for(int i = 0; i < n; ++i)
            if( indegree[i] == 0 )
                candidates.push_back(i);

        vector<bool> mask(n,false);
        return rec(g, score, candidates, indegree, 1, mask);
    }
};
