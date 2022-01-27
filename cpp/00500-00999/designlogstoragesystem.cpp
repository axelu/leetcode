
// 635. Design Log Storage System
// https://leetcode.com/problems/design-log-storage-system/



class LogSystem {
private:
    struct LOGNode {
        map<int,LOGNode*> nodes;
        set<int> ids;
        LOGNode() : nodes({}), ids({}) {}
    };

    LOGNode* root;

    vector<int> timestamp2vector(string& timestamp, int depth = 5) {
        // timestamp format: Year:Month:Day:Hour:Minute:Second
        //            depth:  0     1    2   3     4      5
        vector<int> v;
        stringstream ss(timestamp);
        string s;
        int currDepth = 0;
        while( getline(ss,s,':') ) {
            if( currDepth > depth ) break;
            v.push_back(stoi(s));
            ++currDepth;
        }
        return v;
    }

    LOGNode* mkOrGetNode(vector<int> path) {
        // debug
        // cout << "mkOrGetNode" << endl;
        LOGNode* node = root;
        map<int,LOGNode*>::iterator f;
        for(int i = 0; i < path.size(); ++i) {
            f = node->nodes.find(path[i]);
            if( f != node->nodes.end() ) {
                // debug
                // cout << "found node " << path[i] << endl;
                node = f->second;
            } else {
                // debug
                // cout << "create node " << path[i] << endl;
                LOGNode* newNode = new LOGNode();
                node->nodes.insert({path[i],newNode});
                node = newNode;
            }
        }
        return node;
    }

    void dfs(LOGNode* root, int currDepth, int maxDepth, vector<int>& vs, vector<int>& ve,
             vector<int>& path, vector<int>& ans) {

        // debug
        // cout << "currDepth: " << currDepth;
        // cout << " nodes: ";
        // for(auto node : root->nodes ) cout << node.first << " ";
        // cout << endl;

        if( root->nodes.empty() ) {
            // leaf node
            for(auto it = root->ids.begin(); it != root->ids.end(); ++it)
                ans.push_back(*it);
            return;
        }

        if( currDepth > maxDepth ) {
            // include all children
            for(auto it = root->nodes.begin(); it != root->nodes.end(); ++it)
                dfs(it->second,currDepth+1,maxDepth,vs,ve,path,ans);
            return;
        }

        // determine if our path so far is on the left and/or the right edge
        int n = path.size();
        // left edge
        bool leftEdge = true;
        for(int i = 0; i < n; ++i)
            if( path[i] != vs[i] ) {
                leftEdge = false;
                break;
            }
        // right edge
        bool rightEdge = true;
        for(int i = 0; i < n; ++i)
            if( path[i] != ve[i] ) {
                rightEdge = false;
                break;
            }

        map<int,LOGNode*>::iterator it = leftEdge ? root->nodes.lower_bound(vs[currDepth]) : root->nodes.begin();
        for(; it != root->nodes.end(); ++it) {
            if( rightEdge && it->first > ve[currDepth] ) break;
            path.push_back(it->first);
            dfs(it->second,currDepth+1,maxDepth,vs,ve,path,ans);
            // backtrack
            path.pop_back();
        }
    }

public:
    LogSystem() {
        root = new LOGNode();
    }

    void put(int id, string timestamp) {
        LOGNode* node = mkOrGetNode(timestamp2vector(timestamp));
        node->ids.insert(id);
    }

    vector<int> retrieve(string start, string end, string granularity) {
        // granularity is one of the values ["Year", "Month", "Day", "Hour", "Minute", "Second"]
        int depth;
        if     ( "Year"   == granularity ) depth = 0;
        else if( "Month"  == granularity ) depth = 1;
        else if( "Day"    == granularity ) depth = 2;
        else if( "Hour"   == granularity ) depth = 3;
        else if( "Minute" == granularity ) depth = 4;
        else                               depth = 5;

        // timestamp format: Year:Month:Day:Hour:Minute:Second
        // assumption: start <= end
        vector<int> vs = timestamp2vector(start,depth);
        vector<int> ve = timestamp2vector(end,depth);

        // DFS
        vector<int> ans;
        vector<int> path;
        dfs(root,0,depth,vs,ve,path,ans);
        return ans;
    }
};

/**
 * Your LogSystem object will be instantiated and called as such:
 * LogSystem* obj = new LogSystem();
 * obj->put(id,timestamp);
 * vector<int> param_2 = obj->retrieve(start,end,granularity);
 */
