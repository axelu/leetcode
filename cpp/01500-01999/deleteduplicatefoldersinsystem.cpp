
// 1948. Delete Duplicate Folders in System
// https://leetcode.com/problems/delete-duplicate-folders-in-system/
// https://leetcode.com/contest/weekly-contest-251/problems/delete-duplicate-folders-in-system/





class Solution {
private:
    struct Node{
        string val;
        bool del;
        vector<Node*> children;
        Node() : val(""), del(false), children({}) {}
        Node(string s) : val(s), del(false), children({}) {}
    };

    unordered_map<string,Node*> um;


    string buildTree(Node* root, vector<vector<string>>& paths, int& i) {

        Node* node = new Node(paths[i].back());
        root->children.push_back(node);

        int currDepth = paths[i].size();
        ++i; // advance

        string subtree = "";
        int p = 0;
        while( i < paths.size() && paths[i].size() > currDepth ) {
            subtree += to_string(p) + buildTree(node,paths,i);
            ++p;
            /*
            if( subtree.empty() )
                subtree += buildTree(node,paths,i);
            else
                subtree += "," + buildTree(node,paths,i);
            */
        }

        if( !subtree.empty() ) {
            // cout << "subtree " << node->val << ": " << subtree << endl;
            pair<unordered_map<string,Node*>::iterator,bool> p = um.insert({subtree,node});
            if( !p.second ) {
                p.first->second->del = true;
                node->del = true;
            }
            return node->val + "#" + subtree + ";";
        }

        return node->val;
    }

    void tree2vvs(Node* root, vector<string>& path, vector<vector<string>>& ans) {
        if( root->del )
            return;

        path.push_back(root->val);

        ans.push_back(path);
        /*
        for(int i = 0; i < path.size(); ++i)
            cout << path[i] << " ";
        cout << endl;
        */

         for(int i = 0; i < root->children.size(); ++i)
            tree2vvs(root->children[i],path,ans);

        // backtrack
        path.pop_back();
    }

public:
    vector<vector<string>> deleteDuplicateFolder(vector<vector<string>>& paths) {
        sort(paths.begin(),paths.end());
        /*
        for(int i = 0; i < paths.size(); ++i) {
            for(int j = 0; j < paths[i].size(); ++j)
                cout << paths[i][j] << " ";
            cout << endl;
        }
        */


        // build a directory tree
        Node* root = new Node();
        int i = 0;
        while(i<paths.size())
            buildTree(root,paths,i);

        vector<vector<string>> ans;
        vector<string> path;
        for(i = 0; i < root->children.size(); ++i)
            tree2vvs(root->children[i],path,ans);

        return ans;
    }
};
