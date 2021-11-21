
// 1938. Maximum Genetic Difference Query
// https://leetcode.com/problems/maximum-genetic-difference-query/
// https://leetcode.com/contest/weekly-contest-250/problems/maximum-genetic-difference-query/




class Solution {
private:
    struct Trie {
        struct Trie* children[2];
        struct Trie* parent;
        int endOfWord;
    };

    struct Trie* init() {
        struct Trie* tn =  new Trie;

        tn->endOfWord = -1;

        tn->children[0] = NULL;
        tn->children[1] = NULL;

        tn->parent = NULL;

        return tn;
    }

    struct Trie* add(int s, Trie* dic) {
        struct Trie* tn = dic;

        for(int i = 31; i >= 0; --i) {
            if( s & (1 << i) ) {
                if( !tn->children[1] ) {
                    tn->children[1] = init();
                    tn->children[1]->parent = tn;
                }
                tn = tn->children[1];
            } else {
                if( !tn->children[0] ) {
                    tn->children[0] = init();
                    tn->children[0]->parent = tn;
                }
                tn = tn->children[0];
            }
        }

        // last node is end of word
        tn->endOfWord = s;

        return tn;
    }

    void del(Trie* tn) {

        while( tn->parent && !tn->children[0] && !tn->children[1] ) {

            if( tn->parent->children[0] == tn )
                tn->parent->children[0] = NULL;
            else
                tn->parent->children[1] = NULL;

            struct Trie* t = tn;
            tn = tn->parent;
            delete t;
        }
    }

    int search(int s, Trie* dic) {
        struct Trie* tn = dic;

        // at every bit we try to go opposite
        for(int i = 31; i >= 0; --i) {
            if( s & (1 << i) ) {
                if (tn->children[0])
                    tn = tn->children[0];
                else
                    tn = tn->children[1];
            } else {
                if (tn->children[1])
                    tn = tn->children[1];
                else
                    tn = tn->children[0];
            }
        }

        return tn->endOfWord;
    }

    struct Node {
        int val;
        vector<Node*> children;
        Node(int x) : val(x), children({}) {}
    };

    void preorder(Node* node, Trie* dic, unordered_map<int,vector<array<int,2>>>& qm, vector<int>& ans) {
        //cout << node->val << endl;

        Trie* tn = add(node->val,dic);

        auto f = qm.find(node->val);
        if( f != qm.end() )
            for(int i = 0; i < f->second.size(); ++i) {
                //cout << "executing query for val " << f->second[i][0] << endl;
                ans[f->second[i][1]] = f->second[i][0]^search(f->second[i][0],dic);
            }

        for(int i = 0; i < node->children.size(); ++i)
            preorder(node->children[i],dic,qm,ans);

        del(tn);
    }

public:
    vector<int> maxGeneticDifference(vector<int>& parents, vector<vector<int>>& queries) {
        // idea
        // - a trie for integers can very quickly return the max XOR
        // - what if we had a trie that only included the ancestors
        //   for the number that we are executing a query for?
        // - from the array parents we create a n-ary tree
        //   we then do a preorder traversal, we add the val of the
        //   current node to the trie and execute the query for the value of that node
        //   when we backtrack, we will delete the node's val from the trie

        // query map
        unordered_map<int,vector<array<int,2>>> qm;
        int qsz = queries.size();
        for(int i = 0; i < qsz; ++i) {
            auto p = qm.insert({queries[i][0],{{{queries[i][1],i}}}});
            if( !p.second )
                p.first->second.push_back({queries[i][1],i});
        }

        // build tree from parents
        int n = parents.size();
        vector<Node*> seen(n,nullptr);
        Node* root;
        for(int i = 0; i < n; ++i) {
            // parents[i] is the parent for node i
            // i is the child

            if( seen[i] == nullptr )
                seen[i] = new Node(i); // child

            if( parents[i] == -1 ) {
                root = seen[i];
                continue;
            }

            if( seen[parents[i]] == nullptr )
                seen[parents[i]] = new Node(parents[i]); // parent

            // attach child to parent
            seen[parents[i]]->children.push_back(seen[i]);
        }

        // root of trie
        struct Trie* dic = init();

        vector<int> ans(qsz);

        preorder(root,dic,qm,ans);

        return ans;
    }
};
