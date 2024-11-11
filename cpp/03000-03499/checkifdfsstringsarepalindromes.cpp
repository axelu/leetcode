
// 3327. Check if DFS Strings Are Palindromes
// https://leetcode.com/problems/check-if-dfs-strings-are-palindromes/

// initialize once
unsigned long long p_pow[100001];
bool initialized = false;


class Solution {
private:
    const int p = 31;
    
    bool isPalindrome(string& s) {
        if( s.size() == 1 ) return true;

        bool p = true;

        auto fi = s.begin();
        auto ri = s.rbegin();
        while( fi <= ri.base() ) {
            if( *fi == *ri ) {
                ++fi;
                ++ri;
            } else {
                p = false;
                break;
            }
        }

        return p;
    }
    
    struct TreeNode {
        int val;
        char c;
        vector<TreeNode*> children;
        TreeNode(int val, char c) : val(val), c(c), children({}) {}
    };
    
    vector<bool> ans;
    string str;
    int be[100000][2]; // holds begin and end index in str that a node is responsible for

    void dfs(TreeNode* root) {
        // it is guaranteed that root != nullptr
        // root->children is sorted by value asc
        
        be[root->val][0] = str.size();
        
        for(auto it = root->children.begin(); it != root->children.end(); ++it)
            dfs(*it);
        
        str.append(1, root->c);
                
        be[root->val][1] = str.size()-1;
        
        return;
    }
    
    bool isPalindrome(int b, int e) {
        while(b < e) {
            if (str[b] != str[e]) return false;
            ++b;
            --e;
        }
        return true;
    }

public:
    vector<bool> findAnswer(vector<int>& parent, string s) {
        if( !initialized ) {
            initialized = true;
            p_pow[0] = 1ULL;
            for(int i = 1; i < 100001; ++i)
                p_pow[i] = p_pow[i-1] * p;
        }

        int n = parent.size(); // parent.size() == s.size()    
        
        ans.assign(n, false);
        
        // Tree is rooted in node 0
        // hence parent[0] == -1
        TreeNode* root = new TreeNode(0, s[0]);
        
        vector<TreeNode*> treeNodes(n, nullptr);
        treeNodes[0] = root;
        
        for(int i = 1; i < n; ++i) {
            if( treeNodes[i] == nullptr ) {
                treeNodes[i] = new TreeNode(i, s[i]);
            }
            TreeNode* child = treeNodes[i];
            
            if( treeNodes[parent[i]] == nullptr ) {
                treeNodes[parent[i]] = new TreeNode(parent[i], s[parent[i]]);
            }
            TreeNode* prnt = treeNodes[parent[i]];
            
            prnt->children.push_back(child);
        }
        
        // sort children in each node by val
        for(int i = 0; i < n; ++i)
            sort(treeNodes[i]->children.begin(), treeNodes[i]->children.end(),[](const TreeNode* a, const TreeNode* b){
                return a->val < b->val; 
            });
        
        str = "";
        dfs(root);
        
        // cout << str << endl;
        
        /*
        for(int i = 0; i < n; ++i)
            ans[i] = isPalindrome(be[i][0], be[i][1]);       
        
        return ans;
        */
        
        // 012345678901234567890 forward
        // 098765432109876543210 backward
        
        // rolling hash str hf[i] is hash[0...i] Rabin Karp
        unsigned long long hf[100001];
        hf[0] = str[0]-'a'+1;
        for(int i = 1; i < n; ++i)
            hf[i] = (hf[i-1] * p) + (str[i]-'a'+1);
        
        // rolling hash str hr[i] is hash[n-1...i] of str reversed Rabin Karp
        unsigned long long hr[100001];
        hr[0] = str[n-1]-'a'+1;
        for(int i = 1; i < n; ++i)
            hr[i] = (hr[i-1] * p) + (str[(n-1)-i]-'a'+1);
                
        for(int k = 0; k < n; ++k) {
            int b = be[k][0];
            int e = be[k][1];
                        
            // is str[b...e] a palindrome?
            int l  = e - b + 1;
            if( l == 1 ) {
                ans[k] = true;
                continue;
            }
                
            int l2 = l / 2;
            
            // cout << "node k " << k << " b " << b << " e " << e << " l " << l << " l2 " << l2 << endl;
            // cout << str.substr(b, l) << endl;
            
            // we can compare the hash forward [b, b+l2-1] and reversed [e, e-l2+1]
            
            // the substring of str starting at b with a length of l2, respectively str[b...b+l2-1] is under investigation
            // hash of substring str[b...b+l2-1], "normalized" as if it would be starting at index 0
            unsigned long long h_s_f;
            if( b > 0 )
                h_s_f = hf[b+l2-1] - (hf[b-1] * p_pow[(b+l2-1)-(b-1)]);
            else
                h_s_f = hf[l2-1];

            // the substring of str starting at e with a length of l2, respectively str[e...e-l2+1] is under investigation
            // hash of substring str[e...e-l2+1], "normalized" as if it would be starting at index 0
            unsigned long long h_s_r;
            int br = (n-1) - e;
            if( br > 0 )
                h_s_r = hr[br+l2-1] - (hr[br-1] * p_pow[(br+l2-1)-(br-1)]);
            else
                h_s_r = hr[l2-1];
            
            // cout << "h_s_f " << h_s_f << endl;
            // cout << "h_s_r " << h_s_r << endl;
            
            ans[k] = h_s_f == h_s_r;
        }
            
        return ans;
    }
};





// passes 580 / 584 test cases as of 10/23/2024 then MLE

class Solution {
private:
    bool isPalindrome(string& s) {
        if( s.size() == 1 ) return true;

        bool p = true;

        auto fi = s.begin();
        auto ri = s.rbegin();
        while( fi <= ri.base() ) {
            if( *fi == *ri ) {
                ++fi;
                ++ri;
            } else {
                p = false;
                break;
            }
        }

        return p;
    }

    struct TreeNode {
        int val;
        char c;
        vector<TreeNode*> children;
        TreeNode(int val, char c) : val(val), c(c), children({}) {}
    };

    string dfs(TreeNode* root, vector<bool>& ans) {
        // it is guaranteed that root != nullptr
        // root->children is sorted by value asc

        string s = "";

        for(auto it = root->children.begin(); it != root->children.end(); ++it) {
            s = s.append(dfs(*it, ans));
        }

        s.append(1, root->c);
        if( isPalindrome(s) )
            ans[root->val] = true;

        return s;
    }

public:
    vector<bool> findAnswer(vector<int>& parent, string s) {
        int n = parent.size(); // parent.size() == s.size()

        vector<bool> ans(n, false);

        // Tree is rooted in node 0
        // hence parent[0] == -1
        TreeNode* root = new TreeNode(0, s[0]);

        vector<TreeNode*> treeNodes(n, nullptr);
        treeNodes[0] = root;

        for(int i = 1; i < n; ++i) {
            if( treeNodes[i] == nullptr ) {
                treeNodes[i] = new TreeNode(i, s[i]);
            }
            TreeNode* child = treeNodes[i];

            if( treeNodes[parent[i]] == nullptr ) {
                treeNodes[parent[i]] = new TreeNode(parent[i], s[parent[i]]);
            }
            TreeNode* prnt = treeNodes[parent[i]];

            prnt->children.push_back(child);
        }

        // sort children in each node by val
        for(int i = 0; i < n; ++i)
            sort(treeNodes[i]->children.begin(), treeNodes[i]->children.end(),[](const TreeNode* a, const TreeNode* b){
                return a->val < b->val;
            });

        dfs(root, ans);

        return ans;
    }
};
