
// 3615. Longest Palindromic Path in Graph
// https://leetcode.com/problems/longest-palindromic-path-in-graph/

class Solution {
private:
    // debug
    void printBinary(long x, int c) {
        for(int i = 0; i < c; ++i) {
            if( x & (1UL << i) ) cout << 1;
            else cout << 0;
        }
        // cout << endl;
    }

    int countSetBits(int i) {
        unsigned int count = 0;
        while (i) {
            count += i & 1;
            i >>= 1;
        }
        return count;
    }

    // max 14 nodes
    bool mem[16384][14][14];
    
    int ans;

    int n;
    string label;
    vector<vector<int>> g;

    void rec(int mask, int l, int r) {
        if( mem[mask][l][r] )
            return;

        mem[mask][l][r] = true;
        
        int _setbits = countSetBits(mask);
        ans = max(ans, _setbits);

        for(int i = 0; i < g[l].size(); ++i) {
            int l_new = g[l][i];
            if( mask & (1<<l_new) )
                continue;
            
            char l_label = label[l_new];

            for(int j = 0; j < g[r].size(); ++j) {
                int r_new = g[r][j];
                if( l_new == r_new || mask & (1<<r_new) || l_label != label[r_new] )
                    continue;

                int mask_new = mask | (1<<l_new);
                mask_new |= (1<<r_new);

                rec(mask_new, l_new, r_new);
            }
        }

        return;
    }


public:
    int maxLen(int n, vector<vector<int>>& edges, string label) {
        this->n = n;
        memset(mem,false,sizeof mem); 

        // undirected graph with n nodes labeled from 0 to n - 1
        // 1 <= n <= 14
        //     our min answer is 1
        ans = 1;

        g.resize(n);
        int edges_sz = edges.size();
        for(int i = 0; i < edges_sz; ++i) {
            int u = edges[i][0];
            int v = edges[i][1];
            g[u].push_back(v);
            g[v].push_back(u);
        }

        this->label = label;

        // odd length palindrome
        for(int i = 0; i < n; ++i) {

            int mask = (1<<i);
            int l = i;
            int r = i;

            rec(mask, l, r);
        }

        // even length palindromes
        for(int i = 0; i < edges_sz; ++i) {
            int u = edges[i][0];
            int v = edges[i][1];
       
            if( label[u] != label[v] )
                continue;

            int mask = (1<<u);
            mask |= (1<<v); 
            int l = v;
            int r = u;

            rec(mask, l, r);
        }

        return ans;
    }
};


// passes 533/542 test cases, then TLE as of 7/17/2025
// failing test case understandably, doesnt even complete dfs
// n = 13
// edges = [[0,1],[0,2],[0,3],[0,4],[0,5],[0,6],[0,7],[0,8],[0,9],[0,10],[0,11],[0,12],[1,2],[1,3],[1,4],[1,5],[1,6],[1,7],[1,8],[1,9],[1,10],[1,11],[1,12],[2,3],[2,4],[2,5],[2,6],[2,7],[2,8],[2,9],[2,10],[2,11],[2,12],[3,4],[3,5],[3,6],[3,7],[3,8],[3,9],[3,10],[3,11],[3,12],[4,5],[4,6],[4,7],[4,8],[4,9],[4,10],[4,11],[4,12],[5,6],[5,7],[5,8],[5,9],[5,10],[5,11],[5,12],[6,7],[6,8],[6,9],[6,10],[6,11],[6,12],[7,8],[7,9],[7,10],[7,11],[7,12],[8,9],[8,10],[8,11],[8,12],[9,10],[9,11],[9,12],[10,11],[10,12],[11,12]]
// label = "abcdefggfedca"


class Solution {
private:
    // debug
    void printBinary(long x, int c) {
        for(int i = 0; i < c; ++i) {
            if( x & (1UL << i) ) cout << 1;
            else cout << 0;
        }
        // cout << endl;
    }


    int ans;

    int n;
    string label;
    vector<vector<int>> g;

    // map -> key: path, value: list of masks that make that path
    // vector<map<string,vector<int>>> r;
    struct Cmp
    {
        bool operator()(const string& lhs, const string& rhs) const
        {
            // note: we CANNOT just compare size!!!
            if( lhs.size() != rhs.size() )
                return lhs.size() > rhs.size();

            return lhs < rhs;
        }
    };
    vector<map<string,vector<int>,Cmp>> r;


