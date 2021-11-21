
// 1993. Operations on Tree
// https://leetcode.com/problems/operations-on-tree/





class LockingTree {
private:
    struct Node {
        int user;   // user who has the node locked, -1 if the node in not locked
        Node * parent;
        vector<Node*> children;
        Node(): user(-1), parent(nullptr), children({}) {}
    };

    unordered_map<int,Node*> um;

    bool dfs1(Node* root) {
        if( root->user != -1 )
            return true;

        for(int i = 0; i < root->children.size(); ++i) {
            if( dfs1(root->children[i]) )
                return true;
        }

        return false;
    }

    void dfs2(Node* root) {
        root->user = -1;
        for(int i = 0; i < root->children.size(); ++i)
            dfs2(root->children[i]);
    }


public:
    LockingTree(vector<int>& parent) {
        int n = parent.size();

        // build the tree
        unordered_map<int,Node*>::iterator nit,pit;
        // parent[0] == -1 -> root
        Node* nd = new Node();
        um.insert({0,nd});
        Node* pt;
        for(int i = 1; i < n; ++i) {
            // does our node already exist?
            nit = um.find(i);
            if( nit == um.end() ) {
                nd = new Node();
                um.insert({i,nd});
            } else {
                nd = nit->second;
            }
            // does our parent already exist?
            pit = um.find(parent[i]);
            if( pit == um.end() ) {
                pt = new Node();
                um.insert({parent[i],pt});
            } else {
                pt = pit->second;
            }
            nd->parent = pt;
            pt->children.push_back(nd);
        }
    }

    bool lock(int num, int user) {
        //cout << "lock num " << num << " user " << user << endl;
        auto f = um.find(num);
        if( f->second->user == -1 ) {
            f->second->user = user;
            return true;
        }
        return false;
    }

    bool unlock(int num, int user) {
        auto f = um.find(num);
        if( f->second->user == user ) {
            f->second->user = -1;
            return true;
        }
        return false;
    }

    bool upgrade(int num, int user) {
        auto f = um.find(num);
        if( f->second->user != -1 )
            return false;

        // ancestors
        Node * t = f->second->parent;
        while( t != nullptr ) {
            if( t->user != -1 )
                return false;
            t = t->parent;
        }

        // descendants
        if( !dfs1(f->second) )
            return false;

        dfs2(f->second); // unlock all descendants
        f->second->user = user;
        return true;
    }
};

/**
 * Your LockingTree object will be instantiated and called as such:
 * LockingTree* obj = new LockingTree(parent);
 * bool param_1 = obj->lock(num,user);
 * bool param_2 = obj->unlock(num,user);
 * bool param_3 = obj->upgrade(num,user);
 */
