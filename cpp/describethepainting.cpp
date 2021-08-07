


// 1943. Describe the Painting
// https://leetcode.com/problems/describe-the-painting/
// https://leetcode.com/contest/biweekly-contest-57/problems/describe-the-painting/



class Solution {
private:
    struct Node{
        long long s; // begin
        long long e; // end
        long long c; // color 
        Node* left;
        Node* right;
        Node(int s, int e) : s(s), e(e), c(0), left(nullptr), right(nullptr) {}
    };

    Node* build(vector<int>& arr, int s, int e) {
        //cout << "build s " << s << " e " << e << endl;
        Node* node = new Node(arr[s],arr[e]);
        if( e-s == 1 )
            return node;
        
        int mid = s + ((e-s)/2);
        node->left =  build(arr,s,mid);
        node->right = build(arr,mid,e);
        return node;
    }

    void insert(Node* root, vector<int>& segment) {        
        if( segment[0] <= root->s && segment[1] >= root->e )
            root->c += (long)segment[2];
        else {
            if( root->left != nullptr && root->left->e > segment[0] )
                insert(root->left,segment);
            if( root->right != nullptr && root->right->s < segment[1] )
                insert(root->right,segment);
        }
    }
    
    long long color(Node* root, int x) {
        
        long long ret = root->c;

        if( root->left != nullptr && x < root->left->e )
            ret += color(root->left,x);
        
        if( root->right != nullptr && x >= root->right->s )
            ret += color(root->right,x);
         
        return ret;
    }

public:
    vector<vector<long long>> splitPainting(vector<vector<int>>& segments) {
        int n = segments.size();
        int i;
        
        // get list of atomic intervals
        // those are the leaves in our segment tree
        set<int> e;
        for(i = 0; i < segments.size(); ++i) {
            e.insert(segments[i][0]);
            e.insert(segments[i][1]);
        }
        e.insert(INT_MIN);e.insert(INT_MAX);
        
        // build an empty segment tree
        vector<int> arr(e.begin(),e.end());
        int t = arr.size();
        Node* root = build(arr,0,t-1);
        
        // insert segments into segment tree 
        for(i = 0; i < n; ++i)
            insert(root,segments[i]);

        // get color for each interval
        vector<vector<long long>> ans;
        long long c;
        for(i = 2; i < t-1; ++i) {
            c = color(root,arr[i-1]);
            if( c != 0 )
                ans.push_back({arr[i-1],arr[i],c});
        }
        
        return ans;
    }
};
