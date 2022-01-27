
// 699. Falling Squares
// https://leetcode.com/problems/falling-squares/


class Solution {
private:
    struct Interval {
        int low, high;
    };

    struct Node {
        Interval *i;
        int max;
        Node *left, *right;
        int height;
    };

    Node* newNode(Interval i, int height) {
        Node * node = new Node;
        node->i = new Interval(i);
        node->max = i.high;
        node->left = nullptr;
        node->right = nullptr;
        node->height = height;
        return node;
    };

    Node* insert(Node *root, Interval i, int height) {
        if( root == nullptr ) return newNode(i,height);

        // no need to insert dups
        if( root->i->low == i.low && root->i->high == i.high ) {
            root->height = height;
            return root;
        }

        int l = root->i->low;
        if (i.low < l)
            root->left = insert(root->left,i,height);
        else
            root->right = insert(root->right,i,height);

        // update max value of this ancestor
        if (root->max < i.high)
            root->max = i.high;

        return root;
    }

    bool doOverlap(Interval i1, Interval i2) {
        if( i1.high <= i2.low ) return false;
        if( i1.low >= i2.high ) return false;
        return true;
    }

    int overlapSearch(Node *root, Interval i) {
        if(root == nullptr ) return 0;

        int rt = 0;
        if( doOverlap(*(root->i),i) )
            rt = root->height;

        int l = 0, r = 0;
        // if left child of root is present and max of left child is
        // greater than or equal to given interval, then interval may
        // overlap with an interval in left subtree
        if( root->left != nullptr && root->left->max >= i.low)
            l = overlapSearch(root->left,i);
        // else interval can only overlap with right subtree
        r = overlapSearch(root->right,i);

        return max({rt,l,r});
    }
public:
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        size_t n = positions.size();
        if( n == 1 ) return {positions[0][1]};

        vector<int> r(n);
        int low, side, currHeight, maxHeight = 0;
        Interval iv;
        Node *root = nullptr;
        for(int i = 0; i < n; ++i) {
            low = positions[i][0];
            side = positions[i][1];
            iv = {low,low+side};
            currHeight = overlapSearch(root,iv);
            maxHeight = max(maxHeight,currHeight+side);
            r[i] = maxHeight;
            root = insert(root,iv,currHeight+side);
        }

        return r;
    }
};
