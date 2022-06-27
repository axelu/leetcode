
// 444. Sequence Reconstruction
// https://leetcode.com/problems/sequence-reconstruction/



class Solution {
private:
    void dfs(unordered_set<int> g[], int u, int seen[], stack<int>& stck) {

        seen[u] = 1;

        for(auto it = g[u].begin(); it != g[u].end(); ++it) {
            int v = *it;
            if( !seen[v] )
                dfs(g,v,seen,stck);
        }

        // push vertex onto stack
        // parents pushed onto stack after children
        stck.push(u);
    }

    bool ans;

    void postorder(unordered_set<int> g[], int u, int seen[], vector<int>& nums, int step) {
        // cout << "postorder u " << u << endl;

        seen[u] = 1;

        if( step == nums.size() - 1 )
            return;

        // explore 1st what should be the next step
        auto f = g[u].find(nums[step+1]);
        if( f == g[u].end() ) {
            ans = false;
            return;
        }
        postorder(g,nums[step+1],seen,nums,step+1);

        for(auto it = g[u].begin(); it != g[u].end(); ++it) {
            int v = *it;
            if( v == nums[step+1] )
                continue;
            if( !seen[v] ) {
                ans = false;
                break;
            }
        }

        return;
    }

public:
    bool sequenceReconstruction(vector<int>& nums, vector<vector<int>>& sequences) {
        // observation from the three provided examples:
        // we can create a directed graph between the nodes of sequences
        // if we then to a topological sort and do a DFS after:
        //    - if there is more then one connected component,
        //      then nums is NOT the shortest possible and the only supersequence
        //    - if in the DFS we back up and then have undiscovered children,
        //      then nums is not the shortest possible and the only supersequence
        //    - if there is one connected component but is is shorter,
        //      then nums is NOT the shortest possible and the only supersequence

        int n = nums.size(); // because nums is a permutation of the integers in the range [1, n]
                             // our max element is n

        sort(sequences.begin(),sequences.end());
        unordered_set<int> g[n+1];
        for(auto& sequence : sequences)
            for(int i = 1; i < sequence.size(); ++i)
                g[sequence[i-1]].insert(sequence[i]);

        // topological sort
        stack<int> stck; // visited vertices in topological order
        int seen[n+1];memset(seen,0,sizeof seen);
        for(int u = 1; u < n+1; ++u)
            if( !seen[u] )
                dfs(g,u,seen,stck);

        // traverse in topological order
        if( stck.size() != n )
            return false;

        ans = true;
        memset(seen,0,sizeof seen);
        int i = 0;
        while( !stck.empty() ) {
            int u = stck.top();
            stck.pop();
            if( u != nums[i] )
                return false;
            if( !seen[u] && i > 0 )
                return false;
            if( !seen[u] )
                postorder(g,u,seen,nums,0);
            ++i;
        }

        return ans;
    }
};
