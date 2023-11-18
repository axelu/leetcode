
// 2479. Maximum XOR of Two Non-Overlapping Subtrees
// https://leetcode.com/problems/maximum-xor-of-two-non-overlapping-subtrees/





/* max 50000 nodes, max value 1000000000
 * -> max sum 50000000000000
 * -> binary 1011010111100110001000001111010010000000000000
 * -> most significant set bit is the 45th bit
 */
class Solution {
private:
    struct Trie{
        long long val;
        Trie* set;
        Trie* notset;
        Trie() : val(0), set(nullptr), notset(nullptr) {}
    };

    Trie * root;

    struct Trie* init() {
        struct Trie* tn =  new Trie;
        return tn;
    }

    void add(long long x) {
        struct Trie* tn = root;

        for(int i = 45; i >= 0; --i) {
            if( (1L << i) & x ) {
                if( tn->set == nullptr )
                    tn->set = init();
                tn = tn->set;
            } else {
                if( tn->notset == nullptr )
                    tn->notset = init();
                tn = tn->notset;
            }
        }

        // last node is end of word
        tn->val = x;
    }

    long long search(long long x) {
        // we want to find the val in our Trie that delivers us the
        // max XOR with x, so we will prefer to go oposite of x
        struct Trie* tn = root;

        for(int i = 45; i >= 0; --i) {
            if( (1L << i) & x ) {
                if( tn->notset != nullptr )
                    tn = tn->notset;
                else
                    tn = tn->set;
            } else {
                if( tn->set != nullptr )
                    tn = tn->set;
                else
                    tn = tn->notset;
            }
            if( tn == nullptr )
                return x;
        }

        return tn->val;
    }

    long long dfs1(vector<int> g[], vector<int>& values, int u, int src, int parent[], long long sum[]) {
        parent[u] = src;
        long long ret = values[u];

        for(int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i];
            if( parent[v] != -1 || v == 0 )
                continue;
            ret += dfs1(g,values,v,u,parent,sum);
        }

        return sum[u] = ret;
    }

    long long dfs2(vector<int> g[], long long sum[], int u, int src, int parent[]) {
        parent[u] = src;

        // all sums in our trie do not include those of our children yet, so no overlap,
        // hence we can search for the optimal sum in the trie that would deliver the
        // maximum XOR with the sum of our node
        long long ret = sum[u] ^ search(sum[u]);

        for(int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i];
            if( parent[v] != -1 || v == 0 )
                continue;
            ret = max(ret, dfs2(g,sum,v,u,parent));
        }

        // add our sum to the trie
        add(sum[u]);

        return ret;
    }

public:
    long long maxXor(int n, vector<vector<int>>& edges, vector<int>& values) {
        // tree rooted in node 0
        vector<int> g[n];
        for(auto& v: edges) {
            g[v[0]].push_back(v[1]);
            g[v[1]].push_back(v[0]);
        }

        int parent[n];memset(parent,-1,sizeof parent);
        long long sum[n]; // subtree sum
        dfs1(g,values,0,-1,parent,sum);

        memset(parent,-1,sizeof parent);
        root = init();
        return dfs2(g,sum,0,-1,parent);
    }
};