    void dfs(int root_node, int u, string& path, int& mask) {
        if( (n % 2 == 0 && (int)path.size() == (int)(n/2)) ||
            (n % 2 == 1 && (int)path.size() == (int)(n/2) + 1) )
            return;

        // add u to path and mask
        path.push_back(label[u]);
        mask |= (1<<u);

        r[root_node][path].push_back(mask);

        for(int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i];

            // is v already part of our path?
            if( mask & (1<<v) )
                continue;

            dfs(root_node, v, path, mask);
        }

        // backtrack
        mask &= ~(1<<u);
        path.pop_back();

        return;
    }

public:
    int maxLen(int n, vector<vector<int>>& edges, string label) {
        this->n = n;

        // undirected graph with n nodes labeled from 0 to n - 1
        // 1 <= n <= 14
        //     our min answer is 1
        ans = 1;
        // n - 1 <= edges.length <= n * (n - 1) / 2
        //     note: formula number of pairs n * (n-1)/2
        //     ui != vi
        //     no duplicate edges
        //     edges.length worst case n = 14 -> edges.length = 91
        // for odd length
        //     we have two unique valid paths going from a node that match
        //     we could try that brute force,
        //     we would not have to go out further than floor(n/2)
        //     path key concatenation of chars aka string, and a mask
        //     if mask1 & mask2 == pow(2,root_node), then we have a palindrome
        // for even length
        //     if we have a matching path key (no longer then n/2),
        //     and mask1 & mask2 == 0, and
        //     there is an edge between the two nodes where the path begins,
        //     then we have a palindrome

        g.resize(n);
        int edges_sz = edges.size();
        for(int i = 0; i < edges_sz; ++i) {
            int u = edges[i][0];
            int v = edges[i][1];
            g[u].push_back(v);
            g[v].push_back(u);
        }

        this->label = label;
        r.resize(n);

        for(int i = 0; i < n; ++i) {
            // out << "node " << i << " label " << label[i] << endl;
            string path = "";
            int mask = 0;
            dfs(i, i, path, mask);

            // for the current node i, we can at this point check
            // for odd length palindromes
            // start with longest, will requires custom sorting of map key
            for(auto it = r[i].begin(); it != r[i].end(); ++it) {
                string key = it->first;
                 if( (key.size() * 2) - 1 <= ans )
                    // continue;
                    break;
                // cout << "  key " << key << endl;

                bool f = false;
                for(int j = 0; j < it->second.size()-1 && !f; ++j) {
                    int maskj = it->second[j];
                    for(int k = j+1; k < it->second.size(); ++k) {
                        int maskk = it->second[k];
                        // cout << "  ";printBinary(maskj, n); cout << " "; printBinary(maskk, n); cout << endl;
                        if( (maskj & maskk) == pow(2,i) ) {
                            ans = (key.size() * 2) - 1;
                            f = true;
                            break;
                        }
                    }
                }
            }
        }

        // check for even length palindromes better than current answer
        for(int i = 0; i < edges_sz; ++i) {
            int u = edges[i][0];
            int v = edges[i][1];

            if( label[u] != label[v] )
                continue;

            // unless we already have a better answer, ans = 2 at this point
            ans = max(ans, 2);

            for(auto ito = r[u].begin(); ito != r[u].end(); ++ito) {
                string key = ito->first;
                if( key.size() * 2 <= ans )
                    continue;

                // ito->second is a vector of masks

                // find the same key for v?
                auto iti = r[v].find(key);
                if( iti != r[v].end() ) {
                    // iti->second is a vector of masks


                    bool f = false;
                    for(int mask1: ito->second) {
                        for(int mask2: iti->second) {
                            // cout << "  ";printBinary(mask1, n); cout << " "; printBinary(mask2, n); cout << endl;
                            if( (mask1 & mask2) == 0 ) {
                                ans = key.size() * 2;
                                f = true;
                                break;
                            }
                        }
                        if( f )
                            break;
                    }
                }
            }
        }

        return ans;
    }
};
