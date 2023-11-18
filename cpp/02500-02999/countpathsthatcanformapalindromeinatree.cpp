
// 2791. Count Paths That Can Form a Palindrome in a Tree
// https://leetcode.com/problems/count-paths-that-can-form-a-palindrome-in-a-tree/


class Solution {
private:
    void dfs(vector<pair<int,int>> g[], int u, int msk, int pathmasks[]) {

        pathmasks[u] = msk;

        for(auto& p: g[u]) {
            int v   = p.first;
            if( pathmasks[v] != -1 )
                continue;
            int t = p.second;
            dfs(g,v,msk^t,pathmasks); 
        }
        
        return;
    }
    
    long long count(int pathmasks[], int n, int target) {
        unordered_map<int,int> um;
        long long ret = 0;
        
        for(int i = 0; i < n; ++i) {
            int t = pathmasks[i] ^ target;
            if( um.find(t) != um.end() )
                ret += um[t];
        
            ++um[pathmasks[i]]; 
        }   
            
        return ret;
    }
    
public:
    long long countPalindromePaths(vector<int>& parent, string s) {
        int n = parent.size();
        
        vector<pair<int,int>> g[n];
        for(int i = 1; i < n; ++i) {
            int msk = 1 << (s[i]-'a');
            g[i].push_back({parent[i],msk});
            g[parent[i]].push_back({i,msk});
        }
        
        // if we record all path from root node 0 to each node
        // then later even if we check a path from a node to another that does not
        // traverse root, each nodes path to root will cancel each other out
        int pathmasks[n];memset(pathmasks,-1,sizeof pathmasks);
        dfs(g,0,0,pathmasks);
        
        long long ans = 0;
        
        // any pair of nodes whos XOR of the two pathmasks has either no bit set (== 0)
        // or has 1 bit set respectively is a power of two could form a Palindrome
        // brute force
        /*
        for(int u = 0; u < n-1; ++u) {
            for(int v = u+1; v < n; ++v) {
                int msk = pathmasks[u] ^ pathmasks[v];
                if( msk == 0 || !(msk & (msk - 1)) )
                    ++ans;
            }
        }
        */
        
        ans += count(pathmasks,n,0);
        for(int i = 0; i < 26; ++i)
            ans += count(pathmasks,n,1<<i);
                
        return ans;
    }
};




// passes 539/666 test cases, then TLE as of 9/6/2023

class Solution {
private:
    // debug
    void printBinary(long x, int c) {
        for(int i = c-1; i >= 0; --i) {
            if( x & (1UL << i) ) cout << 1;
            else cout << 0;
        }
        // cout << endl;
    }

    unordered_map<long,vector<int>> mem;

    vector<int> dfs(vector<pair<int,int>> g[], long u, long src, int msk) {

        long key = (u<<43) + (src<<26) + msk;
        auto f = mem.find(key);
        if( f != mem.end() )
            return f->second;

        vector<int> ret;
        // is the path to us a palindrome?
        // if( is_zero_or_powerof2(msk) )
        if( msk == 0 || !(msk & (msk - 1)) )
            ret.push_back(u);

        for(auto& p: g[u]) {
            int v   = p.first;
            if( v == src )
                continue;
            int t = p.second;
            auto st = dfs(g,v,u,msk^t);
            ret.insert(ret.end(),st.begin(),st.end());
        }

        return mem[key] = ret;
    }

public:
    long long countPalindromePaths(vector<int>& parent, string s) {
        int n = parent.size();

        vector<pair<int,int>> g[n];
        for(int i = 1; i < n; ++i) {
            int msk = 1 << (s[i]-'a');
            g[i].push_back({parent[i],msk});
            g[parent[i]].push_back({i,msk});
        }

        long long ans = 0;
        for(int u = 0; u < n; ++u){
            for(auto& p: g[u]) {
                int v   = p.first;
                int msk = p.second;

                // cout << "u " << u << " v " << v << " ";printBinary(msk,26);cout << endl;
                vector<int> st = dfs(g,v,u,msk);
                // for(auto x: st)
                //     cout << x << " ";
                // cout << endl;
                ans += count_if(st.begin(), st.end(), [u](int x) { return x > u; });
            }
        }

        return ans;
    }
};
