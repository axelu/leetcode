
// 3141. Maximum Hamming Distances
// https://leetcode.com/problems/maximum-hamming-distances/

class Solution {
private:
    unordered_map<int,vector<int>> g;
    
    void build_graph(int m) {
        
        queue<int> q;
        q.push(0);
        
        while( !q.empty() ) {
            
            queue<int> q_new;
            unordered_set<int> seen;
            while( !q.empty() ) {
                int u = q.front();
                q.pop();
                
                // generate all int's that have 1 bit difference to u
                int x = u;
                for(int i = 0; i < m; ++i) {
                    if( (u>>i) & 1 )
                        continue;

                    x |= (1<<i); // set the i'th bit
                    g[u].push_back(x);
                    g[x].push_back(u);
                    
                    if( seen.insert(x).second )
                        q_new.push(x);                        

                    // backtrack
                    x &= ~(1<<i); // clear the i'th bit
                }
            }
            q = q_new;
        }
        
        return;
    }
    
    int get_complement(int x, int m) {
        int ret = 0;
        for(int i = 0; i < m; ++i)
            if( !((x>>i) & 1) )
                ret |= (1<<i);
        
        return ret;
    }
    
public:
    vector<int> maxHammingDistances(vector<int>& nums, int m) {
        // if we take the current element of nums,
        // its complement would represent the element with the maximum hamming distance
        // if we do a search, starting with its complement along a path,
        // where the next element differs by only 1 bit, as soon as we find one
        // that is part of nums, we have our answer.
        
        bool dic[(int)pow(2,m)];memset(dic,false,sizeof dic);
        for(int x: nums)
            dic[x] = true;
        
        // build graph
        build_graph(m);
        
        int n = nums.size();
        vector<int> ans(n);
        
        int mem[(int)pow(2,m)];memset(mem,-1,sizeof mem);
        for(int i = 0; i < n; ++i) {
            int x = nums[i];
            int x_complement = get_complement(x, m);
            if( mem[x_complement] != -1 ) {
                ans[i] = mem[x_complement];
                continue;
            }
            
            // our x_complement has the maximum hamming distance of m to x
            // BFS
            queue<pair<int,int>> q;
            q.push({x_complement, m});
            bool seen[(int)pow(2,m)];memset(seen,false,sizeof seen);
            seen[x_complement] = true;
            while( !q.empty() ) {
                int u = q.front().first;
                int d = q.front().second;
                q.pop();
                
                if( dic[u] ) {
                    ans[i] = d;
                    mem[x_complement] = d;
                    break;
                }
                
                for(int v: g[u] )
                    if( !seen[v] ) {
                        q.push({v, d-1});
                        seen[v] = true;
                    }
            }
        }

        return ans;
    }
};

