
// 588. Design In-Memory File System
// https://leetcode.com/problems/design-in-memory-file-system/



class FileSystem {
private:
    struct FSNode {
        map<string,FSNode*> nodes;
        string* content;
        FSNode() : nodes({}), content(nullptr) {}
    };

    FSNode* root;

    vector<string> path2vector(string path) {
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


public:
    FileSystem() {
        root = new FSNode();
    }

    vector<string> ls(string path) {
        vector<string> v = path2vector(path);
        FSNode* node = mkOrGetNode(v);
        vector<string> ans;
        if( node->content != nullptr )
            ans.push_back(v.back());
        else
            for(auto it = node->nodes.begin(); it != node->nodes.end(); ++it)
                ans.push_back(it->first);
        return ans;
    }

    void mkdir(string path) {
        mkOrGetNode(path2vector(path));
    }

    void addContentToFile(string filePath, string content) {
        FSNode* node = mkOrGetNode(path2vector(filePath));
        if( node->content == nullptr )
            node->content = new string(content);
        else
            node->content->append(content);
    }

    string readContentFromFile(string filePath) {
        return *mkOrGetNode(path2vector(filePath))->content;
    }
};
