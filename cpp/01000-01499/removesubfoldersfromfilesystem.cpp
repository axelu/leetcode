
// 1233. Remove Sub-Folders from the Filesystem
// https://leetcode.com/problems/remove-sub-folders-from-the-filesystem/



class Solution {
private:
    struct FSNode {
        map<string,FSNode*> nodes;
        FSNode() : nodes({}) {}
    };

    FSNode* root;

    vector<string> path2vector(string& path) {
        // remove leading '/' from path string and
        // split the path string by '/'
        vector<string> v;
        stringstream ss(path.substr(1));
        string s;
        while( getline(ss,s,'/') )
            v.push_back(s);
        return v;
    }

    FSNode* mkOrGetNode(vector<string> path) {
        FSNode* node = root;
        map<string,FSNode*>::iterator f;
        for(int i = 0; i < path.size(); ++i) {
            f = node->nodes.find(path[i]);
            if( f != node->nodes.end() ) {
                node = f->second;
            } else {
                FSNode* newNode = new FSNode();
                node->nodes.insert({path[i],newNode});
                node = newNode;
            }
        }
        return node;
    }

    FSNode* getNode(vector<string> path) {
        FSNode* node = root;
        map<string,FSNode*>::iterator f;
        for(int i = 0; i < path.size(); ++i) {
            f = node->nodes.find(path[i]);
            if( f != node->nodes.end() ) {
                node = f->second;
            } else {
                return nullptr;
            }
        }
        return node;
    }

    void removeSubFolders(FSNode* node) {
        for(auto it = node->nodes.begin(); it != node->nodes.end(); ++it)
            removeSubFolders(it->second);
        delete node;
    }

    void dfs(FSNode* node, string& path, vector<string>& ans) {
        if( node->nodes.empty() ) {
            // leaf node
            ans.push_back(path);
            return;
        }

        int l = path.size();
        for(auto it = node->nodes.begin(); it != node->nodes.end(); ++it) {
            path += "/" + it->first;
            dfs(it->second,path,ans);
            // backtrack
            path = path.substr(0,l);
        }
    }

public:
    vector<string> removeSubfolders(vector<string>& folder) {
        // assumption: folders do not end in '/'
        int n = folder.size();
        if( n == 1 ) return folder;

        // pass 1
        // build Filesystem
        root = new FSNode();
        for(int i = 0; i < n; ++i)
            mkOrGetNode(path2vector(folder[i]));

        // pass 2
        // remove Sub-Folders
        FSNode* node;
        for(int i = 0; i < n; ++i) {
            node = getNode(path2vector(folder[i]));
            if( node != nullptr ) {
                for(auto it = node->nodes.begin(); it != node->nodes.end(); ++it)
                    removeSubFolders(it->second);
                node->nodes.clear();
            }
        }

        // whatever is left in the Filesystem tree we return
        vector<string> ans;
        string path = "";
        dfs(root,path,ans);
        return ans;
    }
};
